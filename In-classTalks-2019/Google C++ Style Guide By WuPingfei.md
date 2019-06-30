By *Wu Pingfei* in OOP class
Student ID: 2018021366

#### Why are the regulations of code style necessary?
##### Improve Code Reading Efficiency           
##### Reduce communication costs. (especially in open source projects) With less ambiguities in grammar and logic understanding, you can understand other people's code much faster . 
##### After that, the inefficient debates about whether braces need to be newlined or other issues like it can be eliminated, so the team became more harmoni-ous.            
#####Keep in a good mood...

## Google C++ Style Guide
#### Google often publishes open source projects that will accept code from other code contributors. 
#### Therefore, Google has released this guide on its own style of programming, so that anyone who wants to join in Google’s open source projects is able to know the programming style of Google. 
#### Google C++ Style is generally accepted in many projects developed in the C++ language.

### 1. Header files
#### 1) The header file should be self-contained (that is, it can be included as the first header file)
#### 2) All header files should use #define to prevent header files from being multiple-declaration
Tip: To ensure uniqueness, the name of the header file should be based on the full path of the source tree of the project.

### For example, the headerfile foo/bar/baz.h in project foo should be named like this

(```)
	#ifndef FOO_BAR_BAZ_H_
	#define FOO_BAR_BAZ_H_
	...
	#endif //FOO_BAR_BAZ_H_
(```)
#### 3) Avoid using forward-declaration(前置声明) as much as possible. Instead, please use # include  to include the required header file
#### 4) A function is allowed to be defined as an inline function only if it has 10 lines or less.
#### 5) Path and Order  when use #Include : 
Path : Use a more complete path instead of using UNIX special shortcut directories , such as “.” 		(Current directory) and “. .”(Superior directory)
Order : related header files, C library, C++ library, other libraries，header files in this project
### 2. Scoping
#### 1)Namespaces: Namespaces subdivide the global scope into distinct, named scopes, and so are useful for preventing name collisions in the global scope.
#####  When definitions in a.cc file do not need to be referenced outside that file, place them in an unnamed namespace（匿名空间） or declare them static(静态).
#####  Namespaces（命名空间） should have unique names based on the project name, and possibly its path.
Tip1:Do not use using-directives (e.g. using namespace foo). 
Tip2:Do not use inline namespaces. 

#### 2) Local Variables:   
##### Place a function's variables in the narrowest  scope possible, (closest to the first use)  and initialize variables in the declaration.
(```)

	int i;
	i=f();//初始化与声明分离
	int j=g();//在变量声明时进行初始化
(```)
This makes it easier for the reader to find the declaration and see what type the variable is and what it was initialized to.
#### 3) Static and Global Variables:
##### Objects with static storage duration（静态储存周期） are forbidden unless they are trivially destructible（Informally this means that the destructor does not do anything）.
Tip: Try not to use global variables.
### 3. Classes
#### 1)Doing Work in Constructors: 
##### Avoid virtual function calls  (虚函数调用)  in constructors, and avoid initialization that can fail if you can't signal an error.
(```)

	class A
	{
		public:
			virtual void print(){cout << "This is A"<< endl;}
	}
	class B : public A
	{
		public:
			void print(){cout << "This is B"<< endl;}
	}
	int main()
	{
		A a;
		B b;
		A * p1=&a;
		A * p2=&b;
		p1->print();
		p2->print();
		return 0;
	}
(```)
#### 2) Structs vs. Classes:
##### Use a struct only for passive objects that carry data; everything else is a class.
#### 3) Access Control:
##### Make classes' data members private, unless they are static const
#### 4) Declaration Order:
##### Group similar declarations together, placing public parts earlier.
### 4. Functions
#### 1)Order of parameters：
##### If output parameters are used,they should appear after input parameters.
#### 2）Write Short Functions：
##### Prefer small and focused functions
#### 3)Reference Arguments:
##### All parameters passed by reference must be labeled const.
##### It is a very strong convention in Google code that input arguments are values or const references while output arguments are pointers.
### 5. Naming
#### 1)General Naming Rules:
##### Names should be descriptive; avoid abbreviation.
Tip: Note that certain universally-known abbreviations are OK, such as i for an iteration(迭代) variable
#### 2) File Names:
##### Filenames should be all lowercase(小写) and can include underscores "_"or dashes"-".
#### 3) Type names:
Type names start with a capital letter(大写字母) and have a capital letter for each new word, with no underscores(_)
#### 4) Variable Names
##### The names of variables (including function parameters) and data members are all lowercase, with underscores between words.
Tip: Data members of classes (but not structs) additionally have trailing underscores(下划线结尾).
(```)

	class TableInfo{
	...
	private:
		string table_name_;
		string tablename;
		...
	}
	struct UrlTableProperties{
		string name;
		int num_entries;
	};
(```)
#### 5）Constant Names：
#####Variables declared constexpr or const, and whose value is fixed for the duration of the program, are named with a leading "k" followed by mixed case.
#### 6）Function Names：
##### Regular functions have mixed case; accessors and mutators（取值和设值函数） may be named like variables.
### 6. Comments:
#### 1)Use // or /* */, as long as you are consistent.
#### 2)Class Comments:
##### Every non-obvious class declaration should have an accompanying comment that describes what it is for and how it should be used.
#### 3)  Function Comments
##### Declaration comments describe use of the function (when it is non-obvious); comments at the definition of a function describe operation.
#### 4) Variable Comments (the actual name of the variable)

### 7. Formatting
#### 1) Line Length
##### Each line of text in your code should be at most 80 characters long.
#### 2) Non-ASCII Characters
##### Non-ASCII characters should be rare, and must use UTF-8 formatting.
#### 3) Spaces vs. Tabs
##### Use only spaces, and indent 2 spaces at a time.
#### 4) Function Declarations and Definitions: (function calls are just the same )
##### Return type on the same line as function name, and parameters on the same line if they fit. 
Tip: Wrap parameter lists which do not fit on a single line.

##### Function look like this:

![图片2](C:\Users\123\Desktop\图片2.png)

##### If you have too much text to fit on one line:

![图片3](C:\Users\123\Desktop\图片3.png)

##### Or if you cannot fit even the first parameter:

![图片4](C:\Users\123\Desktop\图片4.png)

#### Some points we have to remember:
The open parenthesis(左圆括号) is always on the same line as the function name.
The open curly brace(左大括号) is always on the end of the last line of the function declaration, not the start of the next line.
The close curly brace(右大括号) is either on the last line by itself or on the same line as the open curly brace.

### 8.Cpplint:
##### You can use cpplint.py to detect style errors.
#### Download :
https://raw.githubusercontent.com/google/styleguide/gh-pages/cpplint/cpplint.py

### My summary:
#### Style guides focus on providing a common programming specification so that you can concentrate on implementing content rather than presentation.
#### The most important point: Be consistent.

### Reference:
#### Google C++ style guide:
google.github.io/styleguide/cppguide.html#Comment_Style
#### An article explaining the virtual function:
https://blog.csdn.net/u011580175/article/details/56838877
#### Storage duration:
https://en.cppreference.com/w/cpp/language/storage_duration#Storage_duration

