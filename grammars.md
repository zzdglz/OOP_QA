# This page lists the useful C++ grammars, especially for C++11, C++14, C++17 and C++20.

*Author* : Biru Yang    *Date*: 2020.6.24



## 1. 关键字：decltype

***decltype***与我们在课上曾介绍过的关键字***auto***功能较为相似：**类型推断**。

*auto*可以让我们无需指定表达式的类型，直接用其值初始化新变量；

而**decltype**则可以让我们从表达式类型推断出变量类型，而具体初始化的值则可不指定/另外指定。

示例用法如下：

```c++
int function();
const float a = 4.0;
int B = 0, &refB = B, *ptrB = &B;

int main()
{
    int a = 20;
    
    /*用变量:temp_1为const float类型*/
    decltype(a) temp_1 = 4.0;
    
    /*用函数返回值：temp_2为int类型*/
    decltype(function()) temp_2;  //尽管function()并未定义，该程序同样可以运行，这与auto不同
    
    /*用引用：temp_3为引用*/
    decltype(refB) temp_3 = B;
    
    /*用指针：temp_4为int*的指针*/
    decltype(ptrB) temp_4;
    
    return 0;
}
```

**decltype**与**auto**在功能上类似，但具体使用时有以下几点不同：

> 1.  ***auto***忽略顶层***const***，***decltype***保留顶层***const***。
> 2.  对引用操作，***auto***推断出原有类型，***decltype***推断出引用。
> 3.  ***auto***推断时会实际执行，***decltype***只做分析。




## 2. 条件分支语句初始化

往常只能在 ***for*** 语句中进行变量初始化，如今可以在 ***if*** 和 ***switch*** 语句中进行初始化：

```c++
int main()
{
    int num = 2;
    if (int i = 0; i == num) { //if中初始化
        /*do something*/
    }
    switch (int k = 0; k) { //switch中初始化
        case 0: /*do something*/ break;
        default: /*do something else*/ break;
    }
}
```



## 3. 聚合初始化

可使用**嵌套的花括号**对**嵌套的结构体**进行初始化：

```C++
struct Struct1 {
    int a;
    double b;
}

struct Struct2 {
    char c;
    Struct1 s1;
}

int main()
{
    Struct1 st_1{10, 3.14};
    Struct2 st_2{'e',{0, 2.71}};  //嵌套花括号
}
```



### Reference :

+ [C++11新标准学习：decltype关键字](https://www.cnblogs.com/ghbjimmy/p/10636030.html)
+ [C++17新特性个人总结](https://blog.csdn.net/qq811299838/article/details/90371604)