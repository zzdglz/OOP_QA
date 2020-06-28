#Google Coding Style
**Author**:  2019011298 马子坤

## 1.About Header Files
Generally, each cpp file has a coordinated header file.

A header file should be protected by `#define` to avoid multiple including.

It is to be discussed whether to use `#pragma once`.

The sequences of `#include`: C libraries, C++ libraries, headers from other libraries and then your own headers.


## 2.About Classes
Use `struct` only when there are only data members, use `class` otherwise.

Inheritance should be `public` and multiple inheritance should be avoided most of the time.

Try not to use operator overload.

Member variables should be privatized.

Members of a class are supposed to be declared in the following order:

+ First `public`, then `protected`, and `private` last.
+ enums and typedefs
+ static const
+ constructor
+ destructor
+ member functions
+ overriden functions
+ member variables

## 3.About Functions
Avoid using global functions.

Write functions less than `40` lines.

Inline functions should be less than `10` lines.

Declare a function as `const` if possible.

## 4.About Variables
Follow Camel-Case for variable naming, e.g. `myVariable`.

Add a `_` in the front of member variables, e.g. `_myVar`.

If parameters are passed by reference, declare it as `const`.

Use fewer global variables.

Use all upper cases for constants and use `_` between words.

##5.Else
Use `spaces` instead of tabs, `2` spaces each time.

Minimize use of vertical whitespace.

Keep your coding style consistent.

##References
https://google.github.io/styleguide/cppguide.html
