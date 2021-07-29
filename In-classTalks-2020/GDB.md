# GDB调试 
曾子渝

## 1.简介
* GDB是一个由GNU开源组织发布的、UNIX/LINUX操作系统下的、基于命令行的、功能强大的程序调试工具

* 对于Linux环境，GDB是必不可少的工具

* 支持多种语言

## 2.启动GDB
* 编译时加上-g参数，加入调试信息，否则无法调试
* Makefile中直接添加-g即可
  
thueda@thueda-VirtualBox test\>ls
main.cpp
thueda@thueda-VirtualBox test\>g++ -g main.cpp -o test
thueda@thueda-VirtualBox test\>ls
main.cpp  test

* 启动gdb
  
thueda@thueda-VirtualBox test\>gdb test
……
(gdb)

* 或者用gdb命令启动后输入file test

(gdb) file test
Reading symbols from test...done.

## 3. 基本命令
start: 开始调试,停在第一行代码处

l: list的缩写查看源代码, l a,b查看指定行a~b之间的代码，l functionname 查看函数 

b: break的简写，设置断点。b num在第num行设置，b functionname在函数处设置，b filename:num/functionname   在文件filename的某行或某个函数处设置断点

watch: 设置观察点，watch (变量名）表示变量值改变时停止执行。注意局部变量只有在运行至作用域内才能被观察

i breakpoints: info 的简写,查看断点信息（包括观察点）

d: delete breakpoint的简写，删除指定编号的某个断点（观察点），或删除所有断点（观察点）。断点编号从1开始递增。

s: step执行一行源程序代码，如果此行代码中有函数调用，则进入该函数。

n: next执行一行源程序代码，此行代码中的函数调用也一并执行。

r: run的简写，运行被调试的程序。如果此前没有下过断点，则执行完整个程序；如果有断点，则程序暂停在第一个可用断点处。

c: continue的简写，继续执行被调试程序，直至下一个断点或程序结束。

finish: 函数结束

p: print的简写，显示指定变量的值。多个变量写在{}内逗号隔开

display: 设置想要跟踪的变量,单步执行时自动显示，多个变量时也用{}

undisplay : 取消对变量的跟踪，被跟踪变量用整型数标识。undisplay num

set var: 可设置运行时变量。set var a=1

q: quit的简写，退出GDB调试环境。

help: GDB帮助命令，提供对GDB名种命令的解释说明。如果指定了“命令名称”参数，则显示该命令的详细说明；如果没有指定参数，则分类显示所有GDB命令，供用户进一步浏览和查询。

## 4. 示例

### 一

```
#include<iostream>
using namespace std;
int main(){
    int mul=1,n=0;
    cin>>n;
    for(int i=1;i<=n;i++)
        mul*=i;

    cout<<mul<<endl;

    return 0; 
```

***(gdb) start***

Temporary breakpoint 4 at 0x4008ca: file main.cpp, line 3.
……

***(gdb) watch mul***

Hardware watchpoint 5: mul

***(gdb) n***

4 int mul=1,n=0;

***(gdb) n***

Hardware watchpoint 5: mul

Old value = -8992

New value = 1
……

***(gdb) n***

Hardware watchpoint 5: mul

Old value = 1

New value = 2

### 二

```
int main(){
4	    int arr1[5]={1,2,3,4,5};
5	    int* arr2=new int[5];
6	    
7	    delete []arr2;
8	
9	    return 0;
10	}
```

Breakpoint 1, main () at m.cpp:7 delete []arr2;

***(gdb) p arr1***

$1 = {1, 2, 3, 4, 5}

***(gdb) p arr2***

$2 = (int *) 0x613c20

* (gdb) p *arr2@4

$3 = {0, 0, 0, 0}

***(gdb) set $i=0***

***(gdb) while($i<5)***

***>p arr2[$i]***

***>set $i = $i + 1***

***>end***

$4 = 0

$5 = 0

$6 = 0

$7 = 0

$8 = 0

### 三 
### 利用core文件调试
 
Segmentation fault(core dump)……

在linux下当应用程序发生异常中止退出或者发生崩溃的时候，linux内核会将应用程序在这段运行期间的内存状态等相关信息转存到磁盘，以供系统故障排查或者调试。这个转存的文件叫core dump文件。core dump文件中会记录程序当时的内存调用、堆栈引用、进程和线程调用等信息。

gdb -c core.（xxxx） （core文件）

file test

bt    （backtrace缩写）
显示出现段错误的位置

