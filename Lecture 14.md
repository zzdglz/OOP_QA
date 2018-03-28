# Lecture 14
##	Template
#### 1.	Please state the original intention (意图) of bringing in template mechanism.

- Template allows same operations on different types of data.Avoid code repetition due to different data type.

#### 2. Please write down the general form of function template definition.

	template<class T1, class T2, ...>
	ReturnType FunctionName(ParameterList) {
		// FunctionBody
	}
Where ParameterList must include all the template arguments.


#### 3. Please state all the data types that can be template arguments.

- All the data types that can be instantiated can be template arguments, including all the build-in types, pointers, non-abstract classes, structs, etc.

#### 4. What is template specialization (模板特化)? Please write down the general form of it.


- When we want to use template but we'd like to introduce a specific version of one specific type, the template specialization is needed. 
The general form state as follow:

		template <class T> class pair;
		template <> class pair <int>;
		// template <> class class_name <type>


#### 5. Please implement (实现) the following code such that we can get Fibonacci sequence value of 100 within O(1) runtime.
	int main ()
	{
	    Fib<100> f;
	    cout << f.value << endl;
	    return 0;
	}

###
	template<int n>
	class Fib
	{
	public:
	  float value;
	
	Fib() {
	    value = 1.0 / sqrt(5) * (pow((1 + sqrt(5)) / 2, n));
	  }
	};

#### 6. What is implicit call instantiation of template? When does it work? 


- The implicit call instantiation of template is that sometimes we don’t specify the type of template arguments and the compiler will determine the type by the arguments. 
- It work when the type cannot determined by programmers, then we use implicit call instantiation to let compiler finish the job.Implicit call (instantiation) of template works when a template function is directly called with arguments in certain types. 



#### 7. Can a template parameter appear twice or more in the argument list? Can a template argument never appear in the template function/class body?
- Repeated declaration is prohibited.
- Argument can never appear.

#### 8. Please write down the general form of class template.

	template <class T1, class T2, …>
	class ClassName {
	//Class body
	};
#### 9. Why are the definitions of template functions and template classes supposed to be placed in header files?

- A template is not a class or a function. A template is a “pattern” that the compiler uses to generate a family of classes or functions.
- In order for the compiler to generate the code, it must see both the template definition (not just declaration) and the specific types/whatever used to “fill in” the template.
- Your compiler probably doesn’t remember the details of one .cpp file while it is compiling another .cpp file.



#### 10. What should you do to use default value for template parameters? What should you do to use constant values in template? What should you do to inherit from a template class? Please illustrate them with certain examples.

- Default value for template parameters:
 
		template<class T = int>

- Consntant value in template:

		template<class T, int max>

- Inherit from a template class:

		template<class T>
		class InheritedClass : public BaseClass<T> {
			// Declaration body.
		};


#### 11. Please plot the UML class diagram for the iterator design pattern.
<!-- <![image][tmp11] > -->
	
![14-11](https://raw.githubusercontent.com/darknessnone/oop-exercise/master/14-11.png)
#### 12. Plese implement a general “count_if” algorithm using template along with the iterator design pattern.

	template <typename InputIterator, class Pred>
	int Count_If(InputIterator begin, InputIterator end, Pred pred) {
	    int count = 0;
	    for (; begin != end; ++begin) 
	        if (pred(*begin))
	            count++;
	
	    return count;
	}




#### 13. Please give an example to illustrate how the function object (函数对象) is used in STL.


	Priority_queue<int, vector<int>, greater<int> > Q;
其中greater<int>就是stl中自定义的函数对象，内置了括号运算符来比较两个int的大小。上述代码建立了一个小根堆（默认是less<int>的大根堆）


[tmp11]:data:image/png;base64,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
