# This page lists the useful C++ grammars, especially for C++11, C++14, C++17 and C++20.

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