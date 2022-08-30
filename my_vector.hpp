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
    pointer_ = traits::allocate(allocator_, size_);
  }

  size_type size() { return size_; }

  reference front() { return *pointer_; }

  reference operator[](size_type index) { return *(pointer_ + index); }

  ~my_vector() { traits::deallocate(allocator_, pointer_, size_); }

private:
  using traits = std::allocator_traits<allocator_type>;

  pointer pointer_;
  allocator_type allocator_;
  size_type size_;
};
