#include <cstddef>
#include <iostream>
using namespace std::literals;

template <typename T, typename Allocator = std::allocator<T>> class my_vector {
public:
  using value_type = T;
  using pointer = T *;
  using reference = T &;
  using allocator_type = Allocator;
  using size_type = std::size_t;

  my_vector(size_type size = 0, allocator_type allocator = allocator_type())
      : allocator_(allocator), size_(size) {
    first_ = traits::allocate(allocator_, size_);
  }

  size_type size() { return size_; }

  reference front() { return *first_; }

  reference operator[](size_type index) { return *(first_ + index); }

  ~my_vector() { traits::deallocate(allocator_, first_, size_); }

private:
  using traits = std::allocator_traits<allocator_type>;

  pointer first_;
  allocator_type allocator_;
  size_type size_;
};
