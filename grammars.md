# This page lists the useful C++ grammars, especially for C++11, C++14, C++17 and C++20.


## 关键字：decltype

*Author* : Biru Yang    *Date*: 2020.6.24

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


## 条件分支语句初始化

*Author* : Biru Yang    *Date*: 2020.6.24


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


## 聚合初始化

*Author* : Biru Yang    *Date*: 2020.6.24


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


## Concept

**Concepts** in C++ are an extension to templates feature. A concept, associated with a template, provides a constraint to the template, which limits the set of arguments that are accepted as template parameters.ii That is, A concept is a set of requirements that a set of related types) must fulfill to be used correctly in generic algorithm. Template instantiations which don’t follow corresponding concepts will lead to errors when compiling. So concepts feature simplifies compiler diagnostics for failed template instantiations.

```c++
1. concept ChannelConcept<typename T> : EqualityComparable<T>
2. {
3. typename value_type = T; // use channel_traits<T>::value_type to access it
4. where ChannelValueConcept<value_type>;
5. typename reference = T&; // use channel_traits<T>::reference to access it
6. typename pointer = T*; // use channel_traits<T>::pointer to access it
7. typename const_reference = const T&; // use channel_traits<T>::const_reference to acce ss it
8.
typename const_pointer = const T*; // use channel_traits<T>::const_pointer to access it
9. static const bool is_mutable; // use channel_traits<T>::is_mutable to access it
10.
11. static T min_value(); // use channel_traits<T>::min_value to access it
12. static T max_value(); // use channel_traits<T>::min_value to access it
13. };
14.
15. concept MutableChannelConcept<ChannelConcept T> : Swappable<T>, Assignable<T> {};
16.
17. concept ChannelValueConcept<ChannelConcept T> : Regular<T> {};
```

## "auto" in C++11

## auto的原理是根据变量后面的取值，来推测变量的类型
## 使用auto可以简化变量初始化

```C++
    std::vector<std::string> ve;
    std::vector<std::string>::iterator it = ve.begin();
    auto it1 = ve.begin();
```

此外，如果是可用迭代器的对象的话，还可以这样操作：

```C++
    int main() {
        vector<int> v;
        v.push_back(1);v.push_back(2);v.push_back(3);
        for(auto i:v) cout<<i<<" ";
        return 0;
    }
```

auto在这里替代的就是int
