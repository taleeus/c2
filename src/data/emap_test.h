#include "emap.h"

DECL_EMAP(emap_t, int)

void emap_test() {
  emap_t emap = {0};

  emap_t_init(&emap);
  emap_t_deinit(&emap);
}
