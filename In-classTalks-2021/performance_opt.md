# Performance Optimization

Author: 任自厚 RenZihou 2020012366 ([My GitHub Homepage](https://github.com/RenZihou))

This document is based on my in-class presentation.

***

## Technics

**Locality**

* example code:

```cpp
#include <iostream>
#include <chrono>

const int n = 5000;
int matrix[n][n];
int array[n * n];

int sum_by_row() {
    int result = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result += matrix[i][j];
        }
    }
    return result;
}

int sum_by_col() {
    int result = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result += matrix[j][i];
        }
    }
    return result;
}

int sum_array() {
    int result = 0;
    int nn = n * n;
    for (int i = 0; i < nn; ++i) {
        result += array[i];
    }
    return result;
}

int main() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = rand() % 10;
            array[i * n + j] = rand() % 10;
        }
    }

    auto start = std::chrono::system_clock::now();
    sum_by_row();
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> dur = end - start;
    std::cout << "sum by row: " << dur.count() << std::endl;

    start = std::chrono::system_clock::now();
    sum_by_col();
    end = std::chrono::system_clock::now();
    dur = end - start;
    std::cout << "sum by column: " << dur.count() << std::endl;

    start = std::chrono::system_clock::now();
    sum_array();
    end = std::chrono::system_clock::now();
    dur = end - start;
    std::cout << "sum array: " << dur.count() << std::endl;

    return 0;
}

// OUTPUTS:
// sum by row: 0.0601728
// sum by column: 0.0844137
// sum array: 0.0493367
```

**Loop Unrolling**

* example code:

```cpp
#include <iostream>
#include <chrono>

int main() {
    const int n = 60000000;

    int a = 0;
    auto start = std::chrono::system_clock::now();
    for (int i = 0; i < n; ++i) a += i;
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> dur = end - start;
    std::cout << "no_unrolling: " << dur.count() << std::endl;

    a = 0;
    start = std::chrono::system_clock::now();
    for (int i = 0; i < n; i += 2) {
        a += i;
        a += (i + 1);
    }
    end = std::chrono::system_clock::now();
    dur = end - start;
    std::cout << "unrolling: " << dur.count() << std::endl;

    return 0;
}

// OUTPUTS:
// no_unrolling: 0.219984
// unrolling: 0.104434
```

## Optimization Flags

Let the compiler to do all the stuffs above for you!

### Brief Introduction

> Without any optimization option, the compiler’s goal is to reduce the cost of compilation and to make debugging produce the expected results.
>
> Turning on optimization flags makes the compiler attempt to improve the performance and/or code size at the expense of compilation time and possibly the ability to debug the program.

**-O0**: Reduce compilation time and make debugging produce the expected results. This is the default.

**-O(1)**: Optimize. With -O, the compiler tries to reduce code size and execution time, without performing any optimizations that take a great deal of compilation time.

**-O2**: Optimize even more. GCC performs nearly all supported optimizations that do not involve a space-speed tradeoff.

**-O3**: Optimize yet more.

**-Ofast**: Disregard strict standards compliance. -Ofast enables all -O3 optimizations. It also enables optimizations that are not valid for all standard-compliant programs.

**-Os**: Optimize for size. -Os enables all -O2 optimizations except those that often increase code size.

**-Og**: Optimize debugging experience.

### Examples

**Dead Code Elimination**

Perform dead code elimination (DCE) on RTL. Enabled by default at -O and higher.

* flag: `-dce`

* example code:

```cpp
int foo(int a) {
    int b = 0;
    if (b) a += 1;  // dead code (never execute)
    return a;
}
```

without optimization:

```
_Z3fooi:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -20(%rbp)
	movl	$0, -4(%rbp)
	cmpl	$0, -4(%rbp)
	je	.L2  // the if statement is compiled
	addl	$1, -20(%rbp)
```

with optimization:

```
_Z3fooi:
.LFB0:
	.cfi_startproc
	endbr64
	movl	%edi, %eax
	ret  // no if statement compiled
	.cfi_endproc
```

**Inline Functions**

Consider all functions for inlining, even if they are not declared inline. The compiler heuristically decides which functions are worth integrating in this way. Enabled at levels -O2, -O3, -Os. Also enabled by -fprofile-use and -fauto-profile.

* flag: `-finline-functions`

* example code:

```cpp
int bar(int x) { return x + 3; }  // simple functions can be inlined automaticlly

int foo(int x) {
    int b = bar(x);
    return b;
}
```

without optimization:

```
_Z3fooi:
.LFB1:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$24, %rsp
	movl	%edi, -20(%rbp)
	movl	-20(%rbp), %eax
	movl	%eax, %edi
	call	_Z3bari  // calls the bar function
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
```

with optimization:

```
_Z3fooi:
.LFB1:
	.cfi_startproc
	endbr64
	leal	3(%rdi), %eax
	ret  // inlines bar function
	.cfi_endproc
```

**Merge Constant**

Attempt to merge identical constants (string constants and floating-point constants) across compilation units.

Enabled at levels -O, -O2, -O3, -Os.

* flag: `-fmerge-constants`

* example code:

```cpp
int foo(float x) {
    const float a = x, b = x;  // a and b are same constant
    printf("%f", b);
    return a + 1;
}
```

without optimization:

```
_Z3foof:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movss	%xmm0, -20(%rbp)
	movss	-20(%rbp), %xmm0
	movss	%xmm0, -8(%rbp)
	movss	-20(%rbp), %xmm0  // defines two constant
	movss	%xmm0, -4(%rbp)
	cvtss2sd	-4(%rbp), %xmm0
	leaq	.LC0(%rip), %rdi
	movl	$1, %eax
	call	printf@PLT
	movss	-8(%rbp), %xmm1
	movss	.LC1(%rip), %xmm0
	addss	%xmm1, %xmm0
	cvttss2sil	%xmm0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
```

with optimization:

```
_Z3foof:
.LFB30:
	.cfi_startproc
	endbr64
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movss	%xmm0, 12(%rsp)  // only define one constant
	cvtss2sd	%xmm0, %xmm0
	leaq	.LC0(%rip), %rsi
	movl	$1, %edi
	movl	$1, %eax
	call	__printf_chk@PLT
	movss	12(%rsp), %xmm0
	addss	.LC1(%rip), %xmm0
	cvttss2sil	%xmm0, %eax
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
```

## Outer Links (References)

[gcc document (optimize-options)](https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html)

[Root Lee's blog on locality](http://irootlee.com/juicer_locality/)

[Root Lee's blog on loop unrolling](http://irootlee.com/juicer_loop_unrolling/)
