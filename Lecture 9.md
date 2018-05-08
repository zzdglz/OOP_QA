# Lecture 9
##	Virtual function (虚函数)
#### 1.	Please give an example to explain polymorphism (多态性).

	#include <iostream>
	using namespace std;
	enum note { middleC, Csharp, Eflat };
	class Instrument {
	public:
	  virtual void play(note) const{ cout<< "Instrument::play" <<endl; }
	};
	class Wind : public Instrument {
	public:
	  void play(note) const{ cout<< "Wind::play" <<endl; }
	};
	void tune(Instrument&i) {
	i.play(middleC);
	}
	int main() {
	  Wind flute;
	  tune(flute); // Upcasting
	}

The output is “Wind::play”.


#### 2. Is it necessary to redefine a virtual function in derived class (派生类)? And is the keyword virtual necessary in redefining the virtual function in derived class?

- No. If the base class is virtual, the derived class will automatically becomes virtual, whether it is needed to place the virtual keyword is case-dependent. 
- The keyword virtual is not necessary.When one wants the virtual function to be further “modified”, he or she should keep the keyword. While on the other hand, if the virtual function is not intended to be extensible, he or she should remove that keyword.
	
#### 3. What is the meaning of keyword final? What problem will be caused without it? Please give an example showing a typical situation that keyword final is necessary.

- the derived class can't overload the virtual function, and it can avoid a class to be inherit. 
- Problem will occur when user overload a function improperly. When we don't want a class or virtual be inherit or overload, we can use final.
- Example: class B inherits from class A, and class C inherits from B. func is a virtual function in A and is overridden in B, while it is not expected to be overridden in B’s child classes. Then we should use final for func in B for safety.

#### 4. What is the meaning of keyword override? What problem will be caused without it? Please give an example of a typical situation that keyword override is necessary.

- The redefinition of a virtual function in a derived class.
- When we require polymorphism, override is necessary.
- For example, using override can highlight that you are genius.
		class Man {
		public:
		  virtual void speak() { cout << “I am a man.” << endl; }
		}
		
		class Genius {
		public:
		  void speak() { cout << “I am a genius.” << endl; }
		}
		
		void foo(Man& m) {
		  m.speak();
		}



##	Late binding (后期绑定)
#### 5. Please explain the difference between early binding and late binding.

- Early binding: binding is performed during compilation before the program runs. General functions use early binging.
- Late binding: binding occurs during runtime, according to the original type of the object. Late binding is enabled by virtual function, by declaring functions as virtual in base class.


#### 6. What kind of functions are bond with early binding? And what functions are bond with late binding?
- Non-virtual functions are bond with early binding.
- virtual functions (including normal member functions and destructors) are late bound because of the need of run-time polymorphism.

#### 7. Does late binding work for objects? How about pointers and references?

- It doesn't work for objects, because one kind of objects have the same VPtr. But it work for pointers and references.

##	VTABLE (虚函数表) and VPTR (虚函数指针)
#### 8. What are VTABLE and VPTR? Where are they stored in? 

- VTABLE: a table for each class to store the addresses of virtual functions.
- VPTR: each class with virtual functions and each object of the class contain a pointer pointing to VTABLE.
- VTABLE is built in the memory grobal data area, and VPTR is stored in each object.

#### 9. How do VTABLE and VPTR enable polymorphism?

- For virtual function call (虚函数调用) by base-class pointer, the compiler inserts code to get VPTR and find the function address in VTABLE.
- During compilation (编译期间): the compiler determines the contents of the VTABLE
- During runtime (运行期间), VTABLE is built in the memory, and VPTR is stored in each object

##	Pure virtual function (纯虚函数) and abstract class (抽象类)
#### 10. Why pure virtual functions (纯虚函数) are necessary in some cases? Please give an example of pure virtual function.
- Some classes serve as APIs and are not implemented (and hence should not be constructed directly). So it is good to declare the functions “pure” to make the compiler recognize that the class is abstract.

		Example:
		class FileHandle {
		public:
		   void set_name();
		   virtual void get_data() =0;
		};



#### 11. What is an abstract class?

- A class with pure virtual functions. It can provide a kind of common solution to some classes. It can make interfaces cleaner.

#### 12. Please explain the purpose and advantages of abstract class.

- Purpose:
  - Only provide interfaces for derived classes, prepared for upcasting, program to the interface.
- Advantages:
  - Avoid object slicing: ensure that only pointers and references can be upcasted; provide interfaces for derived classes, prepared for upcasting, program to the interface.
 - Easy for code reuse.Easy for incremental development.


#### 13. Can pure virtual function have function body? What is the purpose to provide a function body for a pure virtual function?
- Yes, it can. 
- Providing a function body for pure virtual function can reuse these code, which is good for programming.

#### 14. Please give an example where a derived class of an abstract class is still an abstract class.
	//Example:
	class FileHandle {
	public:
	   void set_name();
	   virtual void get_data() =0;
	   virtual void process() = 0;
	};
	class RemoteFileHandle: public FileHandle {
	public:
	   void get_data(); 
	}


