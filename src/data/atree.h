#include "../base.h"

#include <stdlib.h>
#include <string.h>

#define ATREE_CAP_DEFAULT 4

#define DECL_ATREE(typename, type)                                             \
  typedef struct typename {                                                    \
    isize len, cap;                                                            \
                                                                               \
    type value;                                                                \
    struct typename *nodes;                                                    \
  }                                                                            \
  typename;                                                                    \
                                                                               \
  bool typename##_is_initialized(typename tree) {                              \
    if (tree.cap) {                                                            \
      return true;                                                             \
    }                                                                          \
                                                                               \
    return false;                                                              \
  }                                                                            \
                                                                               \
  error typename##_init(typename *tree, type value) {                          \
    if (!tree) {                                                               \
      return ERROR_NIL_ARG;                                                    \
    }                                                                          \
                                                                               \
    if (typename##_is_initialized(*tree)) {                                    \
      return nil;                                                              \
    }                                                                          \
                                                                               \
    tree->len = 0;                                                             \
    if (tree->cap <= 0) {                                                      \
      tree->cap = ATREE_CAP_DEFAULT;                                           \
    }                                                                          \
                                                                               \
    tree->nodes = calloc(tree->cap, sizeof(typename));                         \
    if (!tree->nodes) {                                                        \
      return ERROR_CALLOC;                                                     \
    }                                                                          \
                                                                               \
    tree->value = value;                                                       \
    return nil;                                                                \
  }                                                                            \
                                                                               \
  error typename##_deinit(typename *tree) {                                    \
    if (!tree) {                                                               \
      return ERROR_NIL_ARG;                                                    \
    }                                                                          \
                                                                               \
    if (!typename##_is_initialized(*tree)) {                                   \
      return nil;                                                              \
    }                                                                          \
                                                                               \
    for (isize i = 0; i < tree->len; i++) {                                    \
      typename node = tree->nodes[i];                                          \
      error err = typename##_deinit(&node);                                    \
      if (err) {                                                               \
        return err;                                                            \
      }                                                                        \
    }                                                                          \
                                                                               \
    free(tree->nodes);                                                         \
    return nil;                                                                \
  }                                                                            \
                                                                               \
  error typename##_append(typename *tree, type value) {                        \
    if (!tree) {                                                               \
      return ERROR_NIL_ARG;                                                    \
    }                                                                          \
                                                                               \
    if (!typename##_is_initialized(*tree)) {                                   \
      typename##_init(tree, tree->value);                                      \
    }                                                                          \
                                                                               \
    if (tree->len == tree->cap) {                                              \
      tree->cap *= 2;                                                          \
                                                                               \
      if (!realloc(tree->nodes, sizeof(typename) * (tree->cap))) {             \
        return ERROR_REALLOC;                                                  \
      }                                                                        \
      memset(&tree->nodes[tree->len], nil, tree->cap - tree->len);             \
    }                                                                          \
                                                                               \
    typename node = {0};                                                       \
    node.value = value;                                                        \
                                                                               \
    tree->nodes[tree->len] = node;                                             \
    tree->len++;                                                               \
                                                                               \
    return nil;                                                                \
  }

DECL_ATREE(_test_atree, int)
