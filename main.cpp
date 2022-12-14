#include <cassert>
#include <new>

#include "my_vector.hpp"

int main(int argc, char *argv[]) {
  std::size_t size = 5;
  auto v = my_vector<int>{size};

  assert(v.size() == size);
  assert(v.empty() == false);

  assert(v.front() == 0);
  v.front() = 1;
  assert(v.front() == 1);

  assert(v.back() == 0);
  v.back() = 5;
  assert(v.back() == 5);

  assert(v[1] == 0);
  v[1] = 1;
  assert(v[1] == 1);

  v.resize(3);
  assert(v.size() == 3);

  v.reserve(5);
  assert(v.capacity() == 5);
  assert(v[1] == 1);

  auto empty_v = my_vector<int>{};
  assert(empty_v.size() == 0);
  assert(empty_v.empty() == true);
  assert(empty_v.capacity() == 0);

  empty_v.reserve(5);
  assert(empty_v.capacity() == 5);
  empty_v.reserve(1);
  assert(empty_v.capacity() == 5);

  return 0;
}
