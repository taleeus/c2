#include "../base.h"

#include <stdlib.h>
#include <string.h>

#include "__data.h"
#include "_errors.h"

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
  error typename##_init(typename *list) {                                      \
    if (!list) {                                                               \
      return ERROR_NIL_ARG;                                                    \
    }                                                                          \
                                                                               \
    if (typename##_is_initialized(*list)) {                                    \
      return nil;                                                              \
    }                                                                          \
                                                                               \
    list->len = 0;                                                             \
    if (list->cap <= 0) {                                                      \
      list->cap = CAP_DEFAULT;                                                 \
    }                                                                          \
                                                                               \
    list->values = calloc(list->cap, sizeof(type));                            \
    if (!list->values) {                                                       \
      return ERROR_CALLOC;                                                     \
    }                                                                          \
                                                                               \
    return nil;                                                                \
  }                                                                            \
                                                                               \
  error typename##_deinit(typename *list) {                                    \
    if (!list) {                                                               \
      return ERROR_NIL_ARG;                                                    \
    }                                                                          \
                                                                               \
    if (!typename##_is_initialized(*list)) {                                   \
      return nil;                                                              \
    }                                                                          \
                                                                               \
    free(list->values);                                                        \
    list->values = nil;                                                        \
                                                                               \
    list->len = 0;                                                             \
    list->cap = 0;                                                             \
                                                                               \
    return nil;                                                                \
  }                                                                            \
                                                                               \
  error typename##_append(typename *list, type value) {                        \
    if (!list) {                                                               \
      return ERROR_NIL_ARG;                                                    \
    }                                                                          \
                                                                               \
    if (!typename##_is_initialized(*list)) {                                   \
      return ERROR_NOT_INITIALIZED;                                            \
    }                                                                          \
                                                                               \
    if (list->len == list->cap) {                                              \
      list->cap *= 2;                                                          \
                                                                               \
      if (!realloc(list->values, sizeof(type) * (list->cap))) {                \
        return ERROR_REALLOC;                                                  \
      }                                                                        \
      memset(&list->values[list->len], nil, list->cap - list->len);            \
    }                                                                          \
                                                                               \
    list->values[list->len] = value;                                           \
    list->len++;                                                               \
                                                                               \
    return nil;                                                                \
  }

DECL_ALIST(_test_alist, int)
