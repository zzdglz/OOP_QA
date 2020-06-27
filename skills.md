# This page lists the useful programming skills for better efficiency, preferrably with an illustrating example (最好有代码实例展示).

*Author* : Biru Yang     *Date*: 2020.6.27



## 平方根倒数速算法

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