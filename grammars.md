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

### 