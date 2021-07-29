## Memory Leak

***

### what is memory leak

​	Wikipedia: In computer science, a memory leak is a type of resource leak that occurs when a computer program incorrectly manages memory allocations in such a way that memory which is no longer needed is not released.

```c++
#include <iostream>
using namespace std;

int main() {
  while (1) {
    new int[1000000];
  }
  return 0;
}
```

```c++
#include <iostream>
using namespace std;
        
int main() {
  int* array = new int[1000000];
  delete array;  // should be delete[]
  return 0;
}
```

**Both of them are dangerous!**

### how do we find memory leaks

#### use built-in function

```c++
#include <iostream>
#include <new.h>
using namespace std;
        
void check() { cout << "ERROR:out of memory!" << endl; }
        
int main() {
  set_new_handler(check); 
  while (1) {
    new int[1000000];
  }
  return 0;
}
```

#### valgrind

```
valgrind --tool=memcheck --leak-check=full ./mem_leak
```

```
==605== LEAK SUMMARY:
==605==    definitely lost: 10 bytes in 1 blocks
==605==    indirectly lost: 0 bytes in 0 blocks
==605==      possibly lost: 0 bytes in 0 blocks
```

### smart pointer

#### unique\_ptr

- unique\_ptr objects automatically delete the object they manage using a deleter as soon as they themselves are destroyed
- no other managed pointer should point to its managed object

```c++
#include <iostream>
#include <memory>
using namespace std;

int main() {
  unique_ptr<int> p1(new int(1));
  cout << "p1 value: " << *p1 << endl;
  // unique_ptr<int> p2 = p1;        // compile error
  unique_ptr<int> p2 = move(p1);
  cout << "p2 value: " << *p2 << endl;
  return 0;
}
```

#### shared_ptr&weak_ptr

- Objects of shared\_ptr types have the ability of taking ownership of a pointer and share that ownership: once they take ownership, the group of owners of a pointer become responsible for its deletion when the last one of them releases that ownership
- weak_ptr, is able to share pointers with shared_ptr objects without owning them

```c++
#include <iostream>
#include <memory>
using namespace std;

int main() {
  shared_ptr<int> p1(new int(4));
  cout << p1.use_count() << ' ' << endl;
  {
    shared_ptr<int> p2 = p1;
    cout << p1.use_count() << ' ';
    cout << p2.use_count() << ' ';
    cout << *p2 << endl;
  }
  cout << p1.use_count() << ' ';
  cout << *p1 << endl;
  return 0;
}
```

```c++
// weak.h
#include <iostream>
#include <memory>

class B;

class A {
  std::shared_ptr<B> b;

 public:
  A() { std::cout << "A constructing" << std::endl; }
  ~A() { std::cout << "A destructing" << std::endl; }
  void setB(std::shared_ptr<B> c) { b = c; }
};

class B {
  // std::shared_ptr<A> a;
  std::weak_ptr<A> a;

 public:
  B() { std::cout << "B constructing" << std::endl; }
  ~B() { std::cout << "B destructing" << std::endl; }
  // void setA(std::shared_ptr<A> c) { a = c; }
  void setA(std::weak_ptr<A> c) { a = c; }
};
```

```c++
#include "weak.h"

#include <memory>
using namespace std;

int main() {
  shared_ptr<A> p1(new A());
  shared_ptr<B> p2(new B());
  p1->setB(p2);
  p2->setA(p1);
  return 0;
}
```

### conclusion

**Treat your memory seriously**

### references

- http://www.cplusplus.com/reference/memory/
- https://blog.csdn.net/rikeyone/article/details/90071208