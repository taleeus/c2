#include "log.h"

#define assert(condition, message)                                             \
  if (!condition) {                                                            \
    FATAL(message);                                                            \
    exit(1);                                                                   \
  }
