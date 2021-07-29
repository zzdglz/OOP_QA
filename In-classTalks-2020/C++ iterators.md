# C++ iterators
*Zhou Yongxiao*    4/21/2020

___
[TOC]
### What is an iterator?

___

- Any object that works like a pointer is an iterator. 
  
  >In other words, it's a generalized pointer. 
- It points to some element in a range of elements like arrays, containers or more complicated data structures.
- It allows you to traverse a set of elements, using operators like ++, -- etc.

#### Iterator categories

| Categories              | Valid expressions/operators | Special ones                      | Corresponding STL containers    |
| ----------------------- | :-------------------------- | --------------------------------- | ------------------------------- |
| Input/Output iterators  | ++it, it++, *, ->, ==, !=   | \                                 | \                               |
| Forward iterators       | ++it, it++, *, ->, ==, !=   | \                                 | forward list, unordered set/map |
| Bidirectional iterators | ++it, it++, *, ->, ==, !=   | --it, it--                        | list                            |
| Random access iterators | ++it, it++, *, ->, ==, !=   | it + n, >, <, >=,<= , +=, -=, [ ] | vector, array and deque         |

#### Create const iterators

1. Use cbegin() and cend() funcitons  of  STL containers
```cpp
int main(){
	typedef vector<string> Stringvector;
	Stringvector v = { "a", "b", "c" };
	for(auto it = v.cbegin(); it!=v.cend(); ++it){
	  //vector<string>::iterator it = v.cbegin()......
	  *it += "tail";//error!We can't modify the elements using const iterators
        }
}
```
2. Define the iterator as a const_iterator
```cpp
int main(){
	typedef vector<string> Stringvector;
	Stringvector v = { "a", "b", "c" };
	for(Stringvector::const_iterator it = v.begin(); it!=v.cend(); ++it){
	  *it += "tail";//error!
        }
}
```
3. A const container offers a const iterator when invoking begin() and end() functions
```cpp
int main(){
	typedef vector<string> Stringvector;
	const Stringvector v = { "a", "b", "c" };
	for(auto it = v.begin(); it!=v.end(); ++it){
	  *it += "tail";//error!
        }
}
```

### Why do we use iterators?

___

- A key concept in our OOP design and STL. 
  
  > Data hiding ; Easy to write and understand
- Robust when potential changes exist
  
  > Less errors when traversing complicated data structrues compared with using pointers
- Bridge algorithms and containers
  
  >"Containers store data , iterators get the access and algorithms play with iterators.”


### Further discussion

___

- Iterator design pattern
- How to combine containers , iterators  and algorithms to finish our projects.
- Any mistake or drawback in this talk


### References in this talk

___

[1] Beginning C  17, 5th Edition
[2]http://www.cplusplus.com/reference/iterator/
[3]https://wenku.baidu.com/view/a5f1c411e518964bcf847c75.html?fr=search
[4] https://github.com/hailongyao/OOP_QA/blob/master/In-classTalks-2019/Iterators%20in%20C%2B%2B.md
[5]https://www.cnblogs.com/hdk1993/p/4419779.html
[6]https://www.cnblogs.com/linuxAndMcu/p/10258285.html



