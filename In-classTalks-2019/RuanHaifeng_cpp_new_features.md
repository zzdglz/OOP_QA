# C++ 11/14/17 new features
## Ruan Haifeng, CST 75
## 1. rvalue reference
### introduction
Rvalue reference is an effective way to avoid unnecessary copying overhead in programs. A typical case of the overhead is when a function returns a large object, like this:

    vector<int> f() { return vector<int>(10); }
    vector<int> v = f();

Here, in theory, one construction and two copy constructions occur, namely:
+ construction of vector<int>(10)
+ copy construction of a temporary
+ copy construction of v

That can be a large overhead. Note that the initial vector<int>(10) is destructed, causing a waste. We could have utilized it by letting `v` take hold of that resource, letting `v` "point to" that resource. That's exactyly what rvalue reference helps to do - to allow **move semantics** by marking otherwise wasted resources. Another use of it is to implement **perfect forwarding**, which allows move semantics to be passed on.

Below I'll discuss the concept and usage of rvalue reference.
### (1) lvalue VS rvalue
+ lvalue
    + refers to a memory location, whose address can be taken via operator&
    + lvalues have names
    + eg. `int x; // x is lvalue`
+ rvalue
    + refers to any expression other than lvalue
    + including expiring values, temporaries and literal values
    + examples
        + `vector<int>(10)`
        + `c`, `true`, `Hello`, `4.0`
### (2) rvalue reference
+ notation and meaning
    + `&&` denotes an rvalue reference
    + correspondingly, the reference `&` is now called an lvalue reference
    + rvalue reference is a name for rvalue and extends its lifetime
    + examples:
        + `double&& a = 4.0;  // rvalue 4.0 now has name "a" and can be used later`
        + `vector<int>&& v = vector<int>(10)  // vector<int>(10> returns an rvalue(temporary), which would have died without the name "v"`
    + however, **rvalue reference is an lvalue**, because it has a name and consequently a trackable memory location. Similarly, inside a function, its parameters are all lvalues, even though they may be rvalue references, since they all have names.
+ reference binding
    + lvalue reference can only bind to lvalues
    + rvalue reference can only bind to rvalues
    + however, **const lvalue reference** can also bind to rvalue, since it guarantees that no change will be applied.
    + example:
        
            int a; // lvalue  
            int &r1 = a; // ok  
            int &r2 = 1; // error; lvalue reference cannot bind to rvalue
            int &&r3 = 1; // ok  
            int &&r4 = a; // error; rvalue reference cannot bind to lvalue
            const int &cr1 = a; // ok
            const int &cr2 = 1; // ok

+ reference collapsing rule  
    Now that `&` and `&&` denote lvalue and rvalue reference, respectively, you may wonder what `&&&` or even `&&&&` means. Normally, these are illegal expressions.

    However, there is one case where they do occur as legal. That is, in a template, like this:

      template <typename T>
      void f(T&& param) {
          // do something
      }
    Now, what's the type of `param`? The answer is, it can become not only an rvalue reference, but also an lvalue reference, depending on the actual parameter that initializes it. Therefore, `T&&` is called a **universal reference** here. There are two cases:
    + (1) actual parameter is lvalue

        Assume the actual parameter has type `R`. C++ standards says that in the case of a **universal reference**, and **when the actual parameter is an lvalue**, `T` shall evaluate as a reference of that lvalue type, namely `R&`. For example:

          int a;  // a is lvalue
          f(a);

        where `T` will be deduced to `int&`.
    
        Now we can have the type of `param`, which is `T&&`. `T` is `int&`, so `param` has type `int& &&`, an rvalue reference of an lvalue reference. Again, standards say this shall deduce to lvalue reference `int&`.

        Here is the general rule of multiple-reference type deduction: an rvalue reference of rvalue reference deduces to rvalue reference; any other case deduces to lvalue reference. This is called the **reference collapsing rule**.

        A case worth noting is when `R` is an rvalue reference, like `int&&`. Remember that **rvalue reference is lvalue**, so we have `T = R& = int&& &(lvalue reference of rvalue reference) = int&`, and `param` has type `int& && = int&`.
    + (2) actual parameter is rvalue
        
        When the actual parameter is rvalue, `T` is directly deduced to `R`, and `param` to `R&&`.
## (3) move semantics
### a. move constructor
The idea of move semantics has been introduced in the beginning, so let's jump right to the implementation. To make things clear, we use a hand-made vector:

    class MyVector {
    public:
        MyVector(int n) {
        // constructs an array of size n
        }
        
        MyVector(const MyVector& other) {
        // deep copy
        }
    
        ~MyVector() {
          delete data_;
          data_ = nullptr;
        }
    private:
        int* data_;
    };
Then we define a **move constructor** to specify the way move semantics is implemented:

    MyVector(MyVector&& other) {
      swap(data_, other.data_);
    }

It's that simple. The parameter `other` is rvalue reference, indicating we are free to move it, so we just swap the pointer inside and get hold of the array stored in `other`. Now we can write `MyVector v(MyVector(10));`, where no construction occurs. By the way, this expression may seem redundant—`MyVector v(10)` would suffice here. But in practice, the rvalue in the bracket is more often provided by a non-constructor function.

Likewise, move version of `operator=` can be made.

### b. std::move()
Sometimes, an lvalue is no longer useful and we want to use it like an rvalue. `std::move` serves that purpose. Example:

    MyVector v1(10);
    // ...do something with v1
    // v1 no longer useful
    MyVector v2(std::move(v1));  // move construction

While `v1` is an lvalue, `std::move(v1)` allows using `v1` like an rvalue, so the move constructor is called. `move()` doesn't move anything, but claims an rvalue.

Another notable example is this:

    MyVector&& v1 = MyVector(10);
    MyVector v2(std::move(v1));  // not MyVector v2(v1);

Here though `v1` is an rvalue reference, `move()` is still necessary for calling move constructor, since `v1` is an lvalue. If `v2` is constructed like `MyVector v2(v1)`, copy construction occur instead.

## (4) perfect forwarding
Forwarding means passing a parameter to be processed by another function. If the rvalue/lvalue property of parameter is maintained in this process, this is a perferct forwarding. Otherwise, imperfect. Since move construction is efficient, we hope to maintain the rvalue property and keep avoiding copy overhead.

Let's start from imperfect forwarding:

    void process(int& i) {
      cout << "process(int&):" << i << endl;
    }

    void process(int&& i) {
      cout << "process(int&&):" << i << endl;
    }

    void myforward(int&& i) {
      process(i);
    }

    int main() {
        int a = 0;
        process(a); // a is lvalue; process(int&):0
        process(1); // 1 is rvalue; process(int&&):1
        process(std::move(a)); // move(a) is rvalue; process(int&&):0
        
        myforward(2);
        // rvalue 2 forwarded to process() as an lvalue, because
        // it's given the name i inside myforward()
        // process(int&):2
        
        myforward(move(a)); // ditto; process(int&):0
    }

To solve this problem, a template function `std::forward()` is provided. If its argument is an lvalue reference, it returns the argument with its type unchanged. In any other case, it returns an rvalue reference that refers to the argument. To illustrate, rewrite `myforward()`:

    void myforward(int &&i) {
      process(std::forward<int>(i));
    }

    myforward(2); // process(int&&):2

Since `i` is rvalue reference, `std::forward<int>(i)` returns an rvalue reference. Now `process()` still has an rvalue reference parameter, but the parameter is the return value of a function, which is an **rvalue**—preserving the rvalue property of `2`.

Things do not end here, because `myforward()` only accepts rvalues due to reference binding rules. To make it perfect, combine universal reference with `std::forward()`:

    template <typename T>
    // universal reference accepts both kinds
    // of references and doesn't change their type
    void perfectForward(T&& t) {
        process(forward<T>(t));
    }

    int a = 0;
    perfectForward(a);  // process(int&):0
    perfectForward(2);  // process(int&&):2

Then `perfectForward()` is indeed perfect.

### (5) a last reminder
While experimenting with copy construction like `MyVector v(MyVector(10))` without defining a move constructor, you might still find out that no copy construction occurs. That's because of the return value optimization of the compiler(RVO). Turn off RVO of `g++` with the option `-fno-elide-constructors`, then copy happens as expected.

Although the compiler has done this optimization for us, we are not sure whether this always happens, or whether this happens as we desire. That's why we need rvalue reference.

## 2. other features
### (1) nullptr
Old denotation of a null pointer is the macro `NULL`, which is `0` in essence. This can cause creepy bugs. The new denotation can compare well with other pointers, or convert to `false`, but never converts to `0`, so it's less error-prone.
### (2) binary literal value
For example, `110b` means `3`.
### (3) number delimiter
This improves readability of long numbers. The delimeter is a prime `'`, or single quotation mark. For example, `123'45'678910`. You can add the delimiter wherever you like amid the number.
### (3) raw character string
The escape character `\` often damages readability of a character string, especially in regular expressions or file paths. New feature allows writing the string as it is. The only thing to do is add an `R` before the string. For example, instead of `"D:\\MinGW\\bin\\gcc.exe"`, we can write `R"D:\MinGW\bin\gcc.exe"`.