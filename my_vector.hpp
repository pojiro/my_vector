#include <cstddef>
#include <iostream>
using namespace std::literals;

template <typename T> class my_vector {
public:
  my_vector() { std::cout << "constructed \n"s; };

  std::size_t size() { return 0; };
};
