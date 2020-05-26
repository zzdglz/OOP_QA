# This page lists the useful C++ grammars, especially for C++11, C++14, C++17 and C++20.

## Zero Initialization

For fundamental types such as int, double, or pointer types, there is no default constructor that initializes them with a useful default value. Instead, any noninitialized local variable has an undefined value:

'''cpp

void foo() {
  int x;    // x has undefined value
  int* ptr; // ptr points to anywhere
}

'''

Then the following code is undefined if T is a fundamental type:

'''cpp

#include<iostream>
template<typename T>
void foo() {
  T x;
  std::cout<<x<<std::endl; // x is undefined
}

'''

C++ introduces the following mechanism to call explicitly a default constructor for built-in types that initializes them with zero (or false, nullptr). As a consequence, you can ensure proper initialization even for built-in types by writing:

'''cpp

template<typename T>
void foo() {
  T x{}; // x is zero/false/nullptr
}

template<typename T>
void bar(T p = T{}) { // the default value of p is not undefined
  ...
}

'''