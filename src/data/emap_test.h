#include "../testing/test.h"

#include "emap.h"

DECL_EMAP(emap_t, int)

void emap_test() {
  emap_t emap = {0};

  CHECK_FATAL(emap_t_init(&emap), "EMap failed to init")
  CHECK(emap_t_deinit(&emap), "EMap failed to deinit")
}
