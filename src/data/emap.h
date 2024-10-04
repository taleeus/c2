#pragma once

#include "../base.h"

#include <stdlib.h>
#include <string.h>

#include "__data.h"

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
  void typename##_init(typename *map) {                                        \
    assert(map, "map is nil");                                                 \
    if (typename##_is_initialized(*map))                                       \
      return;                                                                  \
                                                                               \
    map->len = 0;                                                              \
    if (map->cap <= 0) {                                                       \
      map->cap = CAP_DEFAULT;                                                  \
    }                                                                          \
                                                                               \
    map->keys = calloc(map->cap, sizeof(emap_key));                            \
    assert(map->keys, "couldn't calloc map keys");                             \
                                                                               \
    map->values = calloc(map->cap, sizeof(type));                              \
    assert(map->values, "couldn't calloc map values");                         \
  }                                                                            \
                                                                               \
  void typename##_deinit(typename *map) {                                      \
    assert(map, "map is nil");                                                 \
    assert(typename##_is_initialized(*map), "map is not initialized");         \
                                                                               \
    free(map->keys);                                                           \
    map->keys = nil;                                                           \
                                                                               \
    free(map->values);                                                         \
    map->values = nil;                                                         \
                                                                               \
    map->len = 0;                                                              \
    map->cap = 0;                                                              \
  }                                                                            \
                                                                               \
  void typename##_append(typename *map, emap_key key, type value) {            \
    assert(map, "map is nil");                                                 \
    assert(typename##_is_initialized(*map), "map is not initialized");         \
                                                                               \
    if (map->len == map->cap) {                                                \
      map->cap *= 2;                                                           \
                                                                               \
      void *ok_keys = realloc(map->keys, sizeof(emap_key) * (map->cap));       \
      assert(ok_keys, "couldn't realloc map keys");                            \
      memset(&map->keys[map->len], nil, map->cap - map->len);                  \
                                                                               \
      void *ok_values = realloc(map->values, sizeof(type) * (map->cap));       \
      assert(ok_values, "couldn't realloc map values");                        \
      memset(&map->values[map->len], nil, map->cap - map->len);                \
    }                                                                          \
                                                                               \
    strncpy(map->keys[map->len], key, EMAP_KEY_SIZE);                          \
    map->values[map->len] = value;                                             \
                                                                               \
    map->len++;                                                                \
  }                                                                            \
                                                                               \
  bool typename##_lookup(typename *map, emap_key key, type *value_out) {       \
    assert(map, "map is nil");                                                 \
    assert(typename##_is_initialized(*map), "map is not initialized");         \
                                                                               \
    for (isize i = 0; i < map->len; i++) {                                     \
      if (strncmp(map->keys[i], key, EMAP_KEY_SIZE) == 0) {                    \
        *value_out = map->values[i];                                           \
        return true;                                                           \
      }                                                                        \
    }                                                                          \
                                                                               \
    return false;                                                              \
  }                                                                            \
                                                                               \
  bool typename##_delete(typename *map, emap_key key) {                        \
    assert(map, "map is nil");                                                 \
    assert(typename##_is_initialized(*map), "map is not initialized");         \
                                                                               \
    bool found;                                                                \
    for (isize i = 0; i < map->len; i++) {                                     \
      if (!found) {                                                            \
        if (strncmp(map->keys[i], key, EMAP_KEY_SIZE) == 0)                    \
          found = true;                                                        \
        else                                                                   \
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
    return found;                                                              \
  }

DECL_EMAP(emap_check, int)
