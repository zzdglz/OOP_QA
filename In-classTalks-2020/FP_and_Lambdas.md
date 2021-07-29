#Lambdas and Functional Programming
##Part 1 - Introducing lambdas in C++
C++ 11 introduced lambda expression to allow us write an inline function which can be used for short snippets of code that are not going to be reuse and not worth naming. In its simplest form lambda expression can be defined as follows:


```c++
    [capture close] (parameters) -> return type
{
    definition of lambda function
}
```
This is an example of implementation
```c++
    //simple lambda function
    auto lambdaFn = [](int x)->int {
        std::cout<<"Hello world"<<std::endl;
        return x+1;
    };

```

In most of cases return type can be evaluated by compiler, so we don't need to specify it, unless its a complex case or there can be several variants for it. 
We can use C++ **auto** keyword, or use **std::function<>template** to hold the functions, we can also use C style function pointer **int(*lambdaFn)(int)** for the same, but is generally avoided because of complicated syntax.

Now, lets see an example of two lambdas, f(x) = x^2 and f(x,y) = (x+y)^2
```c++
    auto fx_square= [](int x){
        return x*x;
    };
    auto fxy_square = [](int x, int y){
        int x_square = [](int x){return x*x; }(x);
        int y_square = [](int y) {return y*y; }(y);
        int two_xy = [](int x, int y) {return 2*(x*y);} (x,y);
        return x_square+y_square+two_xy;
    };
    std::cout<<fx_square(5)<<std::endl;
    std::cout<<fxy_square(3,4)<<std::endl;
    //both will print 25
```
###The capture list []
The capture list is another way to have an access to local variables, which are not passed in parameters.
If the variables are not passed in capture list or as a parameter, then lambda cannot use it.
E.g.
```c++
    int var_local1 = 5;
    int var_local2 = 9;
    [var_local1]() {
        std::cout<<var_local1<<std::endl;
        std::cout<<var_local2<<std::endl; //compiler error, no access to var_local2
    }();
```
There is a way in which we can pass all the variables into lambda, by reference or by value (copy).
If variable is passed by value, then it is immutable, cannot be modified inside the lambda definition.
[=] means all elements are passed by value
[&] means they are passed by reference
```c++
    int var_local1 = 10;
    int var_local2 = 20;
    //all local variables are passed by  value (copy)
    [=](){
        
        std::cout<<var_local1<<std::endl;
        std::cout<<var_local2++<<std::endl; //compiler error !!!
        //variables passed by value are immutable
        //so we are not allowed to change them
    }();

    //all local variables are passed by  reference
    [&](){
        std::cout<<++var_local1<<", "<<++var_local2<<std::endl;
        //here we're allowed to anything with them
    }();
```
Creating Lambda f(x,y) = (x+y)^2 using capture list
```c++
    int x=5, y=10;
    auto cap_fxy_square = [x,y]()->int {
        int x_square = [](int x) {return x*x;}(x);
        int y_square = [](int y) {return y*y;}(y);
        int two_xy = [](int x, int y) {return 2*x*y;}(x,y);
        return x_square+y_square+two_xy;
    };
    int test_val = cap_fxy_square();
    std::cout<<test_val<<std::endl; //prints 125
```
##Part 2 - Functional Programming
Functional programming is a style of programming that emphasizes the evaluation of expressions, rather than execution of commands. The expressions in these languages are formed by using functions to combine basic values. A functional language is a language that supports and encourages programming in a functional style.

One of FP’s most powerful ideas is pure functions: functions that only use (but don’t modify) the arguments passed to them in order to calculate the result. If a pure function is called multiple times with the same arguments, it must return the same result every time and leave no trace that it was ever invoked (no side effects). This all implies that pure functions are unable to alter the state of the program.

```c++
string user = "John Stones";
int square (int x)
{
    //user="Mike Dean";
    return x*x;
}
bool no_need_cube = true;
int cube(int x)
{
    if (no_need_cube) {
        no_need_cube = false;
        return x;
    }
    else {
        no_need_cube = true;
        return x*x*x;
    }
}
//those are not pure functions, 
//because they have interaction with global variable
```
Examples of pure fanctions`
```c++
    int num = 9;
    int num_sqrt = std::sqrt(9);
```
```c++
    char str[] = "This is a sentence.";
    int l= strlen(str);
```
```c++
    double a = 556.6;
    int b = floor(a);
```
This is great, because you don’t have to think about the program state. But, unfortunately, it also implies that pure functions can’t read from the standard input, write to the standard output, create or delete files, insert rows into a database, and so on. If we wanted to be overly dedicated to immutability, we’d even have to forbid pure functions from changing the processor registers, memory, or anything else on the hardware level.

As we mentioned, all values are immutable in functional programming, so instead of loops we use recursion for iteration. recursion is a method of solving a problem where the solution depends on solutions to smaller instances of the same problem.
Some popular examples are factorial, Fibonacci series, Tower of Hanoi and so on.
```c++
// n! = 1*2*3*...*n 
// 0!=1
unsigned int Factorial (unsigned int x)
{
   
    if (x<=1) return 1;
    else
        return x*Factorial(x-1);
}
```
```c++
//each element in series starting from third one 
// is equal to sum of previous two elements
unsigned int Fibonacci(unsigned int n)
{
    if(n<=2)return 1;
    else return Fibonacci(n-1)+Fibonacci(n-2);
}
```
```c++
//https://en.wikipedia.org/wiki/Tower_of_Hanoi
//for proper description
void TowerOfHanoi(int n, char from, char middle, char to)
{
    if (n == 1)
    {
        cout << "Move disk 1 from rod " << from <<" to rod " << to<<endl;
        return;
    }
    TowerOfHanoi(n - 1, from, to, middle);
    cout << "Move disk " << n << " from rod " << from <<" to rod " << to << endl;
    TowerOfHanoi(n - 1, middle, from, to);
}
```
###Advantages and disadvantages of FP
####1. Advantages.
    a. Pure functions are easier to reason about
    b. Tessting and debugging are easier and straightforward
    c. Programs are more bulletproof
    d. Programms are easier to comprehend
    e. Function signatures are more meaningfull
####2. Dissadvantages
    a. Combining pure functions into a complete application is hard.
    b. In many cases, recursion is not the fastest way to handle the algorithm (e.g. Dynamic programming tasks)
    c. Cant input or output anything
    d. Because we cant change data, we always update as a copy, which consums additional memory

##Mix-up conclusion
In C++, since we have lambda functions, which are very convenient to use as a pure functions, we can easily implement FP and in many cases make our programs more advanced and have better performances.
