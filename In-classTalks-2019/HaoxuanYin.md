
# Introduction to Functional Programming
**Haoxuan Yin**
Functional programming is a classic form of programming. This article gives a brief introduction to it. The codes are written in python.
## Pure Functions
### Deterministic
It returns the same result if given the same arguments.
```python
PI=3.14
def area_bad(r):
	return r*r*PI
def area_good(r,PI):
	return r*r*PI
```
### No Side Effects
It does not cause any observable side effects.
```python
x=0

def inc_bad():
	x+=1
	return x

def inc_good():
	return x+1
```
## Immutability
When data is immutable, its state cannot change after it’s created.
```python
def sum_bad(a,n):
	s=0
	for i in range(n):
		s+=a[i]
	return s

def sum_good(a,n):
	if (n==0):
		return 0
	return a[0]+sum_good(a[1:],n-1)
```
## Referential Transparency
Functions can be replaced by constants.
```python
def sum(a,b):
	return a+b
print(sum(3,5))
print(8)
```
## Functions as First Class Entities
Functions are treated as values and used as data.
```python
def sum(a,b):
	return a+b
def double(f,a,b)
	return 2*f(a,b)
print(double(sum,3,4))
```
## Important functions
### Filter
```python
def positive(x):
	return x>0
def filter_bad(a):
	b=[]
	for x in a:
		if(positive(x)):
			b.append(x)
	return b
def filter_good(a):
	return filter(positive,a)
```
### Map
```python
def map_bad(a):
	b=[]
	for s in a:
		b.append(len(s))
	return b
def map_good(a):
	return map(len,a)
```
### Reduce
```python
from functools import reduce
def add(a,b):
	return a+b
def reduce_bad(a):
	s=0
	for x in a:
		s+=x
	return s
def reduce_good(a):
	return reduce(add,a)
```
## References
[Functional Programming Principles in Javascript](https://medium.freecodecamp.org/functional-programming-principles-in-javascript-1b8fc6c3563f)

[An introduction to functional programming](https://codewords.recurse.com/issues/one/an-introduction-to-functional-programming)
