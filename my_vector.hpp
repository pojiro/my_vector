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
  using iterator = pointer;

  my_vector(size_type size = 0, allocator_type allocator = allocator_type())
      : allocator_(allocator) {
    first_ = traits::allocate(allocator_, size);
    last_ = first_ + size;
  }

  size_type size() { return end() - begin(); }
  bool empty() { return begin() == end(); }

  reference front() { return *begin(); }
  reference back() {
    if (begin() == end()) {
      return front();
    } else {
      return *(end() - 1);
    }
  };

  iterator begin() { return first_; }
  iterator end() { return last_; }

  reference operator[](size_type index) { return *(first_ + index); }

  ~my_vector() { traits::deallocate(allocator_, first_, size()); }

private:
  using traits = std::allocator_traits<allocator_type>;

  pointer first_, last_;
  allocator_type allocator_;
};
