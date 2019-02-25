# Lecture 2

## Abstraction

#### 1.	Generally speaking, what are the two major parts of a class? Please define a class that describes a computer, and then give an example of how to instantiate an object and access its members.

- 类的两个主要成分是：成员变量(member variables)和成员函数(member functions)。
以下为对class computer的声明和实例化：

	class computer
	{
	  public:
	    std::string type;  //member variables
	    computer(const std::string& _type) : type(_type) {}    //member functions
	};

	int main()
	{
	  computer A("int");
	  string B = A.type;
	  return 0;
	}


#### 2.	Where should we place the class declaration, in the header file or the source file? Please try to explain why header files are necessary.

- We should place the class declaration in the header file.

  1) Header files show the declarations without implementations, which makes it easier to carry out type security checks.
  2) Header files hide the implementations of interfaces, so that the source codes which are always commercial secrets can be protected.
  3) Classes are likely to be used in multiple compilation units (because the compilers need to know the definitions to allocate memories, for example). However, programmers may accidentally include the same header multiple times (which is actually very common), so we should place an include guard by the aids of preprocessing commands.


#### 3.	Please try to explain why the designers want to organize data and functions into classes? What are the advantages and disadvantages?

- Data and functions are organized into classes because they are easier to deal with as a whole – an object, which has its own characteristic things (data) and can handle some more complicated movements by themselves.
- Advantages:
  - Easy for dividing the whole program into several complete separately functioning parts. Easy for cooperation of a team and also easy for debugging.
  -	Easy for code reuse. Little modifications are needed when using old code. Composition and inheritance are both really good ways.
  - Safe for code reuse. When only headers and libraries are provided, the client user cannot change the implementations made by the providers, thus avoiding mistakes.
  -	Safe for memory control. Just make sure to write good constructors and destructors, and won't need to worry about the client user forgetting to clean up.
- Disadvantages:
  -	Size of object Oriented programs tend to be larger, Because of the size, the execution speed of OO programs maybe be slower and use more resources.
  -	The process of arranging data and functions into different objects takes really much work. And if the wrapping and design is not good enough it might cause lasting problems in large programs.


## Access control
#### 4.	Please try to use access control （访问控制）to enable information hiding of your class definition for computer in Problem No.1.

	class computer {
	public:
		computer(const std::string& _type) : type(_type) {}
		std::string get_type() const { return type; };
	private:
		std::string type;
	};

#### 5.	Please try to explain the benefits of access control.

- 通过在类中建立访问控制，可以将接口部分放在public中，而实现的过程部分放在private之中，这样可以防止用户错误的修改或者访问了一些实现过程的量。同时也可以使编程者修改程序实现方法时更加便捷，可以只用改public部分，因为用户肯定没有对该部分进行访问。
- By accessing control, programmers can put the interfaces in "public", and the implementations in "private". Thus reduce the risk that user programmers access or modify variables by mistake. Also it enabled the programmers to only rewrite the implementation part, which is in "private", without affecting existed programs.

#### 6.	Please tell the difference between keywords public, private and protected. We know that access control works for objects of the class. Does access control work in member functions? I.e., is it possible that one member function cannot access another member?

- difference：
  - public: can be accessed anywhere.
  - private: can only be accessed by members of this class.
  - protected: can be accessed by members of this class and its derived class.

- Access control does not work in member functions, but it is possible that one number function cannot access another member: static member functions cannot access non-static member functions. However, it is not implemented by access control.

#### 7.	Please try to explain why it is suggested to define a member function（成员函数） outside class definition.

- When definitions are outside class definitions, especially in another .cpp file instead of the .h file, you can wrap the implementation up into an object file and then put it inside a library. In this way, your client users cannot modify your implementation and this makes both sides easier.If the member function is defined inside class definition, every .cpp file that include the header file where the class is defined will copy the long definition of functions, which leads to code expansion.
- Also, the member function defined inside the class is regarded as inline functions automatically. It will reduce efficiency if the function is to long.

#### 8.	Please explain the differences between keyword struct and class.

- Members of struct are public by default; members of class are private by default.
- class is an new attribute in C++. C doesn't have keyword "class".

##	Friend
#### 9.	What should you do to permit a non-member function to access private or protected members? What about permitting another class to access them? Please give an example.

- 要用非成员函数访问类的私有成员变量需要将此函数设置成为该类的友元函数。要用另一个类去访问私有成员变量则需要将这个类设置为友元类。
- keyword friend is required if a non-member function wants to access private member of a class. It is similar if we want another class to access private member of a class.
- for example:
		class B;
		class A
		{
			friend int f(A*);
			friend class B;
		private:
			int x;
		};
		int f(A* p)
		{
			return p->x;
		}
		class B
		{
		public:
			int g(A* p){return p->x;}
		}

##	Inline
#### 10.	Please try to define some inline functions in Problems No. 1 with keyword inline. It is suggested to add a header file.


	//In header file:
	class Computer {
	  int computer_size;
	  void set_size(int);
	};
###
	//In source file:
	inline void Computer::set_size(int _size){
	  computer_size = _size;
	}


#### 11.	What are the advantages of inline functions? When and where should we use keyword inline?

- Advantages:
  - Comparing to normal functions: they are function-like macros and after compilation is written into the code, thus faster than other functions.
  - supports type checking, debugging, etc.
  - can be used as member functions.
- When to use:
  - simple functions which are used many times.
  - better without any looping.
  - the addresses of the functions are not used.
- How to use: (coding style)
  - a)	put definitions into headers.


#### 12.	Please try to explain the implementation of inline functions (内联函数的实现) in compiler, and explain the reason for the advantages of inline functions.

- The compiler will copy the code of inline function to where it is called.
- reason:
  - inline function save time because inline can yield less code than the function call preamble and return.
  - No function call overhead, and with more safety. Because of it expand everywhere it called so that definition is needed forward, so that there can't be called overhead.
- Keyword inline send compiler a request to make this function inline. However, this request may be ignored by compiler.

#### 13.	What will happen if we abuse (滥用) keyword inline?

- 由于内联是代码替代，在编译过程之中完成，所以如果对于一些相对较小的函数使用内联，可以适当提高运行时的速度。但如果滥用内联，则会导致空间开销大大增加，同时还有可能反而降低运行时的时间，同时编译时间也会变长。得不偿失。
- Because that inline funtions simply replace the function call by code, so it's OK if we use inline on some "small" functions in order to accelerate the program. However, abused keyword inline will make the code long and thus make compilation longer, and may also reduce running speed.

##	Header guarding
#### 14.	Please give an example of header guarding using preprocessor directives (预编译命令) “#ifndef … #define …#endif”, and try to explain the possible compiling errors without them.

	/* in computer.h */
	#ifndef COMPUTER_H
	#define COMPUTER_H
	class computer {
    private:
      DeviceManager dm;
    public:
      inline void boot() { dm.awake_all(); }
      inline void reboot() { dm.sleep_all(); dm.awake_all(); }
	};
	#endif

If without the guard, you may have error in this following codes.

	#include “Computer.h”
	#include “Bus.h”
	//…

The error message should be 'Computer' : 'class' type redefinition.

This occurs because Computer is somehow already defined in Bus.h, and g++ only allows for one declaration for each class (to guarantee consistency).

##	This pointer
#### 15.	What does this mean? How to avoid the name conflicts (名字冲突) between member and non-member variables with this? How to return current objects in member functions?

- "this" is a constant pointer pointing to the address of the current object. It cannot be changed, and is commonly used to access member variables/functions when name conflicts occur.

- To avoid name conflicts:
  - when using member functions/variables, for example, a variable named “x”:this -> x;
	when using other variable also named “x”: x;
	To return current objects in member functions: return *this;

##	Memory allocation
#### 16.	What are the differences between new/delete and malloc/free?

malloc/free are library functions. new/delete are c++ operators.
malloc calculate the space manually. new calculate the space required automatically.
new/delete can call constructor/destructor. malloc/free can't.

#### 17.	Why does C++ bring in new/delete to replace malloc/free?
- 由于c++语言相比c语言，加强了面向对象设计部分，有许多抽象数据类型，而malloc和free由于是标准库函数，并没有自动调用动态对象的构造函数和析构函数的功能，也不是设计者最初的本愿；相比之下new和delete是运算符，可以执行构造函数和析构函数。
- Compared to malloc/free, new/delete calls constructor and destructor automatically. This is a very important feature in oop designing, makes coding easier (otherwise the memory allocated needs to be freed manually).
- 同时对于内存分配上来说，new和delete更加智能，可以自动计算需要动态分配的内存大小，而malloc和free需要手动输入表达式计算所需大小。同时返回的是指向无类型void区域的指针，还需要一次强制类型转换。
- new/delete is smarter when allocating memory, for they don't need to calculate the size of the memory, while malloc/free has to calculate the size of memory manually.
- C++更加强调安全性，从安全性上来说，new比malloc更加安全。
- new/delete is safer for it calls constructor and destructor automatically.
- New操作符可以重载，可以自定义内存分配策略，甚至不做内存分配，而malloc无能为力。
- the operator new can be overr1dden to have a memory allocating strategy, which malloc cannot.
- Malloc/free需要库文件支持，但是new/delete不需要。
- new/delete doesn't need library.

##	Incomplete class
#### 18.	Please list the situations where we need to use incomplete type, i.e., forward declaration (前向声明).

- When we want to declare a function with a incomplete type as its argument type or return value type.
- When we want to reduce #include to save the time of compilation.
- When class A have a B* pointer and class B have an A* pointer, we must avoid the error of loop header file references.
