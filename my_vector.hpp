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
      : first_(nullptr), last_(nullptr), reserved_last_(nullptr),
        allocator_(allocator) {}

  my_vector(size_type size, const allocator_type &allocator = allocator_type())
      : my_vector(allocator) {
    resize(size);
  }

  my_vector(const my_vector &v) : allocator_(v.allocator_) {
    auto size = v.size();
    reserve(size);
    for (auto source_iterator = v.begin(), destination_iterator = begin();
         source_iterator != v.end();
         ++source_iterator, ++destination_iterator) {
      traits::construct(allocator_, &*destination_iterator, *source_iterator);
    }
    last_ = first_ + size;
  }

  void reserve(size_type size) {
    if (capacity() > size)
      return;

    auto old_first = first_;
    auto old_last = last_;
    auto old_capacity = capacity();

    first_ = traits::allocate(allocator_, size);
    last_ = first_;
    reserved_last_ = first_ + size;

    for (auto old_iterator = old_first; old_iterator != old_last;
         ++old_iterator, ++last_) {
      traits::construct(allocator_, last_, std::move(*old_iterator));
    }

    for (auto riterator = std::reverse_iterator<iterator>(old_last),
              rend = std::reverse_iterator<iterator>(old_first);
         riterator != rend; ++riterator) {
      traits::destroy(allocator_, &*riterator);
    }

    traits::deallocate(allocator_, old_first, old_capacity);
  }

  void resize(size_type size) {
    auto current_size = this->size();

    if (size == current_size)
      return;

    if (size < current_size) {
      destroy_until(rbegin() + current_size - size);
      return;
    }

    if (size > current_size) {
      reserve(size);
      for (; last_ != reserved_last_; ++last_) {
        traits::construct(allocator_, last_);
      }
      return;
    }
  }

  size_type size() { return end() - begin(); }
  size_type capacity() { return reserved_last_ - first_; }
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

  pointer first_, last_, reserved_last_;
  allocator_type allocator_;

  void destroy_until(std::reverse_iterator<iterator> rend) {
    for (auto riterator = rbegin(); riterator != rend; ++riterator, --last_) {
      traits::destroy(allocator_, &*riterator);
    }
  }
};
