## Inclass Talk - Introduction to Libraries

*胡学浚 2019013270*

#### 1. Why we use libraries

* We don’t want to write every code from scratch!

* “Stop Trying to Reinvent the Wheel.” (不要重复造轮子)

* Libraries are packages of codes meant to be reused.

* Also, it prevents the code from being exposed.

#### 2. Static and Dynamic Libraries

* Static Libraries(archive) 
  * compiled and linked directly into your program
  * become part of the executable
  * Extension
    * .lib (Windows)
    * lib*.a (Linux & MacOS)
  * If multiple programs depend on the same static library, there’ll be multiple copies
  * When the library has changed, you need to recompile the executable

* Dynamic Libraries
  * loaded into your applications at runtime
  * remain as a separate unit
    * .dll & .lib (Windows)
    * lib*.so (Linux)
    * .so & .dylib (MacOS)
  * If multiple programs depend on the same dynamic library, there will be only one copy and it can be shared.
  * Loaded during execution
  * When the library has changed, just replace it.

#### 3. Creating Libraries (Examples are under linux)

* Static: Use 'ar' command to pack the object files(.o)

  ```Shell
  g++ -c book.cpp -o book.o
  ar -rsv libbook.a book.o
  ```

* Dynamic: Add '-fPIC' and '-shared' command in your g++ command.

  ```shell
  g++ -fPIC -shared book.cpp -o libbook.so
  ```

#### 4. Compile with Libraries

* use '-l*' option to include the libraries, while * is the name of library without the prefix 'lib'.

* use '-L*' to add a directory to search for libraries.

  ```shell
  g++ main.cpp -L. -lbook -o main
  ```

* Be careful of the order you include all the libraries, write more rudimentary libraries later.
  * Some compilers will search each libraries in the order you write them, write libraries containing definition later than those containing declaration.
  * Good under some compilers (e.g. Clang).

#### 5. Include Dynamic Libraries

* When you execute a program depending on a dynamic library, system will try to find the library in environment variable `$LD_LIBRARY_PATH`.

  ```Shell
  export LD_LIBRARY_PATH=~/librarydirectory:$LD_LIBRARY_PATH
  ```

#### 6.  Libraries Depending on Another Library?

* Lib1 depends on Lib2
* Lib1 is **Static**
  * Lib1 will not include Lib2, no matter which type Lib2 is. Add Lib2 during compilation.
  * After compilation, only Lib2 may be required if it's dynamic.

* Lib1 and Lib2 are  **Dynamic**
  * Both of them will be need both during compilation and later uses.

* Lib1 is **Dynamic** while Lib2 is **Static**
  * Lib2 will be included in Lib1, so after you've got Lib2, Lib1 is of no use.

#### 7. Finding out the Dependencies

* Possible command
  * ldd
  * objdump
  * readelf

