# gdb调试
---
梁家铭</br>2018013388

---








<!-- @import "[TOC]" {cmd="toc" depthFrom=2 depthTo=6 orderedList=false} -->

<!-- code_chunk_output -->

- [ 一. 基本指令介绍](#一-基本指令介绍)
  - [break/b](#breakb)
  - [delete/d](#deleted)
  - [run/r](#runr)
  - [print/p](#printp)
  - [display/disp](#displaydisp)
  - [undisplay/undisp](#undisplayundisp)
  - [next/n](#nextn)
  - [step/s](#steps)
  - [continue/c](#continuec)
- [ 二. gdb调试演示](#二-gdb调试演示)
  - [结语](#结语)
---
<!-- /code_chunk_output -->
## 一. 基本指令介绍
###break/b
	在调试的程序中设置断点

	使用方法：
	1、break line-number                     使程序恰好在执行给定行之前停止
	2、break function-name                   使程序恰好在进入指定的函数之前停止
	3、break line-or-function if condition   如果条件是真，程序到达指定行或函数时停止
	  (b 46 if testsize==100)
	4、break filename:line-number            如果该程序是由很多原文件构成的，你可以在各个原文件中设置断点

###delete/d
	删除设置过的断点。

	使用方法：
	delete break-point number                 删除编号为break-point number的断点

###run/r
	运行准备调试的程序，在它后面可以跟随发给该程序的任何参数.
	包括标准输入和标准输出说明符(<和>)和shell通配符（*、？、[、]）在内。
	如果你使用不带参数的run命令，gdb就再次使用你给予前一条run命令的参数，这是很有用的。

	使用方法：
	run                                       运行

###print/p
	打印变量或表达式的值。

	使用方法：
	1、p a                                    打印变量a的值
	2、p find_entry(1, 0)                     对程序中函数的调用
	3、p *table_start                         数据结构和其他复杂对象

###display/disp
	使用方法与p相同，会在每次停止时打印。
	
###undisplay/undisp
	删除设置过的display。

	使用方法：
	undisplay number                          删除编号为number的display

###next/n
	不进入函数的单步执行

	使用方法：
	next                                      单步

###step/s
	进入函数的单步执行

	使用方法：
	step                                      单步

###continue/c
	从断点开始继续执行

	使用方法：
	continue                                  从下一个断点开始执行
---



## 二. gdb调试演示
使用gdb前需将gdb添加到环境变量中
需在编译使用gdb调试的程序时加入编译选项-g
演示调试以下代码
```c++
 1: #include<cstring>
 2: #include<cstdlib>
 3: #include<cstdio>
 4 :#include<cmath>
 5: #include<iostream>
 6: using namespace std;
 7: int add(int t)
 8: {
 9: 	return t+1;
10: }
11: int main()
12: {
13: 	int t=0;
14:	
15: 	t=add(t);
16:
17: 	t=add(t);
18:
19: 	t=add(t);
20:
21: 	for(int i=1;i<=3;i++)
22:		t=add(t);
23:
24: 	return 0;
25: }
```
我们只需打开终端，将路径设为该cpp的位置，然后就可以通过gdb指令开始调试了
调试过程如下

![Alt text](http://kan.027cgb.com/615847/ljm/a.png)

---
###结语
	gdb是调试程序的有力工具，是简洁、高效的debug工具。
	掌握gdb调试的方法，将会对我们的编程能力有着积极的影响，所以它是十分值得学习和使用的。