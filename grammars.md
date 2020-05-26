# This page lists the useful C++ grammars, especially for C++11, C++14, C++17 and C++20.



## three-way comparison

Before C++20, when we want to make a class comparable, we have to overload many operators (`==`, `!=`, `<`, `<=`, `>`, `>=`). Though [Boost](https://www.boost.org/ "Boost C++ Libraries") uses a tricky way to implement a helper `boost/operators.hpp`：

```c++
#include <boost/operators.hpp>
#include <cassert>

class Foo : public boost::less_than_comparable<Foo> {
 public:
  Foo(int x) : m_x(x) {}
  friend bool operator<(Foo lhs, Foo rhs) { return lhs.m_x < rhs.m_x; }

 private:
  int m_x;
};

int main() {
  Foo a(1), b(2);
  assert(b > a); // We only overloaded operator<.
}
```

It is still very inconvenient.

C++20 introduces a new operator `<=>` called three-way comparison operator or spaceship operator (because it looks like a spaceship). Now, we only need to overload this three-way operator or even simply set as default (`=default`). The compiler will generate other comparison operators automatically and correctly.
**Note**: If `<=>` is not defaulted, `==` and `！=` won’t be generated. Here is the [reason](https://stackoverflow.com/questions/58780829/equality-operator-does-not-get-defined-for-a-custom-spaceship-operator-implement "Stack Overflow").

There are three available return types (declared in header file `compare`):

- `std::strong_ordering`
- `std::weak_ordering`
- `std::partial_ordering`

They represent for different ordering types as their names show. We have learned these three ordering types in Discrete Mathematics (1). So I will just give three examples to show how it works.

- strong ordering

  ```c++
  #include <cassert>
  #include <compare>
  
  struct Foo {
    int x;
    friend std::strong_ordering operator<=>(Foo lhs, Foo rhs) {
      return lhs.x <=> rhs.x;
    }
    friend bool operator==(Foo lhs, Foo rhs) { return (lhs <=> rhs) == 0; }
  };
  
  int main() {
    Foo a{0}, b{1};
    assert(!(a == b)); assert(a != b);
    assert(a < b); assert(a <= b);
    assert(b > a); assert(b >= a);
  }
  ```

- weak ordering

  ```c++
  #include <cassert>
  #include <compare>
  
  struct Foo {
    int x, y;
    friend std::weak_ordering operator<=>(Foo lhs, Foo rhs) {
      return lhs.x <=> rhs.x;
    }
    friend bool operator==(Foo lhs, Foo rhs) { return (lhs <=> rhs) == 0; }
  };
  
  int main() {
    Foo a{0, 1}, b{0, 2};
    assert(a == b); assert(!(a != b));
    assert(!(a < b)); assert(a <= b);
    assert(!(b > a)); assert(b >= a);
  }
  ```

- partial ordering

  ```c++
  #include <cassert>
  #include <compare>
  
  struct Foo {
    int x, y;
    friend std::partial_ordering operator<=>(Foo lhs, Foo rhs) {
      auto cmp_x = (lhs.x <=> rhs.x);
      auto cmp_y = (lhs.y <=> rhs.y);
      if (cmp_x == cmp_y)
        return cmp_x;
      else
        return std::partial_ordering::unordered;
    }
    friend bool operator==(Foo lhs, Foo rhs) { return (lhs <=> rhs) == 0; }
  };
  
  int main() {
    Foo a{0, 1}, b{1, 0};
    assert(!(a == b)); assert(a != b);
    assert(!(a < b)); assert(!(a <= b));
    assert(!(b > a)); assert(!(b >= a));
  }
  ```

You can find more information on [cppreference.com](https://en.cppreference.com/ "cppreference.com"):

- [comparison operators](https://en.cppreference.com/w/cpp/language/operator_comparison "cppreference.com")
- [default comparisons](https://en.cppreference.com/w/cpp/language/default_comparisons "cppreference.com")

