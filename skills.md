# This page lists the useful programming skills for better efficiency, preferrably with an illustrating example (最好有代码实例展示).



##Logging with variadic function

A variadic function can accept variant numbers of parameters, it enables you to log any number of data as you wish.

You can define a variadic logging function like this:

```c++
#include <stdarg.h>
void PrintLog(const char* Format, ...) {
 	va_list args;  //NULL pointer now
  va_start(args, Format); //use va_start to point at the first variable
  //va_arg(args, char); you can use this function to point at next parameter with specific type
  vprintf(Format, args); // = printf(Format, ...)
  // you can add some other information, e.g. time, environment
  va_end(args);
}
```

This function can be used as `printf`.