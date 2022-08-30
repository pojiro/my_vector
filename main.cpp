#include <cassert>
#include <new>

#include "my_vector.hpp"

int main(int argc, char *argv[]) {
  std::size_t size = 5;
  auto v = my_vector<int>{size};

  assert(v.size() == size);

  assert(v.front() == 0);
  v.front() = 1;
  assert(v.front() == 1);

  assert(v[1] == 0);
  v[1] = 1;
  assert(v[1] == 1);

  return 0;
}
