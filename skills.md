# This page lists the useful programming skills for better efficiency, preferrably with an illustrating example (最好有代码实例展示).


## 平方根倒数速算法

*Author* : Biru Yang     *Date*: 2020.6.27

**平方根倒数**指一个数的算术平方根的倒数（32位浮点数），这一计算在图形学中有大量的需求。

平方根倒数速算法最早可能于90年代由SGI发明，但直到2002-03年才在公共论坛上出现。

该算法首先接收一个32位带符号浮点数，然后将其作为32位整数看待，右移后以**魔法数字0x5f3759df**减之，如此使用牛顿迭代法反复跌倒，直至求出符合精确度要求的近似值。

代码如下：

```c++
float fast_reverse( float num )
{
    long i;
    float x, y;
    const float threehalfs = 1.5F;
    
    x = num * 0.5F;
    y = num;
    i = *(long *) &y;
    i = 0x5f3759df - (i >> 1);
    y = * (float *) &i;
    y = y * (threehalfs - (x * y * y));  //first iteration
    //y = y * (threehalfs - (x * y * y));  if necessary, second iteration
    
    return y;
}
```

若将其与以下使用math.h中sqrt()函数的版本相比：

```c++
float func_reverse( float num )
{
    return (1.0/sqrt(num));
}
```

+ **结果正确性** ：对于输入 **3.14159F** ，两者的返回值完全相同，均为 **0.564190** 。

+ **效率** ：

  + 百度百科词条是这样描述该算法的效率的：

    > 在计算浮点数的平方根倒数的同一精度的近似值时，此算法比直接使用浮点数除法要快四倍。
    
  + 但在我本地的编译器条件下，两个算法的时间基本相同（甚至第二个算法略快），运行10^8次后速算法用时0.518s，普通算法用时0.445s。可能是我的测试数据过于单一，在更为多样化的数据条件下也许其优势便会凸显。
---

该算法的更详细介绍（包括**魔法数字**的推导）见下文：[平方根倒数速算法](https://www.cnblogs.com/german-iris/p/5767546.html)

## Minimize the use of if/else branches

If there are are many *else* branches, and the test-condition is very close to the last *else* branch, the CPU may spending lots of time jumping from one *else* to another *else*. If possible, convert to a *switch* statement, then CPU only need to execute one jump with a lookup table.

## Minimize the use of function calls
Function calls require two jumps, and cause the compiler to manipulate stack memory. Consider using inline functions, and using iterations over recursion.

## Use ++i instead of i++ unless you have an explicit reason.
++i have a better efficiency than i++.

```cpp
for(int i = 0; i < 10; ++i)
```

instead of

```cpp
for(int i =  0; i < 10; i++)
```

Because `++i`  needn't call the copy constructor to build a new object `temp`.

`++i` is also faster than `i++` in `iterator` of STL.

because i++ creates a copy of the object, which, when not needed, is suboptimal.

## Use bit operations
When the operation involves powers of two, the bit operation can be used to solve the problem.  
For example, you can use a int as a bool[32].

## inline、const、&
+ Whenever you use a variable that never change, you'd better declare it as a const.
+ And for those function less than 10 lines, declare them as inline can improve the efficiency. 
+ For those large objects, it is costly to copy. So it better to use reference.

## Avoid the use of division
use a * b = c instead of a = c / b because computers are less efficient at division.


## __builtin functions：

这些函数是C标准库中的一些函数，被GCC引入为内置函数。可以快速完成基础的位运算或其他功能，从而大幅优化关键位置效率。

`__builtin_popcount(uint32_t x)`：返回`x`二进制表示中`1`的个数。
`__builtin_ctz(uint32_t x)`：返回`x`二进制中最低位0的个数。注意`x=0`时返回值是未定义的。
`__builtin_clz(x)`：返回`x`二进制中最高位前导0的个数。注意`x=0`时返回值是未定义的。
`__builtin_bswap16(uint16_t x)`：返回16位整数字节顺序翻转的结果
`__builtin_bswap32(uint32_t x)`：返回32位整数字节顺序翻转的结果
`__builtin_bswap64(uint64_t x)`：返回64位整数字节顺序翻转的结果
`__builtin_except(bool x,true/false)`：表示期望这个`bool`表达式的真假，优化编译器的分支预测。
`__builtin_parity(uint32_t x)`：返回`x`的二进制中`1`个数的奇偶性。

**注意**：上述字节顺序翻转是指：以字节为单位将整数看作字符串，然后将这个字符串翻转。而非逐位取反。如`0xabcd -> 0xcdab`，`0x12345678 -> 0x78563412`）

更多请参考：https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html#Other-Builtins

## Multiple conditions in if
When we have a statement like `if (A && B)` and A is false, program will not check B.

Also statement like `if (A || B)` and A is true, program will not check B.

Sometime we may use it to realize some functions.

## unsigned int & int

​	在C/C++语言中，整数存在无符号整数(unsigned int)和有符号整数(int)两种数据类型，虽然表面上这种安排是很合理的：用unsigned int来表示不会小于0的整数(如长度、集合中的元素的枚举关系等等)，用int来表示有可能为负数的整数。但实践证明，这种安排带来的麻烦远远超过了他所带来的收益(让unsigned int 能表示的最大值相较于int提高了一倍)，以至于在之后的高级编程语言中都选择了废弃无符号整数这一数据类型。

​	为了理解这一点，我们首先要了解unsigned int 和 int类型的数据是如何在计算机中存储的。

​	unsigned int的存储是十分简单，由于所有数字都是非负数，所以他们直接以其二进制的表示方式存入计算机中，示例如下：

```c++
	unsigned int a = 10;		//0x0000000a
	unsigned int b = 100;		//0x00000064
	unsigned int c = 100000;	//0x000186a0
```

​	int的存储方式稍显复杂；首先int的最高位被用来做符号位，不能直接用于表示数字的大小；对于非负数的情况，存储方式与unsigned int相同，直接以二进制的表示方式存储；但对于负数，其是以补码的形式存储(对负数的绝对值的二进制取反再加1) 。采用这种方式的主要原因是为了让int之间的四则运算保持一致性，具体证明按下不表，同学们可自行寻找数电/计组教材学习。示例如下：

```c++
	int a = 10;			//0x0000000a
	int b = 100;		//0x00000064
	int c = 100000;		//0x000186a0
	int d = -1			//0xffffffff = ~0x00000001 + 1
	int e = -2000		//0xfffff830 = ~0x000007d0 + 1
```

​	这种存储方式带来的问题是：如果我们将值为负数的int强制转为unsigned int，我们就会得到一个很大的正数；如果我们将值为很大(超过int最大值)的unsigned int强制转为int，我们就会得到一个很小的负数。这往往会在程序内引发许多难以察觉但又会造成严重后果的问题。即便是经验丰富的程序员，也不一定能完全避免这类问题。

它可能导致程序运行错误：

```c++
/* WARNING: This is buggy code */
float sum_elements(float a[], unsigned int length)
{
    int i;
    float result = 0;
    
    for(i = 0; i <= length - 1; i++)
        result += a[i];
    return result;
}
```

这段代码试图计算数组a中所有元素的和，其中元素数量由length给出。但当我们传入length = 0时，代码并没有返回0的结果，而是出现了内存错误，原因就是length是unsigned int类型的，传入0后，length -1的十六进制表示为0xffffffff，但由于它是unsigned int类型，所以被翻译为了一个很大的正数，导致内存访问越界。

它可能导致运行结果错误：

```C++
/* Prototype for library function strlen */
size_t strlen(const char *s);

/* WARNING: This is buggy code */
bool str_longer(char *s, char *t)
{
    return strlen(s) - strlen(t) > 0;
}
```

这段代码试图返回s和t比较长度的结果，但由于strlen的返回类型为size_t(unsigned)，所以strlen(s) - strlen(t)即便为负数，但还是被翻译为了一个正数，进而返回了错误的结果。

它还甚至会让程序出现安全漏洞：

```c++
/* Declaration of library function memcpy */
void *memcpy(void *dest, void *src, size_t n);

/* Kernel memory region holding user-accessible data */
#define KSIZE 1024
char kbuf[KSIZE]
    
/* Copy at most maxlen bytes from kernel region to user buffer */
int copy_from_kernel(void *user_dest, int maxlen)
{
    int len = KSIZE < maxlen ? KSIZE : maxlen;
    memcpy(user_dest, kbuf, len);
    return len;
}
```

​	copy_from_kernel函数的主要功能是将系统内核中的数据复制到用户的缓冲区中，但如果用户是怀有恶意的攻击者，他就会传入maxlen为一个负数值，此时长度len就会以负数的形式传入memcpy中，但由于memcpy的接受类型为size_t(unsigned)，那么实际上在复制的过程中，n就会被翻译为的一个很大的正数，进而会把内核内的许多额外信息复制到用户的缓冲区，尽管不一定能够完全复制出来，但攻击者还是会看到很多其未被授权查看的信息。

由此可见，unsigned int 会带来很多让人意想不到的麻烦，因此，最好的解决方案就是：

#### 尽量避免使用unsigned int这个数据类型！


## 使用nullptr

nullptr是c++11用来表示空指针新引入的常量值，在c++中表示空指针语义时，建议使用nullptr而不要使用NULL，因为NULL本质上是个int型的0，其实不是个指针。

```c++
void func(void *ptr) {
    cout << "func ptr" << endl;
}

void func(int i) {
    cout << "func i" << endl;
}

int main() {
    func(NULL); // 编译失败，会产生二义性
    func(nullptr); // 输出func ptr
    return 0;
}
```

## Loop unrolling
Normal Loop

```c++
 int x;
 for (x = 0; x < 100; x++)
 {
     delete(x);
 }
```
After loop unrolling

```c++
 int x; 
 for (x = 0; x < 100; x += 5 )
 {
     delete(x);
     delete(x + 1);
     delete(x + 2);
     delete(x + 3);
     delete(x + 4);
 }
```
The goal of loop unwinding/unrolling is to increase a program's speed by reducing or eliminating instructions that control the loop. Optimizing compilers will sometimes perform the unrolling automatically, or upon request. But the code may become less readable after loop unrolling.

## Allow small error in accuracy rather than using == operator when comparing two floating-point numbers
As we all know, it is inevitable that error will occur when doing floating-point calculations. So instead of using `if(a==b)`, use `if(fabs(a-b)<EPS)`, where EPS is a very small number, for example 1E-7.

## 数组的多重循环按行遍历
例如下面的程序：
```c++
#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;
int main()
{
	const int MAX_ROW = 2000;
	const int MAX_COL = 2000;
	int(*a)[MAX_COL] = new int[MAX_ROW][MAX_COL];
	clock_t start, finish;

	//先行后列
	start = clock();
	for (int i = 0; i<MAX_ROW; i++)
	for (int j = 0; j<MAX_COL; j++)
		a[i][j] = 1;
	finish = clock();
	//totaltime=(double)()/CLOCKS_PER_SEC;
	cout << "先行后列遍历时间为：" << finish - start << "ms" << endl;
	//先列后行
	start = clock();
	for (int i = 0; i<MAX_COL; i++)
	for (int j = 0; j<MAX_ROW; j++)
		a[j][i] = 1;
	finish = clock();
	//totaltime=(double)()/CLOCKS_PER_SEC;
	cout << "先列后行遍历时间为：" << finish - start << "ms" << endl;

	return 0;
}
```
这个程序的结果为：11ms，20ms
由于行遍历的连续性，按行遍历可以快速找到下一个内存的指针，从而效率更高。

