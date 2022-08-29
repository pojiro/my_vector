#include <cassert>
#include <new>

#include "my_vector.hpp"

int main(int argc, char *argv[]) {
  auto v_ptr = new my_vector<int>{};

  assert(v_ptr->size() == 0);
  return 0;
}
