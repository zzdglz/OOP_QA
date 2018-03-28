# Lecture 3
## Scope
#### 1. What is the scopes of a, b, c and d?
	int a;
	int f ()
	{	
    	static int c;
    	int b;
    	{int d; }
	}
	int main ()
	{
    	f ();
	}



a是全局变量，作用域是整个编译单元范围内；  
b是函数中的栈变量，作用域只限于函数内部，在函数定义的反括号之后结束作用；  
c是static静态变量，在静态内存区分配内存，虽然在函数内部声明定义，但是作用域是全局的；  
d的作用域比函数作用域更小，是只限于函数内部的括号里。


#### 2. What is the scopes of objects of O?
 
	struct O
	{
	    int i;
	};
	O f (O o)
	{
	    return o;
	}
	const O& g (O o)
	{
	    return std::move(o);
	}
	O h (const O& o)
	{
	    return o;
	}



O as f parameter: in function f.  
O as f return value: in the expression including f.  
O as g parameter and g return value: in the expression including g.  
O as h parameter and h return value: in the expression including h.  



##	Constructor and destructor
#### 3. Is it necessary to declare destructors（析构函数） as public members? What about constructors（构造函数）?

- 析构函数: 不是. 构造函数: 不是. 
- 原因：
  - 如果你不想让外面的用户直接构造一个类（假设这个类的名字为A）的对象，而希望用户只能构造这个类A的子类，那你就可以将类A的构造函数/析构函数声明为protected。
  - 如果将构造函数/析构函数声明为private，那只能这个类的“内部”的函数才能构造这个类的对象：
	
		    \#include <iostream>  
		    using namespace std;  
		      
		    class A  
		    {  
		    private:  
		        A():data(10){ cout << "A" << endl; }  
		        ~A(){ cout << "~A" << endl; }  
		    public:  
		        static A& Instance()  
		        {  
		            static A a;  
		            return a;  
		        }
		        void Print()  
		        {  
		            cout << data << endl;  
		        }
		    private:  
		        int data;  
		    }; 
		    int main(int argc, char** argv)  
		    {  
		        A& ra = A::Instance();  
		        ra.Print();  
		    }  
  - 当我们规定类只能在堆上分配内存时，就可以将析构函数声明为私有的：
  		 
			class alloc
			{
			public:
			   alloc():			
			　 destroy(){ delete this;} 　
			private:
			   ~alloc();
			};


#### 4. When does copy constructors and move constructors get called?

- Copy constructor is usually called when:
  - New objects are being defined by an existing object of the same class
  - Function parameter or function return value is an object passed by value

- Move constructor is usually called when: 
  - New objects are being defined by an rvalue reference(an object that is about to be destroyed)
  - Function parameter or function return value is an rvalue reference(an object that is about to be destroyed)


#### 5. What are the benefits of constructors and destructors? Try to declare a class with constructors and destructor.


- 构造函数和析构函数，一方面是可以为private的部分提供初始值，以免无法访问造成不便；另一方面是保证安全性，通过构造函数来强制或者叫做提示使用者该类的初始化数据类型，而不会造成错误的初始化赋值，同时析构函数也可以很好的防止出现memory leak，下面是一个例子：


	class A
	{
		int* x;
		A()
		{
			x = new int;
			*x = 0;
		}
		~A()
		{
			if (x) delete x;
		}
	}


#### 6. Is it possible to call constructor and destructor explicitly? It is necessary?

- It is possible to call constructor and destructor explicitly. For An instance a1 of a class A, we can use a1.A::A() to call constructor explicitly, and we can use a1.A::~A() to call destructor explicitly.
- It is not necessary to call constructor explicitly. If space is dynamically allocated in the constructor, it is shown that calling constructor explicitly will cause a memory leak.
- It is not necessary to call destructor explicitly. If we call destructor explicitly, it may cause the same memory to be released many times which has potential to cause errors.

#### 7. Specify which constructor will get called for each statement.
 
	constructor ();
	constructor (int);
	constructor a;
	constructor b(5);
	constructor *c = new constructor;
	constructor *d = new constructor (5);
	constructor e[5] = {};
	constructor f[5] = {(1), (2)};


because numbers are default int type:  
a)	constructor ();  
b)	constructor (int);  
c)	constructor ();  
d)	constructor (int);  
e)	constructor ();  
f)	constructor (int) for the first two and constructor() for the last three.  


#### 8. How to define an object on stack（栈）? What about heap? What will happen if you define oversize object exceed your system’s limit?

- To define an object on stack, directly use its type name to define it.
- To define an object in heap, use pointer and new to define it.
- It will cause stackoverflow error.


Generally, when an object is initialized without the use of new/delete (like myObj object(15, “hello”, 5);), the object is placed on the stack and will be destroyed when its scope ends. If we use new/delete, (like myObj* object = new myObj(15, “hello”, 5);), the object will usually be stored on the heap while the pointer is most likely stored on stack. However this is dependent on a couple of things, for example whether the new() operator for myObj is overridden or not. If we exceed the system’s limits we might experience stack overflow which can cause the program to crash.

#### 9. What is the difference between the stack and the heap(堆)?


- Stack:
  - Limited size of several kilobytes to megabytes depending on the system and compiler settings.
  - Store local variables in functions
  - Stack overflow may occur for large array varibles and deep recursive functions
- Heap:
  - The size of heap is much larger than stack.
  - Heap is used for dynamic memory allocations.

#### 10. Do we need to free memory of stack or heap? How to verify that?

- We do not need to free memory of stack, which will be freed automatically when the end of the object’s life scope is met.
- We need to free memory of heap, otherwise the memory of heap will be leaked, increasing the memory burden.
- In C++ language, memory allocated by pointers and the keyword new is memory of heap, otherwise it is memory of stack.



#### 11. It is necessary to apply destructor? Explain the reason.

- Not always. because some objects without using heap memories will be automatically freed by the compiler.

#### 12. Is the code below work fine? Explain the reason. How to fix the problem?
	
	struct O
	{
	    int i;
	    O (int i) {}
	};
	int main ()
	{
	    O* o = new O[5];
	}


No. It doesn’t define the default constructor.  
To fix this problem, we can:  
1、give the constructor a default Argument.  
&emsp;&emsp;O (int i=0) {};  
2、Or just overload a constructor  
&emsp;&emsp;O (){};

