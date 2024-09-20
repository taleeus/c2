#include "testing/test.h"

#include "data/emap_test.h"

int main() {
  test_add("Data/EMap", emap_test);

  return test_run();
}
