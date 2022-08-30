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
      : allocator_(allocator) {
    first_ = traits::allocate(allocator_, size);
    last_ = first_ + size;
  }

  size_type size() {
    size_type size;
    if (first_ == last_) {
      size = 0;
    } else {
      size = last_ - first_;
    }
    return static_cast<size_type>(size);
  }

  reference front() { return this->operator[](0); }
  reference back() {
    size_type size = this->size();
    if (size == 0) {
      return front();
    } else {
      return this->operator[](size - 1);
    }
  };

  reference operator[](size_type index) { return *(first_ + index); }

  ~my_vector() { traits::deallocate(allocator_, first_, size()); }

private:
  using traits = std::allocator_traits<allocator_type>;

  pointer first_, last_;
  allocator_type allocator_;
};
