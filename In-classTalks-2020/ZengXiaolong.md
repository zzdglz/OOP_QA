# Linux命令行介绍

	Graphical user interfaces make easy tasks easy,
	while command line interfaces make difficult tasks possible.
	 ——《The Linux Command Line》 

## 简介

- 命令行通常指Shell.
- shell是一个程序，它接受从键盘输入的命令并将命令传递给操作系统去执行。

## 体验

- date
	- 显示了时间
- cal
	- 显示了日历
- df 
	- 显示了目前在Linux系统上的文件系统的磁盘使用情况统计。

## 常用命令
- pwd - 得知目前所在的工作目录的绝对路径名称
- cd [dirname] - 切换工作目录至dirname
- ls - 列出目前工作目录所含的文件及子目录
- file [filename] - 用于辨识文件类型。
- less [filename] - 用于浏览文件,用法较多
- cp [name] - 复制文件或文件夹
- mv
    - mv [源文件名] [目标文件名] - 将源文件名改为目标文件名
    - mv [源文件名] [目标目录名] - 将文件移动到目标目录
    - mv [源目录名] [目标目录名]
        - 若目标目录已存在，将源目录移动到目标目录;
        - 若目标目录不存在且目标目录的上一级目录存在则改名
    
- mkdir [dirname] - 创建新文件夹
- rm [name] - 删除文件或目录
- ln -s [源文件名] [目标文件名] - 为源文件创建快捷方式

## 通配符
- \* - 表示0或无穷多个任意字符
- ? - 表示1个任意字符
- $[\{$set$\}]$ - 表示一个在集合中的字符,如[abcd]表示一个a或b或c或d的字符
- $[!\{$set$\}]$ - 表示一个不在集合中的字符,如[!abcd]表示一个非a且非b且非c且非d的字符

## 关于"命令"的命令

- type - 用来显示指定命令的类型
- which - 在环境变量\$PATH设置的目录里查找符合条件的文件。
- man - 显示某个命令的帮助手册
- apropos - 查找与某个关键词相关的命令,相当于man -k
- info - 显示某个命令的信息
- whatis - 显示关于一个命令的具体描述,相当于man -f
- alias - 用于设置指令的别名
	


## I/O重定向

- cat - 将文件按行连接
- sort - 对文本按行排序
- uniq - 报告或删除重复的行(要求重复的行相邻)
- grep - 输出包含指定字符串的行
- wc - 计算文件的列数, 字数和字节数.
- head - 输出文件的开头部分
- tail - 输出文件的结尾部分
- tee - 读取标准输入的数据，并将其内容输出成文件。
- cut - 剪切每一行的一段
- paste - 将文件按列合并
- join - 将每个文件第一列相等的那些行的数据连接起来。
- comm - 比较两个排过序的文件
- diff - 比较两个文件
- sed - 过滤和转换文本