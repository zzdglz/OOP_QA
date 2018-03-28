# Lecture 1

##Command-line argument（命令行参数）

####1. Suppose that you want to write an A+B program, which get A and B from command-line argument, how to complete the task? Please give an example of the source code, as well as how to compile and run the program.    

    //a.cpp
	#include <iostream>
	#include <cstdlib>
    #include <cstdio>
    int main(int argc, char** argv)
    {
	    std::cout << atof(argv[1]) + atof(argv[2]) << std::endl;
	    return 0;
    }

&emsp;Windows下  
&emsp;&emsp;编译时输入：g++ a.cpp -o a.exe\   
&emsp;&emsp;运行时输入：a.exe 1 2

####2. Please list（列举）the potential advantages and disadvantages of obtaining arguments by file reading vs. by command-line argument.

- Advantage of file reading:  
&emsp;&emsp;1) File reading can be used in programs with GUI.  
&emsp;&emsp;2) Files can be copied and modified easily.  
&emsp;&emsp;3) Files can provide a larger size of arguments.  
- Disadvantage of file reading:  
&emsp;&emsp;1) File IO is more complex and slower than command arguments with exceptions to handle.  
&emsp;&emsp;2) Conventions(e.g. “a.out”) are required without command argument.  
&emsp;&emsp;3) Not easy to know argument amounts.   
- Advantage of command-line argument:  
&emsp;&emsp;1) Make the program easier to be called in command-line.  
&emsp;&emsp;2) Make the program able to be called in batch scripts.  
&emsp;&emsp;3) Eliminate the trouble of creating unnecessary files.  
- Diadvantage of command-line argument:  
&emsp;&emsp;1) Unable to handle big number of data or binary data.   
&emsp;&emsp;2) Sometimes too complex for users to remember and use.  
&emsp;&emsp;3) Passing argc and argv takes some effort, and they can’t be changed during the process.  


####3. How to input a command-line argument with spaces in it, e.g., how to input ‘Hello World’ as one argument? 
 
- use quotation marks to embrace the whole message. For example, to input Hello World as one argument, put “Hello World” in the command-line.Or input a slash sign \ before the space ,like Hello\ World.


 
####4. What is the meaning of argc and argv? What are their data types? If command “a.exe 1 2 3” is executed in the terminal (终端), what are the values of argc and argv?  

- argc: the number of arguments put to terminal, the data type is int.  
- argv: the arguments put to terminal, the data type is char**.  
- when “a.exe 1 2 3” is executed in the terminal, argc = 4, argv = {“a.exe”, “1”, “2”, “3”}  

## Translation（翻译）from source code（源代码）to binary executable（二进制可执行文件）  

####5.	Please explain how interpreters（解释器）and compilers（编译器）work. What are the typical programming languages (典型编程语言) for each of the two translation methods? Please list the advantages and disadvantages of interpreters vs. compilers.  

- 解释器是在执行程序时,才一条一条的解释成机器语言给计算机来执行,所以运行速度是不如编译后的程序运行的快的。典型语言为Python，java。优点是比较容易实现跨平台，因为解释器可根据运行时所在平台对代码进行转换。缺点是速度慢。    
- 编译器是把源程序的每一条语句都编译成机器语言,并保存成二进制文件,这样运行时计算机可以直接以机器语言来运行此程序,速度很快。典型语言为C++。优点是执行效率高，因为不需要一边运行一边翻译。缺点是需要根据不同的操作系统编制代码。

####6.	GNU compiler g++ is universally used in both commercial and research projects. So you are supposed to know how to compile C++ source files into the binary file. State the basic usage (基本用法) to compile a source file. List useful compiling options (编译选项) as many as possible, and explain why and when we need these options.    
<pre>   
Usage: g++ [options] file...  
Options:  
 
   -pass-exit-codes         Exit with highest error code from a phase
  --help                   Display this information
  --target-help            Display target specific command line options
  --help                   Display specific types of command line options (Use '-v --help' to display command line options of sub-processes)
  --version                Display compiler version information
  -dumpspecs               Display all of the built in spec strings
  -dumpversion             Display the version of the compiler
  -dumpmachine             Display the compiler's target processor
  -print-search-dirs       Display the directories in the compiler's search path
  -print-libgcc-file-name  Display the name of the compiler's companion library
  -print-file-name=< lib>  Display the full path to library <lib>
  -print-prog-name=< prog> Display the full path to compiler component <prog>
  -print-multiarch         Display the target's normalized GNU triplet, used as a component in the library path
  -print-multi-directory   Display the root directory for versions of libgcc
  -print-multi-lib         Display the mapping between command line options and multiple library search directories
  -print-multi-os-directory Display the relative path to OS libraries
  -print-sysroot           Display the target libraries directory
  -print-sysroot-headers-suffix Display the sysroot suffix used to find headers
  -Wa,< options>            Pass comma-separated <options> on to the assembler
  -Wp,< options>            Pass comma-separated <options> on to the preprocessor
  -Wl,< options>            Pass comma-separated <options> on to the linker
  -Xassembler < arg>        Pass <arg> on to the assembler
  -Xpreprocessor < arg>     Pass <arg> on to the preprocessor
  -Xlinker <arg >           Pass <arg> on to the linker
  -save-temps              Do not delete intermediate files
  -save-temps=<arg >        Do not delete intermediate files
  -no-canonical-prefixes   Do not canonicalize paths when building relative prefixes to other gcc components
  -pipe                    Use pipes rather than intermediate files
  -time                    Time the execution of each subprocess
  -specs=< file>            Override built-in specs with the contents of <file>
  -std=< standard>          Assume that the input sources are for <standard>
  --sysroot=< directory>    Use <directory> as the root directory for headers and libraries
  -B < directory>           Add <directory> to the compiler's search paths
  -v                       Display the programs invoked by the compiler
  -###                     Like -v but options quoted and commands not executed
  -E                       Preprocess only; do not compile, assemble or link
  -S                       Compile only; do not assemble or link
  -c                       Compile and assemble, but do not link
  -o < file>                Place the output into <file>
  -pie                     Create a position independent executable
  -shared                  Create a shared library
  -x < language>            Specify the language of the following input files
                           Permissible languages include: c c++ assembler none
                           'none' means revert to the default behavior of
                           guessing the language based on the file's extension

</pre>
Options starting with -g, -f, -m, -O, -W, or --param are automatically passed on to the various sub-processes invoked by g++.  In order to pass other options on to these processes the -W<letter> options must be used.



####7.	What is a library (库)? How to build a library using g++ compiler? How to use a library using g++ compiler? At what stage is a library loaded (载入)? Is it always during the linking stage (链接阶段)? Please explain the difference between static (静态) and dynamic (动态) libraries.    

*	C/C++ libraries are modules of already-compiled code which are accessed through including proper headers and linking the libraries (*.a, *.lib). By using libraries we could use functions provided by others without having to write something with similar use again. There are two kinds of libraries – static ones and dynamic ones.
*	To build a library using g++ compiler, the following commands are used.  

		Use –c option to create .o lib  
		Use ar to create .a lib  
		Use –dynamiclib to create .so lib  
*	to use mylib.a:  
*	
		g++ main.o mylib.a –o main.exe
*	Static libraries are loaded during compiling.Dynamic libraries are loaded when the program runs.
*	A static library is required at compile time, but not at runtime because all useful message has been encoded into the executable; however, a dynamic one is required at runtime but not compile time, for they are referred while using.




###Multi-file project

####8.	Assume that there are main.cpp, sum.cpp, product.cpp, and functions.h, please write down the command to compile them into main.exe with g++.    

- g++ main.cpp sum.cpp product.cpp -o main.exe  
####9.	Please explain why multiple files are necessary for a project, especially the advantages of multi-file project compared with single-file project.
    
- 多文件的工程将任务分解到不同的文件之中。当出现问题时，可以很快锁定问题所在的位置。而且多文件工程可以方便的根据功能需要添加或替换文件以达到改变工程功能的目的，而单文件工程必须要打开文件修改代码，不方便且容易出错。  
- 在多文件工程中，编译往往需要很长时间。对于单文件工程来说，如果一部分源代码被修改，那么所有代码都要重新编译，若是在多文件工程中，只需要重新编译被修改的文件。  

####10.	What is separate compilation (分段编译)? Why is it better than direct compilation, i.e., to generate the executable directly from the source files? Please state the whole process of separate compilation.  
  
- Separate compilation is a compiling way which separates the whole program to parts and compiles each parts then.  

- Advantage of separate compilation:  
&emsp;Separate compilation makes the whole program divided to small modules. When we modify some modules of the program, we only need to re-compile the modified modules, rather than compile all the modules, which greatly reduce the demanding time of compiling. Thus, separate compilation can improve the efficiency of developing programs.  

- Process:   

 * Compile each module to target files(.o). If some of the target files exist already and their corresponding source codes have not been modified, the original target files will be reserved and the compilation of this module will be skipped.
 * Link all the target files to the executable file.




####11.	What should you do to use a global variable (全局变量) or function (函数) in several source files (源文件)? Please give as many ways as you can.  

*	For a global variable: define it in one .cpp file, use extern keyword to declare it in other files. similar for functions, only extern keyword could be omitted.  
*	Define the variable/function in a .h header file, and include the header in the .cpp files where the variable/function is needed.  
*	pass them as arguments of functions  
*	for functions, definitions can be repeated for multiple times  





####12.	Is it allowed to redefine a variable or function with the keyword extern? For example, “extern int a = 2;”. Why?    
 
- No. Because variable “a” has occurred in other place and “extern int a = 2;” is equal to “int a = 2;”. It will cause redefinition error.

####13.	Please explain the usage of header files (头文件). Is it allowed to define the function body (函数体) in the header file? Do we need to compile header files using g++? Why?    

- 头文件是用来使多文件项目可以顺利完成正常编译的必要部分。因为多文件项目中的某些编译单元定义了某些函数或者变量，而另一些编译单元又需要使用（调用）这些函数或者变量，此时我们把这些函数和变量的声明统一放在一个头文件之中，这样我们只需要在每个编译单元之中使用预处理器将头文件包含进去，就可以正常完成编译，而不会出现未声明就使用的错误。而且，头文件使整个项目中出现的函数和变量列出，显得十分有条理。
- 在头文件中，对于普通函数的定义是不允许的，因为这样可能出现链接时出现重复定义的错误，普通函数可以多次声明但不可以多次定义。但是如果是内联函数，就必须写在头文件之中，不能写在任何其他的编译单元之中，否则在分段编译形成目标文件之后，对应的内联函数的标识符就会被编译器自动替换为整个函数体，此时该标识符就不存在了，于是在其他的编译单元中调用该内联函数时就会报错。
- 头文件是不需要单独编译的，因为头文件之中只是一些函数和变量等等的声明而已，通过预处理过程被包含进独立的编译单元之中，成为该编译单元的一部分，此时参与到编译之中。

####14.	Please explain the differences between “”  and  <>  when including a header file in the source file.  

- \#include “”:  
The compiler will search from the user’s working directory. If not found to include a directory to find. This way is used if we want to include header files we wrote by ourselves.
- \#include <>:  
The compiler will search from the standard library directory. This way is used if we want to include header files in the standard library.
###	Make and makefile
####15.	Please explain the dependency rules of make.  

- the one in front of the colon is the target. if it’s date is later than any dependencies after the colon or they don’t exist, it will find the missing file/ out-of-date file to generate it. only when the files are all up-to-date will target be generated. 

		target: file1 file2 file3
			command to generate target
		file1: file12 file13
			command to generate file1



####16.	How to enable separate compilation (分段编译) of source files using make and makefile? Assume that we have main.cpp, sum.cpp, product.cpp, and functions.h, please write the makefile to generate main.exe by separate compilation.  

	all: main.exe
	main.exe: main.o sum.o product.o functions.h
		g++ main.o sum.o product.o -o main.exe
	sum.o: sum.cpp
		g++ -c sum.cpp -o sum.o
	product.o: product.cpp
		g++ -c product.cpp -o product.o
	main.o: main.cpp
		g++ -c main.cpp -o main.o
	clean:
		del *.o
		del *.exe


####17.	On linux, how to generate a binary file with a makefile? How to use the library file to generate an executable file with makefile? Please give a simple example on Linux.

	/*  mylib.h  */  
	#ifndef MYLIB_H
	#define MYLIB_H
		
	void fun();
		
	#endif  

### 
	/*  main.cpp  */
	#include <iostream>
	#include "mylib.h"
	using namespace std;
		
	int main()
	{
		fun();
		return 0;
	}

### 
	/* makefile */

	all:main
	main:main.o
		g++ main.o mylib.a -o main
	main.o:main.cpp
		g++ -c main.cpp -o main.o
	clean:
		rmmain.o main



## 
	/*生成二进制文件*/
	all: main
	main: main.o class1.o class2.o
		g++ main.cpp –o main
	main.o: main.cpp header1.h header2.h
		g++ main.cpp –c main.o
	class1.o: class1.cpp header1.h
		g++ -c class1.cpp –o class1.o
	class2.o: class2.cpp header2.h
		g++ -c class2.cpp –o class2.o
	clean:
		rm *.o main  

### 
	/*利用库文件生成二进制文件*/
	sSOURCES=$(wildcard *.cpp)
	HEADERS=$(wildcard *.h)
	sOBJECTS=$(sSOURCES:%.cpp=%.o)
	TARGET=maze
	LIB=maze.a
	
	all: $(TARGET) 
	$(TARGET): $(sOBJECTS) $(HEADERS) $(LIB)
		@echo "Now Generating $(TARGET) ..."
		g++ $(sOBJECTS) $(LIB) -o $(TARGET)
	%.o: %.cpp $(HEADERS)
		@echo "Now Compiling $< ..."
		g++ -c $< -o $@
	%.o: %.cxx $(HEADERS)
		@echo "Now Compiling $< ..."
		g++ -c $< -o $@
	clean:
		rm *.o $(TARGET) *.bak 
	explain:
		@echo "User Sources: $(sSOURCES)"
		@echo "User Objects: $(sOBJECTS)"
		@echo "Lib: $(LIB)"
			@echo "Target: $(TARGET)"

####18.	Please explain more options for make, which are the command-line arguments of make.

<pre>
 Options:
	-b, -m                                        Ignored for compatibility.
	-B, --always-make                             Unconditionally make all targets.
	-C DIRECTORY, --directory=DIRECTORY           Change to DIRECTORY before doing anything.
	-d                                            Print lots of debugging information.
	--debeg[=FLAGS]                               Print various types of debugging information.
	-e, --environment-overrides                   Environment variables override makefiles.
	-f FILE, --file=FILE, --makefile=FILE         Read FILE as a makefile
	-I, --ignore-errors		                      Ignore errors from commands.
	-I DIRECTORY, --include-dir=DIRECTORY         Search DIRECTORY for included makefiles
	-j [N], --jobs[=N]                            Allow N jobs at once; infinite jobs with no arg.
	-k, --keep-going                              Keep going when some targets can’t be made.
	-l [N], --load-average[=N], --max-load[=N]    Don’t start multiple jobs unless load is below N.
	-L, --check-symlink-times                     Use the latest mtime between symlinks and target.
	-n, --just-print, --dry-run, --recon          Don’t actually run any commands; just print them.
	-o FILE, --old-file=FILE, --assume-old=FILE   Condier FILE to be very old and don’t remake it.
	-p, --print-data-base                         Print make’s internal database.
	-q, --question                                Run no commands; exit status says if up to date.
	-r, --no-builtin-rules                        Disable the built-in implicit rules.
	-R, --no-builtin-variables                    Disable the built-in variable settings.
	-S, --no-keep-going, --stop                   Turns off –k.
	-t, --touch                                   Touch targets instead of remaking them.

</pre>
**19.	Please list useful advanced grammars (高级语法) of makefile as many as you can. It is suggested to explain the usage of these grammars. For example, it is convenient to automatically detect all the source files in a folder (自动检测文件夹下的所有文件) and automatically compile them all. How does makefile support this?**

- Such as that there is a.cpp b.cpp c.cpp in the folder,and at the same time,they use headfile func.h.So,we can complie it in this way:  

		object=a.o b.o c.o
		main:func.h
		g++ $(object) –o main  
	By using “$”,我们能够实现批处理。  
-  “.RECIPEPREFIX = >” can change all the tab into ‘>’  
- Makefile使用 Bash 语法，完成判断和循环。  

        ifeq ($(CC),gcc)
			libs=$(libs_for_gcc)
		else	
  			libs=$(normal_libs)
		endif





