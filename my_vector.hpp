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

  my_vector(const allocator_type &allocator = allocator_type())
      : first_(nullptr), last_(nullptr), allocator_(allocator) {}

  my_vector(size_type size, const allocator_type &allocator = allocator_type())
      : my_vector(allocator) {
    first_ = traits::allocate(allocator_, size);
    last_ = first_ + size;

    for (auto p = first_; p != last_; ++p) {
      traits::construct(allocator_, p, T{});
    }
  }

  size_type size() { return end() - begin(); }
  bool empty() { return begin() == end(); }

  reference front() { return *begin(); }
  reference back() { return *rbegin(); };

  iterator begin() { return first_; }
  iterator end() { return last_; }
  std::reverse_iterator<iterator> rbegin() {
    return std::reverse_iterator<iterator>{end()};
  }
  std::reverse_iterator<iterator> rend() {
    return std::reverse_iterator<iterator>{begin()};
  }

  reference at(size_type index) {
    if (index >= size())
      throw std::out_of_range("index is out of range.");

    return operator[](index);
  }

  pointer data() { return first_; }
  reference operator[](size_type index) { return *(first_ + index); }

  void clear() { destroy_until(rend()); }

  ~my_vector() {
    clear();
    traits::deallocate(allocator_, first_, size());
  }

private:
  using traits = std::allocator_traits<allocator_type>;

  pointer first_, last_;
  allocator_type allocator_;

  void destroy_until(std::reverse_iterator<iterator> rend) {
    for (auto riterator = rbegin(); riterator != rend; ++riterator, --last_) {
      traits::destroy(allocator_, &*riterator);
    }
  }
};
