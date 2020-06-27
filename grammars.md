# This page lists the useful C++ grammars, especially for C++11, C++14, C++17 and C++20.

## `decltype` in C++11

Just like its name "declared type", it is an operator that can check the declared type of an expression. 

Unlike `auto`, `decltype` can distinguish `const` varaible and reference. Besides, it won't execute the expression. It will just infer the type.

```cpp
int func();

int main()
{
    int var = 2;
    
    decltype(var) type1;  // type1 is int
    decltype(func()) type2;  // func is not defined, but decltype just analyze the type, won't execute the function

    return 0;
}
```