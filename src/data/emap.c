#include <stdlib.h>
#include <string.h>

#include "../errors.h"

#include "data.h"
#include "emap.h"
#include "errors.h"

bool emap_is_initialized(EMap map) {
  if (map.keys || map.values) {
    return true;
  }

  return false;
}

error EMap_init(EMap *map) {
  if (!map) {
    return ERROR_NIL_ARG;
  }

  if (emap_is_initialized(*map)) {
    return nil;
  }

  if (!map->cap) {
    map->cap = CAP_DEFAULT;
  }

  map->keys = calloc(map->cap, sizeof(char *));
  if (!map->keys) {
    return ERROR_CALLOC;
  }

  map->values = calloc(map->cap, sizeof(void *));
  if (!map->values) {
    return ERROR_CALLOC;
  }

  return nil;
}

error EMap_deinit(EMap *map) {
  if (!map) {
    return ERROR_NIL_ARG;
  }

  if (!emap_is_initialized(*map)) {
    return nil;
  }

  free(map->keys);
  map->keys = nil;

  free(map->values);
  map->values = nil;

  map->len = 0;
  map->cap = 0;

  return nil;
}

error EMap_append(EMap *map, char *key, void *value) {
  if (!map) {
    return ERROR_NIL_ARG;
  }

  if (!emap_is_initialized(*map)) {
    return ERROR_NOT_INITIALIZED;
  }

  if (map->len == map->cap) {
    map->cap *= 2;
    if (!realloc(map->keys, sizeof(char *) * (map->cap))) {
      return ERROR_REALLOC;
    }
    memset(map->keys[map->len], 0, map->cap - map->len);

    if (!realloc(map->values, sizeof(void *) * (map->cap))) {
      return ERROR_REALLOC;
    }
    memset(map->values[map->len], 0, map->cap - map->len);
  }

  map->keys[map->len] = key;
  map->values[map->len] = value;

  map->len++;

  return nil;
}

error EMap_lookup(EMap *map, char *key, void **value_out) {
  if (!map) {
    return ERROR_NIL_ARG;
  }

  if (!emap_is_initialized(*map)) {
    return ERROR_NOT_INITIALIZED;
  }

  for (size i = 0; i < map->len; i++) {
    if (strcmp(map->keys[i], key) == 0) {
      *value_out = map->values[i];
      break;
    }
  }

  return nil;
}

error EMap_delete(EMap *map, char *key) {
  if (!map) {
    return ERROR_NIL_ARG;
  }

  if (!emap_is_initialized(*map)) {
    return ERROR_NOT_INITIALIZED;
  }

  bool found;
  for (size i = 0; i < map->len; i++) {
    if (!found) {
      if (strcmp(map->keys[i], key) == 0) {
        found = true;
      } else
        continue;
    }

    if (i + 1 == map->len) {
      map->keys[i] = nil;
      map->values[i] = nil;
    } else {
      map->keys[i] = map->keys[i + 1];
      map->values[i] = map->values[i + 1];
    }
  }

  return nil;
}
