#include <cassert>
#include <new>

#include "my_vector.hpp"

int main(int argc, char *argv[]) {
  std::size_t size = 5;
  auto v = my_vector<int>{size};

  assert(v.size() == size);
  return 0;
}
