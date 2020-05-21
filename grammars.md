# This page lists the useful C++ grammars, especially for C++11, C++14, C++17 and C++20.

## tuple

​	C++11 introduced tuple, an extension of pair, to simply package several values into a structure.

```c++
tuple<int, double, char> t(1, 2.0, 'a');
// return the reference
get<0>(t) = 2;
cout << get<0>(t) << endl;  // 2

std::tuple<int, double, std::string> f() {
  return std::make_tuple(1, 2.3, "456");
}
auto [x, y, z] = f();  // structured binding (C++17)
```

## noexcept

​	Starting with C++11, we've seen a lot of code with the keyword noexcept. This keyword tells the compiler that no exceptions will occur in the function, which is conducive to the compiler to do more optimization of the program. If the noexcept function throws an exception outward (if the exception isn't caught inside the function and handled), the program terminates directly, calling the std::terminate() function, which internally calls std::abort() to abort the program.

```c++
constexpr initializer_list() noexcept
: _M_array(0), _M_len(0) { }

// It means that if the operation x.swap (y) does not have an exception, then the function swap(Type& x, Type& y) will not have an exception
void swap(Type& x, Type& y) noexcept(noexcept(x.swap(y))) //C++11
{
	x.swap(y);
}
```

Use of noexcept is encouraged in the following situations:

- move constructor
- move assignment
- destructor (default)
- Leaf Function