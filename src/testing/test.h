#ifndef RELEASE

#pragma once

#include "../base.h"
#include "../log.h"

#include "../data/emap.h"

typedef void (*test_fn)();

DECL_EMAP(TestEMap, test_fn);

bool TEST_FAILED = false;
TestEMap test_map = {0};

void test_add(emap_key name, test_fn test) {
  if (!TestEMap_is_initialized(test_map)) {
    TestEMap_init(&test_map);
  }

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

#define ASSERT(condition, message)                                             \
  if (!condition) {                                                            \
    ERROR(message);                                                            \
    TEST_FAILED = true;                                                        \
  }

#define CHECK(err, message)                                                    \
  if (err) {                                                                   \
    ERROR("%s (error: %d)", message, err);                                     \
    TEST_FAILED = true;                                                        \
  }

#define ASSERT_FATAL(condition, message)                                       \
  if (!condition) {                                                            \
    FATAL(message);                                                            \
    TEST_FAILED = true;                                                        \
                                                                               \
    return;                                                                    \
  }

#define CHECK_FATAL(err, message)                                              \
  if (err) {                                                                   \
    FATAL("%s (error: %d)", message, err);                                     \
    TEST_FAILED = true;                                                        \
                                                                               \
    return;                                                                    \
  }

#endif
