#include <cassert>

#include "my_vector.hpp"

int main(int argc, char *argv[]) {
  auto v = my_vector<int>();

  assert(v.size() == 0);
  return 0;
}
