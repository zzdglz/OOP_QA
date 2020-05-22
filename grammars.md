# This page lists the useful C++ grammars, especially for C++11, C++14, C++17 and C++20.

## Auto in C++17

The deduction range of auto is expanded in C++17. You can use it as:

```c++
std::tuple<int,double,std::string> f() {
    return std::make_tuple(1,4.3,"abc");
}
auto [x,y,z] = f(); // x,y,z are individually deducted as int,double,std::string
```

Before we cannot do that.