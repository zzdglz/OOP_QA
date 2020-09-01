# This page lists the useful programming skills for better efficiency, preferrably with an illustrating example (最好有代码实例展示).

There are some good habit for better efficiency:
### 1. Use ++i instead of i++ except that you have a reason todo that.
++i have a better efficiency than i++.

>for(int i = 0; i < 10; ++i)

instead of

>for(int i =  0; i < 10; i++)

### 2. Use bit operations
When the operation involves powers of two, the bit operation can be used to solve the problem.  
For example, you can use a int as a bool[32].

### 3. inline、const、&
+ Whenever you use a variable that never change, you'd better declare it as a const.
+ And for those function less than 10 lines, declare them as inline can improve the efficiency. 
+ For those large objects, it is costly to copy. So it better to use reference.

### 4. Decline the use of division
use a * b = c instead of a = c / b because computers are less efficient at division.