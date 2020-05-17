# This page lists the useful C++ grammars, especially for C++11, C++14, C++17 and C++20.

## 1. If Statement with Initializer (since C++17)

Add an initializer to the *if* statement. It allows you to declare arrays and arbitrary many variables in the *if* statement itself, and ensures that they don't leak out of the *if* scope.

Grammar: 

```c++
if (init-statement condition) {
    // Do something when condition is true
} else {
    // Do something when condition is false
}
```

Example:

```c++
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
  srand(time(NULL));
  if (int number = rand(); number % 2 == 0) {
    std::cout << number << " is an even number" << std::endl;
  } else {
    std::cout << number << " is an odd number" << std::endl;
  }
  return 0;
}
```

