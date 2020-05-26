# This page lists the useful programming skills for better efficiency, preferrably with an illustrating example (最好有代码实例展示).



## SFINAE

SFINAE /s’fi:nei/ is short for “Substitution Failure Is Not An Error”. It is a black magic widely used in C++ template metaprogramming. This feature applies during overload resolution.

In C++, different functions can have the same name. When you call a function, the compiler will maintain a set of functions that have the called name. Overload resolution is the process that selects the fittest function from the set. The compiler will first discard functions which can’t match the given arguments. Here is an example:

```c++
#include <iostream>
#include <type_traits>

struct Foo {};
struct Bar {};

static_assert(!std::is_convertible_v<Foo, Bar> &&
              !std::is_convertible_v<Bar, Foo>);

void func(Foo) { std::cout << "func(Foo) is called." << std::endl; }
void func(Bar) { std::cout << "func(Bar) is called." << std::endl; }

int main() {
  Foo foo;
  func(foo);
}

// output: func(Foo) is called.
```

Though the function `void func(Bar)` can’t match the given argument `foo`, it doesn’t cause a compile error.

If a function in the set is actually a function template, it gets complicated. The compiler has to substitute the template parameters. If the substitution fails, SFINAE rule will be applied and the compiler will simply remove this function template from the set without declaring an error. Here is an example:

```c++
#include <iostream>

struct Foo {};

template <typename Type>
void func(Type, decltype(Type::m_x)) {
  std::cout << "func(Type,decltype(Type::m_x)) is called." << std::endl;
}

void func(Foo, int) { std::cout << "func(Foo,int) is called." << std::endl; }

int main() {
  Foo foo;
  func(foo, 0);
}

// output: func(Foo,int) is called.
```

`Foo` doesn’t have a member variable `m_x`, so after substituting `Type` with `Foo` in the function template `func`, `decltype(Type::m_x)` is invalid. Thus, this substitution fails, but there won’t be a compile error.

We can use SFINAE to add constraints to function templates and make the complier select the right one. In header file `type_traits`, there is a tool called `std::enable_if` and its convenient alias template helper `std::enable_if_t`. It has two template parameters. The first one is a non-type parameter `bool` and the second one is a type parameter(the default is `void`). If the non-type parameter is `true`, `std::enable_if_t` is just the same as the second type parameter, but if it is `false`, `std::enable_if` won’t have the member type `type` and `std::enable_if_t` will cause a substitution failure. Here is an example:

```c++
#include <iostream>
#include <type_traits>

template <typename Type>
auto func(Type) -> std::enable_if_t<std::is_integral_v<Type>> {
  std::cout << "This is the function for integers." << std::endl;
}

template <typename Type>
auto func(Type) -> std::enable_if_t<std::is_floating_point_v<Type>> {
  std::cout << "This is the function for floating numbers." << std::endl;
}

int main() {
  func(1);
  func(1.0);
}

// output:
//   This is the function for integers.
//   This is the function for floating numbers.
```

SFINAE has many applications. Here are some good uses: [C++ SFINAE examples](https://stackoverflow.com/questions/982808/c-sfinae-examples "Stack Overflow").
You can find more information [here](https://en.cppreference.com/w/cpp/language/sfinae "cppreference.com").