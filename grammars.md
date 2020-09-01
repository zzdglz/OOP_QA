# This page lists the useful C++ grammars, especially for C++11, C++14, C++17 and C++20.

## 1. Concept

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

## 2. "auto" in C++11

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
