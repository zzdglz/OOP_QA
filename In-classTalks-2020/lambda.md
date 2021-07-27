# introduction

```cpp
int func(int a,int b){
  return a+b;
}
```
```
<return type> <function name>( <parameters> ){
  <body>
}
```

```cpp
auto func2 = [](int a,int b)->int {return a+b;};
```
```
[ <capture> ]( <parameters> )-> <return type> { <body> }
```

## return type

```cpp
auto func1 = [](){return 1;}; //OK ->int
/*
auto func1 = []()->int {return 1;};
*/

auto func2 = [](){cout<<endl;}; //OK ->void

auto func3 = [](){
  if(true) return 1;
  return 2;
}; // OK in c++14  ->int

auto func4 = [](){
  if(true) return 1;
  return false;
}; // Error
```

## capture

- `[]`cannot capture any local variables
- `[&]`capture all local variables by reference
- `[=]`capture all local variables by value
- `[a,&b]`capture `a` by value, `b` by reference
- `[=,&a,&b]`capture `a` and `b` by reference, and other local variables by value
- `[&,a,b]`capture `a` and `b` by value, and other local variables by reference

```cpp
int a = 0;

int main(){
  int b = 0;

  auto func1 = [ ]() {a;}; //OK
  auto func2 = [a]() {a;}; //Error
  auto func3 = [ ]() {b;}; //Error
  auto func4 = [b]() {b;}; //OK
}
```

Try this.

```cpp
int a = 0;
auto func1 = [a]() {cout<<a<<endl;};
auto func2 = [&a]() {cout<<a<<endl;};
a = 10;
func1();  // 0
func2();  // 10
```

Capture `this`.

```cpp
class A{
  int val = 0;
public:
  void f(){
    [this](){ val = 3; cout<<val<<endl; }();
    // this must be captured by value
    cout<<val<<endl;
  }
}
```

```cpp
class A{
	int val=0;
public:
	std::function<int()> f(){
		return [this](){return val;};
	}
};

int main(){
	A *a=new A{};
	auto f=a->f();
	delete a;
	cout<<f()<<endl;
}
```

Capturing a variable by value just like passing actual arguments to formal parameters. But capture is done when lambda function is defined, but not called.

In other words, no matter how many times the function is called, capture is done only once.


```cpp
class A{
public:
  A(){cout<<"constructed"<<endl;}
  A(const A &copied){cout<<"copy constructed"<<endl;}
  ~A(){cout<<"destructed"<<endl;}
};

int main(){
  A a;
  {
    cout<<"start of code block"<<endl;
    auto f = [a]() {}; // a is captured by value
    cout<<"lambda function defined"<<endl;
    f();
    f();
    f();
    cout<<"end of code block"<<endl;
  }
}
```

# `mutable`

Lambda function is set `const` by default, which means we cannot change the variables captured by value. (Or our compiler will tell us the variable is read-only. )
We need to use keyword `mutable` to change that.


```cpp
int a = 0;
auto f = [a](){a=0;}; //Error
```

```cpp
int a = 0;
auto f = [a]()mutable {a=2;cout<<a<<endl;} // 2
cout<<a<<endl; // 0
```

# how to store a lambda

We can use a ¡®std::function¡¯ or function pointer to get a lambda function, but there is implicit type conversion. 

And a function pointer can only receive a lambda without capture. 


```cpp
std::function<int(int,int)> f(){
	return [](int x,int y){return x+y;};
}
```

We can convert lambda function to ¡®std::function¡¯, but can not convert back.


```cpp
int a = 0;
auto x = [a]() mutable {cout <<++a<< endl;};
x();
auto y = x;
x();
y();

std::function<void()> a = [](){};

int (*b)(int,int) = [](int x,int y){return x+y;};


void (*a)() = [](){};
	auto b = [](){};
	a=b; // OK
	b=*a; // Error
```

# like a functor

In c++, we can define a class and overload its parentheses to create a functor.   

We can use the object as a function.


```cpp
class cmp{
public:
	bool operator() (int a,int b) const {return a<b;}
};

int main(){
	cmp functor;
	bool ret = functor(1,2);
}
```

```cpp
std::function<void()> f1(){
	return [](){cout<<"This is a functional interface."<<endl;};
}

std::function<void()> f2(){
	class functor{
	public:
		void operator() (){
			cout<<"This is a functional interface."<<endl;
		}
	}ret;
	return ret;
}
```
