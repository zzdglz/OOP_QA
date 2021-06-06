上传_gcs

### Google Coding Style 简介

### 0. 背景和总述

Google经常接受来自其他代码贡献者的代码. 但是如果这些代码的编程风格与 Google 的不一致, 会给代码阅读者造成不小的困扰. Google 因此发布了这份**自己的**编程风格指南, 使所有提交代码的人都能获知 Google 的编程风格. 

不同开发团队发布了不同的指南/标准, 例如[Clang-Format所支持的几种编码风格](https://clang.llvm.org/docs/ClangFormatStyleOptions.html). 

“风格”可能有些用词不当. 这份指南给出了远远多于如何格式化文档的规范: 

- 例如, 因为可能导致的一些问题, 限制甚至禁止了对某些特性(例如, 异常)的使用. 

- 由很多具体琐碎的规则构成, 所以会非常无聊. (老强迫症或许会感觉是令人愉悦的技能?)

此外, 这份指南并不包含一份C++的教程. 假定读者已经对 C++ 非常熟悉. 

> 但明显地, 我在准备这次pre时对C++的了解相当有限, 因此只从整个指南中挑选出自己比较理解(因此可以期望几乎所有听众能够理解)的很少一部分来讲述. 

### 1. 头文件

头文件应当做到Self-contained, 即可以作为第一个头文件被引入. 

必须使用 `#define` 防止多重包含, 例如

```cpp
#ifndef FOO_BAR_BAZ_H_
#define FOO_BAR_BAZ_H_
...
#endif // FOO_BAR_BAZ_H_
```

头文件的命名应当使用全路径, 例如`foo/src/bar/baz.h`. 

- 避免快捷目录`.`和`..`. 

包含路径顺序: 大体上, 想要先看到来自哪里的报错就将什么前置. 例子: 

```cpp
#include "foo/public/fooserver.h" // 优先位置

#include <sys/types.h>
#include <unistd.h>

#include <hash_map>
#include <vector>

#include "base/basictypes.h"
#include "base/commandlineflags.h"
#include "foo/public/bar.h"
```

详见参考文献. 

### 2. 作用域

鼓励在.cpp 文件内使用匿名命名空间或 static 声明. 
- 注意, 不要在头文件中这么做. 

不应该使用 using 指示引入整个命名空间的标识符. 这会污染命名空间. 

将局部变量置于尽可能小的作用域内, 并在定义时初始化. 例子: 

```cpp
int i;
i = f(); // 坏——初始化和声明分离
int j = g(); // 好——初始化时声明
```

### 3. 函数

函数应当短小, 紧凑, 功能单一. 如果函数超过 40 行, 可以思索一下能不能在不影响程序结构的前提下对其进行分割. 

参数顺序为: 输入参数(不需要修改的参数. 对这种参数应当传值或者传常量引用)在先, 后跟输出参数(指望用函数来修改的参数, 通常是引用). 例子: 

```cpp
void Foo(const string &in, string *out);
```

首选返回*值*, 其次是返回引用. 再次才是返回指针. 

函数重载应当让读者一看调用点就胸有成竹. 

- 在想要重载时可以试着在函数名中加入参数信息(而不是一口气构造数个重载), 例如 `AppendString()`. 

### 4. 命名

通用的原则: 要有描述性; 少用缩写. 

广为人知的缩写是允许的, 例如用 `i` 表示迭代变量和用 `T` 表示模板参数. 

文件命名: 全部小写, 可以包含 `_` 或 `-` . 例如`my_useful_class.cc` 以及 `myusefulclass.cc`. 

类型命名: 每个单词首字母大写, 不包含下划线. 例如 `MyExcitingClass`. 

变量命名: 一律小写, 单词之间用下划线连接. 类成员变量以下划线结尾. 例如 `a_local_variable` 以及 `a_class_data_member`. 

常量命名: 以 `k` 开头, 大小写混合. 

- 这对于静态储存类型之外的变量是可选的. 

函数命名

- 常规函数使用大小写混合(即驼峰命名法). 

- 取值和设值函数则要求与变量名匹配, 例如`MyExcitingFunction()` ,` set_my_exciting_member_variable()`. 

### 5. 注释

注释虽然写起来很痛苦, 但对保证代码可读性至关重要. 

用 `//` 还是 `/* … */` ? 保持统一! 

文件注释通常是必要的, 包含版权公告和对内容的(简短)说明. 例如![image-20210606002504899](C:\Users\Jeff\Desktop\OOP_QA\In-classTalks-2021\1.png)

类注释: 每个类的定义都要附带一份注释, 描述类的功能和用法, 除非它的功能相当明显.

函数注释: 在声明处描述功能, 定义处描述实现. 这是程序设计通用的原则之一. 

实现注释: 对于代码中巧妙的, 晦涩的, 有趣的, 重要的地方加以注释. 

不要写毫无必要的注释! 自文档化的代码根本就不需要注释.

比较下述两串代码: 

```cpp
// Find the element in the vector.  <-- 差: 这太明显了!
auto iter = std::find(v.begin(), v.end(), element);
if (iter != v.end()) {
  Process(element);
}
// 以及
// Process "element" unless it was already processed.
auto iter = std::find(v.begin(), v.end(), element);
if (iter != v.end()) {
  Process(element);
}
```

高下立判. 

### 6. 格式

循环和开关选择语句: `switch`语句可以使用大括号分段, 以表明 cases 之间不是连在一起的. 空循环体应使用 `{}` 或 `continue.` 例子: 

```cpp
while (condition) continue;  // 可 - contunue 表明没有逻辑.
```

指针和引用: 句点和箭头前后没有空格; 解引用与取址运算符之后没有空格. 定义时左邻还是右邻? 保持统一! 例子: 

```cpp
const string &str;
x = *p;
p = &x;
x = r.y;
x = r->y;
```

类格式, 命名空间, 预处理命令, 水平留白, 垂直留白……: 过于琐碎(但也许重要), 参考源文档. 

### 7. 其他

对迭代器和模板类型, 使用前置自增, 自减(而非后置). (在代码效率上有差别)

使用宏时要非常谨慎, 尽量以内联函数, 枚举和常量代替之. 

对于局部变量, 用 `auto` 绕过繁琐的类型名. 

内联函数: 

- 不超过10行才将其定义为inline. 

- 谨慎对待析构函数. 

- 不要内联循环/switch. 

来自Google的奇技: 智能指针和Cpplint(略)

### 8. 结语

特例和变通存在, 限于篇幅这里不做介绍. 

注意, 这份指南是一个合理规则的集合. 比较重要的是, "**运用常识和判断力,并且保持一致**". 

风格指南的重点在于提供一个通用的编程规范, 这样大家可以把精力集中在实现内容而不是表现形式上. 希望大家都能写出*诗一样优雅*的代码!

![image-20210606003816435](C:\Users\Jeff\Desktop\OOP_QA\In-classTalks-2021\2.png)

### 参考

(也许是本文档最重要的价值)[https://zh-google-styleguide.readthedocs.io/en/latest/]
