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

## Minimalize the use of if/else branches

If there are are many *else* branches, and the test-condition is very close to the last *else* branch, the CPU may spending lots of time jumping from one *else* to another *else*. If possible, convert to a *switch* statement, then CPU only need to execute one jump with a lookup table.

## Use ++i instead of i++ except that you have a reason todo that.
++i have a better efficiency than i++.

>for(int i = 0; i < 10; ++i)

instead of

>for(int i =  0; i < 10; i++)

## Use bit operations
When the operation involves powers of two, the bit operation can be used to solve the problem.  
For example, you can use a int as a bool[32].

## inline、const、&
+ Whenever you use a variable that never change, you'd better declare it as a const.
+ And for those function less than 10 lines, declare them as inline can improve the efficiency. 
+ For those large objects, it is costly to copy. So it better to use reference.

## Decline the use of division
use a * b = c instead of a = c / b because computers are less efficient at division.

## 快速乘

当在C++中进行这种计算时可能因为不正确的结果：long long * long long % long long.

即int64与int64相乘的结果对int64取模，如果直接进行的话，有可能会因为溢出而得到错误的结果。在这种情况下，有一种比较简单但是速度比较慢的方法：（假设模数小于LLONG_MAX/2，否则在unsigned long long下运算即可)

```C++
long long mul(long long a,long long b,long long P)
{
    long long ret=0;
    for(;b;b>>=1,a=(a+a)%P)
        if(b&1)
            ret=(ret+b)%P;
    return ret;       
}
```

这个方法利用了快速幂的思想，单次的时间复杂度为$O(\log_2 b)$。

但实际上，有更加快速的方法，其代码为：

```C++
long long fast_mul(long long x,long long y,long long p)
{
	long long z=(long double)x/p*y;
	long long res=(unsigned long long)x*y-(unsigned long long)z*p;
	return (res+p)%p;
}
```

这份代码中，利用了$xy \bmod P=xy-\lceil \frac{xy}{P}\rceil *P$这个公式。

虽然在第四行有可能出现溢出的情况，但由于是unsigned long long的自然溢出，因此可以保证它们的差值是正确的。

这种方法的复杂度为$O(1)$。