# This page lists the useful C++ grammars, especially for C++11, C++14, C++17 and C++20.

## Zero Initialization

For fundamental types such as int, double, or pointer types, there is no default constructor that initializes them with a useful default value. Instead, any noninitialized local variable has an undefined value:

```cpp

void foo() {
  int x;    // x has undefined value
  int* ptr; // ptr points to anywhere
}

```

Then the following code is undefined if T is a fundamental type:

```cpp

#include<iostream>
template<typename T>
void foo() {
  T x;
  std::cout<<x<<std::endl; // x is undefined
}

```

C++ introduces the following mechanism to call explicitly a default constructor for built-in types that initializes them with zero (or false, nullptr). As a consequence, you can ensure proper initialization even for built-in types by writing:

```cpp

template<typename T>
void foo() {
  T x{}; // x is zero/false/nullptr
}

template<typename T>
void bar(T p = T{}) { // the default value of p is not undefined
  ...
}

```

## Argument-Dependent Lookup

ADL applies primarily to unqualified names that look like they name a nonmember function ina function call or operator invocation. ADL does not happen if ordinary look up finds

- the name of a member function
- the name of a variable
- the name of a type
- the name of a block-scope function declaration

ADL is also inhibited if the name of the function to be called is enclosed in parentheses.

Otherwise, if the name if followed by a list of argument expressions enclosed in parentheses, ADL proceeds by looking up the name in namespaces and classes associated with the types of the call arguments, ie. assoceated namespaces and associated classes:

- for built-in types, this is the empty set
- for pointer and array types -> of the underlying type
- for enumeration types, the namespace in which the enumeration is declared
- for class members, the enclosing class
- for class types, itself, the enclosing class, and base classes
- for template classes, add that of the template parameters
- for function types, add that of the parameter types and return type

example:

```cpp

#include<iostream>

namespace X {
  template<typename T> void f(T);
}

namespace N {
  using namespace X;
  enum E {e1};
  void f(E) {
    std::cout << "N::f(N::E) called\n";
  }
}

void f(int) {
  std::cout << "::f(int) called\n";
}

int main() {
  ::f(N::e1); // qualified function name: no ADL
  f(N::e1);   // ordinary lookup finds ::f() and ADL finds N::f(), the latter is preferred
}

```

## Reference Qualifier

C++ introduces a new feature called reference qualifier to constrain member functions to be used only when the class is a lvalue or a rvalue.

Example 1

```cpp

class Widget {
  public:
  void doWork() &;  // called when *this is a glvalue
  void doWork() &&; // called when *this is a prvalue
}

Widget makeWidget();
Widget w;

w.doWork();            // w is a lvalue, calls the glvalue version
makeWidget().doWork(); // makeWidget() is a prvalue, calls the prvalue version

```

Example 2

```cpp

#include <iostream>

class W {
 public:
  void f() & { std::cout << "f() & called.\n"; }
  void f() && { std::cout << "f() && called.\n"; }
};

int main() {
  W w1;
  W w2 = std::move(w1);
  w2.f();  // calls f() & because w2 is an xvalue
}

```
