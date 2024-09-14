#include "../defines.h"

#include "data.h"

typedef struct EMap {
  char **keys;
  void **values;

  size len;
  size cap;
} EMap;

error EMap_init(EMap *map);
error EMap_deinit(EMap *map);
error EMap_append(EMap *map, char *key, void *value);
error EMap_lookup(EMap *map, char *key, void **value_out);
error EMap_delete(EMap *map, char *key);
