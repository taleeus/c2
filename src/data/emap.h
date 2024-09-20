#pragma once

#include "../base.h"

#include <stdlib.h>
#include <string.h>

#include "__data.h"
#include "_errors.h"

#define EMAP_KEY_SIZE 32

typedef char emap_key[EMAP_KEY_SIZE];

#define DECL_EMAP(typename, type)                                              \
  typedef struct {                                                             \
    isize len, cap;                                                            \
                                                                               \
    emap_key *keys;                                                            \
    type *values;                                                              \
  } typename;                                                                  \
                                                                               \
  bool typename##_is_initialized(typename map) {                               \
    if (map.keys || map.values) {                                              \
      return true;                                                             \
    }                                                                          \
                                                                               \
    return false;                                                              \
  }                                                                            \
                                                                               \
  error typename##_init(typename *map) {                                       \
    if (!map) {                                                                \
      return ERROR_NIL_ARG;                                                    \
    }                                                                          \
                                                                               \
    if (typename##_is_initialized(*map)) {                                     \
      return nil;                                                              \
    }                                                                          \
                                                                               \
    map->len = 0;                                                              \
    if (map->cap <= 0) {                                                       \
      map->cap = CAP_DEFAULT;                                                  \
    }                                                                          \
                                                                               \
    map->keys = calloc(map->cap, sizeof(emap_key));                            \
    if (!map->keys) {                                                          \
      return ERROR_CALLOC;                                                     \
    }                                                                          \
                                                                               \
    map->values = calloc(map->cap, sizeof(type));                              \
    if (!map->values) {                                                        \
      return ERROR_CALLOC;                                                     \
    }                                                                          \
                                                                               \
    return nil;                                                                \
  }                                                                            \
                                                                               \
  error typename##_deinit(typename *map) {                                     \
    if (!map) {                                                                \
      return ERROR_NIL_ARG;                                                    \
    }                                                                          \
                                                                               \
    if (!typename##_is_initialized(*map)) {                                    \
      return nil;                                                              \
    }                                                                          \
                                                                               \
    free(map->keys);                                                           \
    map->keys = nil;                                                           \
                                                                               \
    free(map->values);                                                         \
    map->values = nil;                                                         \
                                                                               \
    map->len = 0;                                                              \
    map->cap = 0;                                                              \
                                                                               \
    return nil;                                                                \
  }                                                                            \
                                                                               \
  error typename##_append(typename *map, emap_key key, type value) {           \
    if (!map) {                                                                \
      return ERROR_NIL_ARG;                                                    \
    }                                                                          \
                                                                               \
    if (!typename##_is_initialized(*map)) {                                    \
      return ERROR_NOT_INITIALIZED;                                            \
    }                                                                          \
                                                                               \
    if (map->len == map->cap) {                                                \
      map->cap *= 2;                                                           \
      if (!realloc(map->keys, sizeof(emap_key) * (map->cap))) {                \
        return ERROR_REALLOC;                                                  \
      }                                                                        \
      memset(&map->keys[map->len], nil, map->cap - map->len);                  \
                                                                               \
      if (!realloc(map->values, sizeof(type) * (map->cap))) {                  \
        return ERROR_REALLOC;                                                  \
      }                                                                        \
      memset(&map->values[map->len], nil, map->cap - map->len);                \
    }                                                                          \
                                                                               \
    strncpy(map->keys[map->len], key, EMAP_KEY_SIZE);                          \
    map->values[map->len] = value;                                             \
                                                                               \
    map->len++;                                                                \
                                                                               \
    return nil;                                                                \
  }                                                                            \
                                                                               \
  error typename##_lookup(typename *map, emap_key key, type *value_out) {      \
    if (!map) {                                                                \
      return ERROR_NIL_ARG;                                                    \
    }                                                                          \
                                                                               \
    if (!typename##_is_initialized(*map)) {                                    \
      return ERROR_NOT_INITIALIZED;                                            \
    }                                                                          \
                                                                               \
    for (isize i = 0; i < map->len; i++) {                                     \
      if (strncmp(map->keys[i], key, EMAP_KEY_SIZE) == 0) {                    \
        *value_out = map->values[i];                                           \
        break;                                                                 \
      }                                                                        \
    }                                                                          \
                                                                               \
    return nil;                                                                \
  }                                                                            \
                                                                               \
  error typename##_delete(typename *map, emap_key key) {                       \
    if (!map) {                                                                \
      return ERROR_NIL_ARG;                                                    \
    }                                                                          \
                                                                               \
    if (!typename##_is_initialized(*map)) {                                    \
      return ERROR_NOT_INITIALIZED;                                            \
    }                                                                          \
                                                                               \
    bool found;                                                                \
    for (isize i = 0; i < map->len; i++) {                                     \
      if (!found) {                                                            \
        if (strncmp(map->keys[i], key, EMAP_KEY_SIZE) == 0) {                  \
          found = true;                                                        \
        } else                                                                 \
          continue;                                                            \
      }                                                                        \
                                                                               \
      if (i + 1 == map->len) {                                                 \
        memset(&map->keys[i], nil, EMAP_KEY_SIZE);                             \
        map->values[i] = nil;                                                  \
      } else {                                                                 \
        strncpy(map->keys[map->len], map->keys[i + 1], EMAP_KEY_SIZE);         \
        map->values[i] = map->values[i + 1];                                   \
      }                                                                        \
    }                                                                          \
                                                                               \
    if (found) {                                                               \
      map->len--;                                                              \
    }                                                                          \
                                                                               \
    return nil;                                                                \
  }

DECL_EMAP(emap_check, int)
