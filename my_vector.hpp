#include <cstddef>
#include <iostream>
using namespace std::literals;

template <typename T, typename Allocator = std::allocator<T>> class my_vector {
  using traits = std::allocator_traits<Allocator>;

public:
  my_vector() { std::cout << "constructed \n"s; };

  my_vector(std::size_t size = 0, Allocator allocator = Allocator())
      : allocator_(allocator), size_(size) {
    pointer_ = traits::allocate(allocator_, size_);
  }

  std::size_t size() { return size_; }

  T &front() { return *pointer_; }

  ~my_vector() { traits::deallocate(allocator_, pointer_, size_); }

private:
  T *pointer_;
  Allocator allocator_;
  std::size_t size_;
};
