#include "log.h"

#define assert(condition, message)                                             \
  if (!condition) {                                                            \
    FATAL(message);                                                            \
    exit(1);                                                                   \
  }

#define check(condition, err)                                                  \
  if (!condition) {                                                            \
    return err;                                                                \
  }
