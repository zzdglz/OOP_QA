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



## Filesystem Library (C++17)

The Filesystem library provides facilities for performing operations on file systems and their components. It's based on Boost::filesystem and finally merged into ISO C++. 

#### Path

First we need to get familiar with `path` class. This class is very easy to understand. Here is an example. (This example is under Mac OS, output under Windows maybe a little different)

```c++
#include <iostream>
#include <filesystem>
using namespace std;

int main() {
  filesystem::path mypath("/Users/FallDream/OOP_QA/skills.md");
  cout << "exists() = " << filesystem::exists(mypath) << "\n"
       << "root_name() = " << mypath.root_name() << "\n"
       << "root_path() = " << mypath.root_path() << "\n"
       << "relative_path() = " << mypath.relative_path() << "\n"
       << "parent_path() = " << mypath.parent_path() << "\n"
       << "parent_path().parent_path() = " << mypath.parent_path().parent_path() << "\n"
       << "filename() = " << mypath.filename() << "\n"
       << "stem() = " << mypath.stem() << "\n"
       << "extension() = " << mypath.extension() << "\n";
  for (auto& part : mypath) {
    cout << part << "\n";
  }
  return 0;
}
```

The output is like:

```
exists() = 1
root_name() = ""
root_path() = "/"
relative_path() = "Users/FallDream/OOP_QA/skills.md"
parent_path() = "/Users/FallDream/OOP_QA"
parent_path().parent_path() = "/Users/FallDream"
filename() = "skills.md"
stem() = "skills"
extension() = ".md"
"/"
"Users"
"FallDream"
"OOP_QA"
"skills.md"
```

You can use `/=` to concatenate two paths with a directory separator`/` and '+=' to only add a string.

```c++
mypath = "/Users/FallDream/"
mypath += "OOP_QA";  // "/Users/FallDream/OOP_QA"
mypath /= "skills.md";  // "/Users/FallDream/OOP_QA/skills.md"
```

#### Judge the type of a Path

Use `filesystem::status` to get the status of a path, and then judge its type.

```c++
void demo_status(const filesystem::path& p)
{
    std::cout << p;
    filesystem::file_status s = filesystem::status(p);
    if(filesystem::is_regular_file(s)) std::cout << " is a regular file\n";
    if(filesystem::is_directory(s)) std::cout << " is a directory\n";
    if(filesystem::is_block_file(s)) std::cout << " is a block device\n";
    if(filesystem::is_character_file(s)) std::cout << " is a character device\n";
    if(filesystem::is_fifo(s)) std::cout << " is a named IPC pipe\n";
    if(filesystem::is_socket(s)) std::cout << " is a named IPC socket\n";
    if(filesystem::is_symlink(s)) std::cout << " is a symlink\n";
    if(!filesystem::exists(s)) std::cout << " does not exist\n";
}
```

####  Go through all files under a directory

Use `filesystem::directory_iterator`.

```c++
filesystem::path mypath("/Users/FallDream/OOP_QA");
filesystem::directory_iterator list(mypath);
for (auto& i: list) {
  cout << i.path().filename() << "\n";
}
```

#### Other file operations

This library provides many useful functions that can be used to manage your files and directories. You can create, copy, rename or remove a file, get the lastest modification time, or create links.

For more information, see [cppreference](https://en.cppreference.com/w/cpp/filesystem).