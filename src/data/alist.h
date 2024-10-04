#pragma once

#include "../base.h"

#include <stdlib.h>
#include <string.h>

#include "__data.h"

#define DECL_ALIST(typename, type)                                             \
  typedef struct {                                                             \
    isize len, cap;                                                            \
    type *values;                                                              \
  } typename;                                                                  \
                                                                               \
  bool typename##_is_initialized(typename list) {                              \
    if (list.values) {                                                         \
      return true;                                                             \
    }                                                                          \
                                                                               \
    return false;                                                              \
  }                                                                            \
                                                                               \
  void typename##_init(typename *list) {                                       \
    assert(list, "list is nil");                                               \
    if (typename##_is_initialized(*list))                                      \
      return;                                                                  \
                                                                               \
    list->len = 0;                                                             \
    if (list->cap <= 0) {                                                      \
      list->cap = CAP_DEFAULT;                                                 \
    }                                                                          \
                                                                               \
    list->values = calloc(list->cap, sizeof(type));                            \
    assert(list->values, "couldn't calloc list values");                       \
  }                                                                            \
                                                                               \
  void typename##_deinit(typename *list) {                                     \
    assert(list, "list is nil");                                               \
    assert(typename##_is_initialized(*list), "list is not initialized");       \
                                                                               \
    free(list->values);                                                        \
    list->values = nil;                                                        \
                                                                               \
    list->len = 0;                                                             \
    list->cap = 0;                                                             \
  }                                                                            \
                                                                               \
  void typename##_append(typename *list, type value) {                         \
    assert(list, "list is nil");                                               \
    assert(typename##_is_initialized(*list), "list is not initialized");       \
                                                                               \
    if (list->len == list->cap) {                                              \
      list->cap *= 2;                                                          \
                                                                               \
      void *ok = realloc(list->values, sizeof(type) * (list->cap));            \
      assert(ok, "couldn't realloc list");                                     \
                                                                               \
      memset(&list->values[list->len], nil, list->cap - list->len);            \
    }                                                                          \
                                                                               \
    list->values[list->len] = value;                                           \
    list->len++;                                                               \
  }

DECL_ALIST(alist_check, int)
