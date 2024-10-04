#pragma once

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
  void typename##_init(typename *tree, type value) {                           \
    assert(!tree, "tree is nil");                                              \
    if (typename##_is_initialized(*tree))                                      \
      return;                                                                  \
                                                                               \
    tree->len = 0;                                                             \
    if (tree->cap <= 0) {                                                      \
      tree->cap = ATREE_CAP_DEFAULT;                                           \
    }                                                                          \
                                                                               \
    tree->nodes = calloc(tree->cap, sizeof(typename));                         \
    assert(tree->nodes, "couldn't calloc tree nodes");                         \
                                                                               \
    tree->value = value;                                                       \
  }                                                                            \
                                                                               \
  void typename##_deinit(typename *tree) {                                     \
    assert(tree, "tree is nil");                                               \
    assert(typename##_is_initialized(*tree), "tree is not initialized");       \
                                                                               \
    for (isize i = 0; i < tree->len; i++) {                                    \
      typename##_deinit(&tree->nodes[i]);                                      \
    }                                                                          \
                                                                               \
    free(tree->nodes);                                                         \
  }                                                                            \
                                                                               \
  void typename##_append(typename *tree, type value) {                         \
    assert(tree, "tree is nil");                                               \
    assert(typename##_is_initialized(*tree), "tree is not initialized");       \
                                                                               \
    if (tree->len == tree->cap) {                                              \
      tree->cap *= 2;                                                          \
                                                                               \
      void *ok = realloc(tree->nodes, sizeof(typename) * (tree->cap));         \
      assert(ok, "couldn't realloc tree");                                     \
                                                                               \
      memset(&tree->nodes[tree->len], nil, tree->cap - tree->len);             \
    }                                                                          \
                                                                               \
    typename node = {0};                                                       \
    node.value = value;                                                        \
                                                                               \
    tree->nodes[tree->len] = node;                                             \
    tree->len++;                                                               \
  }

DECL_ATREE(atree_check, int)
