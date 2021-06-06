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

## Duff's device
在计算机科学领域，达夫设备（英文：Duff's device）是串行复制（serial copy）的一种优化实现，通过汇编语言编程时一常用方法，实现展开循环，进而提高执行效率。
原理上，在编程时，循环展开注重于利用批量处理，减少总处理分支数。而在串行复制数据时，当总循环次数无法被展开后循环的增量整除时，一般就用直接跳转到展开后循环体中部的方式，完成剩余数据的复制流程。
因此，根据循环展开的思想，针对串行复制数据的需要，以每次迭代时赋最多8个值的方式，用C语言写出了一个优化实现，成功优化了串行复制的效率。
例如：
send(to, from, count)
register short *to, *from;
register count;
{
	register n = (count + 7) / 8;
	switch (count % 8) {
	case 0:	do { *to = *from++;
	case 7:		 *to = *from++;
	case 6:		 *to = *from++;
	case 5:		 *to = *from++;
	case 4:	     *to = *from++;
	case 3:      *to = *from++;
	case 2:      *to = *from++;
	case 1:      *to = *from++;
	        } while (--n > 0);
	}
}
从速度上说，由于采用了循环展开技巧，使所需处理的分支数减少，从而降低了在处理分支时，中断与刷新流水线的巨大运算开销，因而相较于简单、直接的循环代码，这段代码的执行效率较高。
另外，由代码易知，若不带switch语句，则这段代码只能复制8*n个数据项，而若count无法为8整除，则仍有count%8（即count除于8的余数）项未处理；有鉴于此，此间嵌入了switch/case语句，负责处理剩余数据。
reference：https://zh.wikipedia.org/wiki/%E8%BE%BE%E5%A4%AB%E8%AE%BE%E5%A4%87
---------------------------