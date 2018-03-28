# Lecture 13
##	Operator overloading
#### 1.	Please state the essence (本质) of operator overloading.

- use operators for user-defined data types (classes), it is actually function overloading.

#### 2. Please state the restrictions on operator overloading.
- Cannot change the usage; 
- Cannot define new operators by yourself; 
- Cannot change precedence rules; 
- Cannot change the number of operands.

#### 3. Assume @ is an operator overloaded as member function, please write down the declaration of the functions corresponding to the following statements.
a) x @ y;
b) @x;
c) y@;


- x @ y; return-type opeator@(object, object);
- @x;   return-type operator@(object);
- y@;   return-type operator@(object, int);

#### 4. Assume @ is an operator overloaded as friend function, please write down the declarations of functions corresponding to the following statements.
a) x @ y;
b) @x;
c) y@;

- friend abcd operator @ (const abcd &x,const abcd &y);
- friend abcd operator @ (const abcd &x);
- friend abcd operator @ (const abcd &x,int);

#### 5. When are you supposed to overload operator as member functions? And when are you supposed to overload operator as friend functions? Please try to explain your answer in detail.


- 当双目运算符的左元素是一个系统定义好的类型，不方便重载，而又需要在函数中访问右元素的私有变量，就要用friend。
- 当双目运算符的左元素是自定义类型，就可以将重载运算符作为成员函数，这时只需要一个参数就是右元素。当然也可以将其作为全局函数,参数改为两个，不需要加friend


#### 6. Why should stream operators “<<” and “>>” be overloaded as friend functions?
- Because we want to use operator “<<” as “cout << obj;”, the operator occurs before object, if we overloaded it as member functions, we can only use it as “obj << obj2”, which is not expected.

#### 7. Please write down the declaration of the function that is called for the following statement. (Note that vec3 is a well-defined object.)
	Vector3 vec3_ = vec3;

- Vector3& operator = (const complex& vec_);


#### 8. Please write down a declaration of stream operator “<<” for Vector3, making the following statements legal.
	a)	std::cout << vec3 << std::endl;
	b)	std::cout << std::left << std::setw (5) << vec3 << std::endl;

- friend ostream & operator << (ostream &os, const Vector3 & vec3);


#### 9. Why is bit-copy dangerous, especially when there are pointer members in the class? Please give an example where bit-copy is adopted by the compiler, which potentially causes bugs.
因为默认拷贝构造函数是按位拷贝的，所以如果类中有指针变量的时候，就很可能会拷贝出一个一模一样的指针，此时如果delete掉一个类，会影响到另一个类的值。

	/* example */
	#include <iostream>
	
	using namespace std;
	
	class A
	{
	private:
		string* m_s;
	public:
		A() {
			m_s = NULL;
		}
		A(const string &s) {
			m_s = new string;
			m_s = s;
		}
		~A() {
			delete m_s;
		}
	};
	
	int main()
	{
		A a(“hello, world.”);
		A b;
		b = a;
		return 0;
	}

when a and b are destructed, the memory area m_s point will be released for twice.




#### 10. Please explain why self-assignment checking is important in overloading assignment operator.
- If there is pointer in the class, the assignment will first delete the original pointer to free the memory. But in self-assignment, we cannot delete it and it may cause data lost and memory leak.

#### 11. Please state the difference between operator postfix ++ (--) and prefix ++ (--). Please write down the function body of operator postfix ++ and prefix ++ for the following class.
	class Integer
	{
	public:
	    Integer (int x = 0): _x (x) {}
	private:
	    int _x;
	};


- Using postfix, the return value is the original one while using prefix the return value is the one after operation.

		const Integer& operator++ () { // Prefix
	    	_x++;
	    	return *this;
	  	}
	  	const Integer operator++ (int) { // Postfix
	    	Integer before (_x);
	    	_x++;
	    	return before;
	  	}


##	Function object (函数对象)
#### 12. What is a function object? What is the difference between function objects and normal functions? 

- An object of a class with overloaded function call operator “()”.
- Function object can store and pass data. An function object can correspond to multiple functions.


#### 13. What is the difference between function objects and normal objects?

- Function objects can store and pass values.
- Normal functions can only calculate certain problems.

#### 14. Please state the advantages of function object compared with function pointer (函数指针).
- Function object can store some member variables which is easy to change through interface. But function pointer can only point to a fixed function. In addition, function object can have inheritance, composition and so on, which make it easy to be reused or adapted. So function object is more valuable.
- Function objects can be safer and enables type checking. It can also utilize template to aid more powerful code reuse.
- Function objects can create lots of different kinds of objects according to the parameter passed, while function pointer can only point to existing function.

#### 15. Please complete the missing code in the following program such that we can obtain the sum of the integers in arr.
	#include <iostream>
	#include <array>
	#include <algorithm>
	#include <random>
	const size_t size = 1 << 5;
	std::ostream& operator << (std::ostream& os, const Sum& sum)
	{
	    os << "sum:" << sum._x << std::endl;
	    return os;
	}
	int main ()	
	{
	    std::random_device rd;
	    std::mt19937 mt (rd ());
	    std::uniform_int_distribution<> dis (0, size);
	    std::array<int, size> arr;
	    for (auto& element: arr)
	        element = dis (mt);
	    Sum s (0);
	    s = std::for_each (std::begin (arr), std::end (arr), s);
	    std::cout << s;
	    return 0;
	}

###

	#include <iostream>
	#include <array>
	#include <algorithm>
	#include <random>
	const size_t size = 1 << 5;
	
	class Sum {
		private:
			int _x;
		public:
			Sum(int s = 0): _x(s) {}
			void operator()(int x) {
				this->_x += x;
			}
			friend std::ostream& operator << (std::ostream&, const Sum&);
	};
	
	
	std::ostream& operator << (std::ostream& os, const Sum& sum)
	{
	    os << "sum:" << sum._x << std::endl;
	    return os;
	}
	int main ()
	{
	    std::random_device rd;
	    std::mt19937 mt (rd ());
	    std::uniform_int_distribution<> dis (0, size);
	    std::array<int, size> arr;
	    for (auto& element: arr)
	        element = dis (mt);
	    Sum s (0);
	    s = std::for_each (std::begin (arr), std::end (arr), s);
	    std::cout << s;
	    return 0;
	}

