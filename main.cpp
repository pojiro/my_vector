#include <cassert>
#include <new>

#include "my_vector.hpp"

int main(int argc, char *argv[]) {
  void *ptr = ::operator new(sizeof(my_vector<int>));
  auto v_ptr = new (ptr) my_vector<int>{};

  assert(v_ptr->size() == 0);
  return 0;
}
