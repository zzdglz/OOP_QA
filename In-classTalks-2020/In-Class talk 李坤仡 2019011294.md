# Automatic Variables and Functions in Makefiles
**Author**:  Kunyi Li



## 1. Brief Introduction to Makefile


### 1. 1  Defination/Function

The Makefile file describes the rules for compiling, joining, and so on for the entire project.There are countless source files in a project, placed in several directories by type, function, and module.Makefiles define a set of rules to specify which files need to be compiled first, which files need to be compiled later, which files need to be recompiled, and even more complex functions, because makefiles are like Shell scripts that can also execute operating system commands. 

-----

### 1.2  Advantages of Makefile


+ Automatic compilation, the whole project is completely automatic compilation, greatly improving the efficiency.
+ Automatically find updated files based on the file timestamp, reducing compilation effort.

### 1.3 Basic Grammer
>target... : prerequisites ...          
>&emsp;command  
>&emsp;...  
>&emsp;...

-----


## 2. Automatic Variables  
  
  
  
### 2.1  What is automatic variable

This is a variable whose value is **automatically derived** by the Makefile.The value of an automated variable is determined by the **specific rules** being executed.This variable automatically fetches the series of files defined in the schema one by one until all the files that conform to the schema have been fetched. 

---

### 2.2  Commonly Used Automation Variables

#### 2.2.1 $@: Represent targets
**Demo**:
>a.o:b.cpp  
>&emsp; g++ -c b.cpp -o $@

**Result**
>thueda@thueda-VirtualBox:~share$ make  
>g++ -c b.cpp -o <u>a.o</u>  
>thueda@thueda-VirtualBox:~share$ ls  
>a.cpp <u>a.o</u> b.cpp makefile

In this **Demo**, $@ represents "a.o",which is the target.

-----

#### 2.2.2 $^: Represent prerequisites

**Demo**
>b.o:b.cpp b.h  
>&emsp;g++ -c $^

**Result**
>thueda@thueda-VirtualBox:~share$ make  
>g++ -c <u>b.cpp b.h</u>   
>thueda@thueda-VirtualBox:~share$ ls  
>a.cpp b.cpp <u>b.h b.h.gch b.o</u> makefile

In this **Demo**, $^ represents "b.cpp b.h",which are the prerequisites.

#### 2.2.3 $<: Represent the first item of prerequisites

**Demo**
>b.o:b.cpp b.h  
>&emsp;g++ -c $<

**Result**
>thueda@thueda-VirtualBox:~share$ make  
>g++ -c <u>b.cpp</u>  
>thueda@thueda-VirtualBox:~share$ ls  
>a.cpp b.cpp b.h <u>b.o</u> makefile

In this **Demo**, $< represents "b.cpp",which is the first item of the prerequisites.
## 3. Functions

**Makefile functions :**  
$(<Fanction\> <Parameters\>)Or ${<Function\><Parameters\>}  
Among them, <Function\> is the function name, <Parameters\> is the arguments separated by a comma

**Example**:
>$(subst $(source),$(target),$(string))

In this example, subst is the function name and $(source), $(target), $(string) is the arguments.
Adjacent arguments are separated by commas.

###Common string functions
####3.1 subst: String replacement function
**format:** $(subst <from\>,<to\>,<text\>)  
**Usage:** <from\> in <text\> is replaced with <to\>, and return the replaced character without changing the original value, where <text\> can include spaces and <to\> can be empty.  
**Demo:**
>target = B  
>source = b  
>string  = abcd  
>bar =$(subst $(source),$(target),$(string))  
>all:   
>&emsp;@echo bar:$(bar)   
>&emsp;@echo string:$(string)  

**Result:**  
>thueda@thueda-VirtualBox:~share$ make  
>bar:aBcd  
>string:abcd

####3.2 patsubst: Pattern string replacement function
**format:** $(patsubst <pattern\>,<replacement\>,<text\>)  
**Usage:** Find out if the words in the <text\> match the <pattern\> and replace them with <replacement\> if they match.Here, <pattern\> can include the wildcard "%" for strings of any length.If the <replacement\> also contains "%", then this "%" in <replacement\> will be the string represented by that "%" in <pattern\>.It doesn't change the original value.  
**Demo:** 
>bar =$(patsubst %.c, %.o, a.c b.c %.c)  
>all:   
>&emsp;@echo bar:$(bar)     

**Result:**
>thueda@thueda-VirtualBox:~share$ make  
>bar:a.o b.o %.o

####3.3 filter: The filter function
**format:**  $(filter <patterns\>,<text\>)  
**Usage:** Filter the words in the <text\> in a <pattern(s)\> pattern and retain the words that conform to the <pattern(s)\> pattern.You can have multiple modes, separated by Spaces.Returns a filtered string without changing the original string.  
**Demo:** 
>string = a.c b.s c.o  
>bar =$(filter %.c %.s, $(string))  
>all:   
>&emsp;@echo bar:$(bar)   
>&emsp;@echo string:$(string)  

**Result:**
>thueda@thueda-VirtualBox:~share$ make  
>bar:a.c b.s
>string:a.c b.s c.o

####3.4 filter-out: Anti-filter function
**format:**  $(filter-out <patterns\>,<text\>)  
**Usage:** As opposed to filter, retain words that do not conform to a <pattern(s)\> pattern.   
**Demo:** 
>string = a.c b.s c.o  
>bar =$(filter-out %.c %.s, $(string))  
>all:   
>&emsp;@echo bar:$(bar)   
>&emsp;@echo string:$(string)  

**Result:**
>thueda@thueda-VirtualBox:~share$ make  
>bar:c.o
>string:a.c b.s c.o


## 4. Reference

For more information about **Automatic Variables** and **Functions**, you can refer to the following blog:  

+ **Automatic Variables:** https://www.cnblogs.com/yangquanhui/p/4937494.html

+ **Fucntions:** https://blog.csdn.net/ustc_dylan/article/details/6963248
