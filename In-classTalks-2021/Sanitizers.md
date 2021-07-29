# Sanitizers

## Introduction

[Sanitizers](https://github.com/google/sanitizers) is an open source tool set initiated by Google, including AddressSanitizer, MemorySanitizer, ThreadSanitizer, LeakSanitizer, Sanitizers is a part of LLVM, but GNU add it into GCC compiler as well.

## Address_Sanitizer

[AddressSanitizer](https://hub.fastgit.org/google/sanitizers/wiki/AddressSanitizer) (aka ASan) is a memory error detector for C/C++.

This tool is very fast. The average slowdown of the instrumented program is ~2x.

It is much better and faster than valgrind.

## Using AddressSanitizer

- Compile your program with option `-fsanitize=address`

  else you can compile it with option `-fno-omit-frame-pointer` to get nicer stack traces in error messages.

- To get a reasonable performance add `-O1` or higher. 

There is an example.

```cpp
#include<cstdio>

int main(){
	int a[2] = {0, 0};
	int b = a[2];
	return 0;
} //test.cpp
```

Compile it with the option `g++ % -o %< -fsanitize=address`.

Now, run the executable `./test` . [AddressSanitizerCallStack](https://hub.fastgit.org/google/sanitizers/wiki/AddressSanitizerCallStack) page describes the memory error.

```bash
==36018==ERROR: AddressSanitizer: stack-buffer-overflow on address 0x7ffd68ea0d48 at pc 0x55b6ea6a831c bp 0x7ffd68ea0d00 sp 0x7ffd68ea0cf0
READ of size 4 at 0x7ffd68ea0d48 thread T0
    #0 0x55b6ea6a831b in main (/home/zjp-shadow/test+0x131b)
    #1 0x7f9b28dd70b2 in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x270b2)
    #2 0x55b6ea6a812d in _start (/home/zjp-shadow/test+0x112d)

Address 0x7ffd68ea0d48 is located in stack of thread T0 at offset 40 in frame
    #0 0x55b6ea6a81f8 in main (/home/zjp-shadow/test+0x11f8)

  This frame has 1 object(s):
    [32, 40) 'a' (line 4) <== Memory access at offset 40 overflows this variable
HINT: this may be a false positive if your program uses some custom stack unwind mechanism, swapcontext or vfork
      (longjmp and C++ exceptions *are* supported)
SUMMARY: AddressSanitizer: stack-buffer-overflow (/home/zjp-shadow/test+0x131b) in main

......
```

The information will tell you the type of error(*stack-buffer-overflow*) and the position in the program(*[32, 40) 'a' (line 4)*), so you could debug the program easily with the tool.

## Some types of error

 AddressSanitizer finds:

- [Use after free](https://hub.fastgit.org/google/sanitizers/wiki/AddressSanitizerExampleUseAfterFree) (dangling pointer dereference)
- [Heap buffer overflow](https://hub.fastgit.org/google/sanitizers/wiki/AddressSanitizerExampleHeapOutOfBounds)
- [Stack buffer overflow](https://hub.fastgit.org/google/sanitizers/wiki/AddressSanitizerExampleStackOutOfBounds)
- [Global buffer overflow](https://hub.fastgit.org/google/sanitizers/wiki/AddressSanitizerExampleGlobalOutOfBounds)
- [Use after return](https://hub.fastgit.org/google/sanitizers/wiki/AddressSanitizerExampleUseAfterReturn)
- [Use after scope](https://hub.fastgit.org/google/sanitizers/wiki/AddressSanitizerExampleUseAfterScope)
- [Initialization order bugs](https://hub.fastgit.org/google/sanitizers/wiki/AddressSanitizerInitializationOrderFiasco)
- [Memory leaks](https://hub.fastgit.org/google/sanitizers/wiki/AddressSanitizerLeakSanitizer)

They are easily understood through their name and the links give the examples as well.

### Set Whitelist

Sometimes we need:

- ignore a correct function to improve the speed
- ignore a function with specific features
- ignore a known problem

In these situations, we need set a whitelist to let the sanitizers ignore them.

----

- Use attribute `no_sanitize_address` (supported by `Clang3.3/GCC4.8` or higher versions)

  Define the macro command as follows

  ```cpp
  #if defined(__clang__) || defined (__GNUC__)
  # define ATTRIBUTE_NO_SANITIZE_ADDRESS __attribute__((no_sanitize_address))
  #else
  # define ATTRIBUTE_NO_SANITIZE_ADDRESS
  #endif
  ```

- therefore we will ignore the function with definition`ATTRIBUTE_NO_SANITIZE_ADDRESS`

  ```cpp
  ATTRIBUTE_NO_SANITIZE_ADDRESS
  void func(){
      int a[2] = {0, 0};
      int b = a[2];
  }
  ```

## Some Extentions

it can interact with other tools, such as gdb(see [AddressSanitizerAndDebugger](https://hub.fastgit.org/google/sanitizers/wiki/AddressSanitizerAndDebugger)), ulimit -v, Flags, Call Stack ...

## Some common questions and answers

- Q: Can [AddressSanitizer](https://hub.fastgit.org/google/sanitizers/wiki/AddressSanitizer) continue running after reporting first error?
- A: Yes it can, AddressSanitizer has recently got continue-after-error mode. This is somewhat experimental so may not yet be as reliable as default setting (and not as timely supported). Also keep in mind that errors after the first one may actually be spurious. To enable continue-after-error, compile with `-fsanitize-recover=address` and then run your code with `ASAN_OPTIONS=halt_on_error=0`.

- Q: Why didn't ASan report an obviously invalid memory access in my code?
- A: If your errors is too obvious, compiler might have already optimized it out by the time Asan runs.

## Referrences

•[Sanitizers(github)](https://github.com/google/sanitizers)

•[AddressSanitizer使用介绍](https://www.bynav.com/cn/resource/bywork/healthy-work/70.html?id=35)

•[Address Sanitizer](https://www.jianshu.com/p/3a2df9b7c353)

•[AddressSanitizer vs Valgrind](https://stackoverflow.com/questions/47251533/memory-address-sanitizer-vs-valgrind)

