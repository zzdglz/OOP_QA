# This page lists the useful programming skills for better efficiency, preferrably with an illustrating example (最好有代码实例展示).



## Logging with variadic function

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



## Detect Current Platform

You can rely on preprocessor to detect the current platform.

```c++
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
   //define something for Windows (32-bit and 64-bit, this part is common)
   #ifdef _WIN64
      //define something for Windows (64-bit only)
   #else
      //define something for Windows (32-bit only)
   #endif
#elif __APPLE__
    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR
         // iOS Simulator
    #elif TARGET_OS_IPHONE
        // iOS device
    #elif TARGET_OS_MAC
        // Other kinds of Mac OS
    #else
    #   error "Unknown Apple platform"
    #endif
#elif __linux__
    // linux
#elif __unix__ // all unices not caught above
    // Unix
#elif defined(_POSIX_VERSION)
    // POSIX
#else
#   error "Unknown compiler"
#endif
```

