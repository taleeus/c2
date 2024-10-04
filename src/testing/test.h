#ifndef CRELEASE

#pragma once

#include "../base.h"
#include "../log.h"

#include "../data/emap.h"

typedef void (*test_fn)();

DECL_EMAP(TestEMap, test_fn);

bool TEST_FAILED = false;
TestEMap test_map = {0};

void test_add(emap_key name, test_fn test) {
  TestEMap_init(&test_map);
  TestEMap_append(&test_map, name, test);
}

i32 test_run() {
  i32 passed = 0;
  i32 failed = 0;

  INFO("Running %d tests\n", test_map.len)
  for (i32 i = 0; i < test_map.len; i++) {
    INFO(test_map.keys[i])
    test_map.values[i]();

    if (TEST_FAILED) {
      failed++;
    } else {
      passed++;
    }

    TEST_FAILED = false;
  }

  INFO("Passed: %d\tFailed: %d", passed, failed)
  return failed;
}

#define test(condition, message)                                               \
  if (!condition) {                                                            \
    ERROR(message);                                                            \
    TEST_FAILED = true;                                                        \
  }

#undef assert
#define assert(condition, message)                                             \
  if (!condition) {                                                            \
    FATAL(message);                                                            \
    TEST_FAILED = true;                                                        \
                                                                               \
    exit(1);                                                                   \
  }

#undef check
#define check(condition, err)                                                  \
  if (!condition) {                                                            \
    TEST_FAILED = true;                                                        \
    return err;                                                                \
  }

#endif
