# Cmake
Author: Zhang Yipeng
## What is CMake?
* CMake is a cross-platform installation (compilation) tool that can describe the installation (compilation process) of all platforms in simple statements.
* It can be considered a top-level management tool for 'make', because one of its direct functions is to help us generate makefile files.

## Why CMake?
* CMake is cross-platform
* CMake can manage large projects
* Easy to use
* High efficiency
## How to use CMake?

### Step1 Download and compile and run CMake
* Download cmake of the corresponding system from https://cmake.org and install it according to different tips.
* After installation, if you can't find the 'cmake' command, it may because that the path has not been configured successfully, and you need to configure the path manually.
* For Mac, CMake also gives other two methods that can install CMake for command line use.
### Step2 Write a CmakeLists.txt
#### For a simple project that has only one source file
##### introduction
* Assuming that there is only one source file in our project. We just need to add a CMakeLists.txt to this dirctory. And here are some grammars we need to use.
##### grammer
* cmake_minimum_required( VERSION )  
It sets up the minimum CMake version required for a project. Although cmakelists are case-insensitive in most cases, 'VERSION' must use capital letters.

* project( NAME )  
It names the whole project.

* set( \<variable> \<value> )  
Set the value of variable \<variable> to \<value>. Something interesting is that variables in cmake are very similar to strings in c++, so this variable can store either the name of a file or the path of the file. 

* add_executable( \<name> source1 source2 source3 ...)  
Introduce an executable file for the project using the given source file.

* aux_source_directory( \<dir> \<variable> )  
It will collect the file names of all source files under the specified path and store the output results list in the specified variable.
##### example
* For example, there is only one file named main.cpp in a project. You just need to write the CMakeLists.txt shown below in the directory where the file is located.
> cmake_minimum_required( VERSION 2.6 )  
> PROJECT( HELLO )  
> SET( src main.cpp )  
> ADD_EXECUTABLE( HELLO main.cpp )  

* Or if you have many different files such as main.cpp、a.cpp、b.cpp and so on in one directory. The last command is useful in this case. Here is an example.

> cmake_minimum_required( VERSION 2.6 )  
> PROJECT( test )  
> #SET( src_list a.cpp b.cpp main.cpp )  
> aux_source_directory( . src_list )  
> ADD_EXECUTABLE( test ${src_list} )
* ps:The content after the '#' symbol is the annotated content. In other words, the contents of the third and fourth lines are equivalent, but the second is more concise.


#### For multi-source file directories
##### introduction
If you have a subdirectory in the root directory and both of them have some files of a project. Then we need to write CMakelists.txt in each directory.

##### grammer
* add_subdirectory( source_dir )  
Add a subdirectory.
* target_link_libraries( target item1 item2... )  
Link a given library to a target.
* add_library( \<name> source1 source2... )  
Add a library named \<name> to the project using the specified source file.

##### example
* For example, if you have a project in the root directory and some files needed in the subdirectory of the root directory. Then you need to write something like this in the root directory:
> PROJECT( main )  
> CMAKE_MINIMUM_REQUIRED( VERSION 2.6 )  
> ADD_SUBDIRECTORY( subdirectory )  
> AUX_SOURCE_DIRECTORY( . DIR_SRCS )  
> ADD_EXECUTABLE( main ${DIR_SRCS} )  
> TARGET_LINK_LIBRARIES( main Test )
* And something like this in the subdirectory:
> AUX_SOURCE_DIRECTORY( . DIR_TEST_SRCS )  
> ADD_LIBRARY( Test ${DIR_TEST_DIR} )  
#### For some project which needs another link libraries
##### introduction
* In many cases, we need to use third-party libraries(.dll .so .dylib etc.)
* If we want to use them, we need to know  

	1.where to find the header file.  
	2.where to find the library.  
	3.what is the name of the library.
	
* Even using CMake, these things will not change.
##### grammer
* message( "message" )  
Print the message on the screen.
* find_path( \<variable> \<name> path1 path2... )    
It will search the header file named \<name> in the provided path and save the final path in the variable \<variable>.

* find_library( \<variable> name path1 path2... )  
Finding library file \<variable> in the given path. 

* find_package( name )  
Load third party libraries.

* include_directories( dir1 dir2... )  
Add a path list containing header files.

##### example
* For example, if you want to use a library named libz3.You need to three things.
* First, create a directory cmake/modules under the root directory. However,it's not a rule but just a conventional practice.
* Then, create a FindlibNAME.cmake in this directory
> MESSAGE( STATUS "Findlibz3.cmake..." )  
> FIND_PATH(   
>   LIBZ3_INCLUDE_DIR  
>	z3++.h  
>	/usr/local/include/  
> )  
> 
> FIND_LIBRARY(  
> 	LIBZ3_LIBRARIES  
> 	libz3.dylib  
> 	/usr/local/lib/  
> )  

* And last, you need to write a CMakeLists.txt like this in the root directory.
> PROJECT( main )  
> cmake_minimum_required( VERSION 2.6 )  
> set( CMAKE_SOURCE_DIR . )  
> set( CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules )   
> message( STATUS "module path ok!" )  
> message( ${CMAKE_MODULE_PATH} )  
> aux_source_directory( . DIR_SRCS )  
> add_executable( main ${DIR_SRCS} )  
> find_package( libz3 REQUIRED )  
> if( LIBZ3_INCLUDE_DIR AND LIBZ3_LIBRARIES )  
> message( STATUS "Found libz3!" )  
> message( ${LIBZ3_INCLUDE_DIR} )  
> include_directories( ${LIBZ3_INCLUDE_DIR} )  
> message( ${LIBZ3_LIBRARIES} )  
> target_link_libraries( main ${LIBZ3_LIBRARIES} )  
> endif( LIBZ3_INCLUDE_DIR AND LIBZ3_LIBRARIES )

### Step3 Compile and run
* It is a good habit to use the following commands to create a folder named "build" and generate makefiles in this folder. In this way, the generation file and the source file can be separated which is easy to manage.
> mkdir build  
> cd build  
> cmake ..  
> make 

## Summary
* As a cross-platform compilation tool, more and more projects are using cmake, making cmake more and more mainstream tools.
