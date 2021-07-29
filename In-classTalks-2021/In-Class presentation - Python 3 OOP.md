# In-Class presentation - Python 3 OOP

**Author**: Siyuan WU  
**Date**: 2021-6-5

### Syllabus

1. Python 与 C++ 基本语法对比  
2. Python 面向对象

## Python 与 C++ 基本语法对比

一、缩进具有语法和逻辑意义

1. 优点：代码美观  
2. 缺点：不按正确的缩进格式写代码会报错（unexpected indent / expected an indented block）

二、变量初始化

1. 定义变量时无需声明类型，在运行时Python解释器会根据传入参数判断变量所属类型

三、Python中的函数定义
    
    def function_name(parameter):
        <statements...>
    return value
    
四、Python中的分支、循环和枚举

1. if - elif - else  
2. while  
3. for

## Python 面向对象

### 1. 类定义、类对象

类实例化后，可以使用其属性，也可以通过类名访问其属性。

    class MyClass:
        i = 1
        def f(self):
            return 'hello world'

    x = MyClass()

    print(x.i)
    print(x.f())

以上代码创建了一个新的类实例并将该对象赋给局部变量 x，x 为空的对象。执行以上程序输出结果为：
    
    1
    hello world
    
类有一个名为 __init__() 的特殊方法（构造方法），该方法在类实例化时会自动调用。__init__() 方法可以有参数。

### 2.类的方法

在类的内部，使用 def 关键字来定义一个方法，与一般函数定义不同，类方法必须包含参数 self, 且为第一个参数，self 代表的是类的实例。

    class people: 

        name = ''
        age = 0 
    
        def __init__(self,n,a): 
            self.name = n 
            self.age = a 
            
        def speak(self): 
            print("%s is %d." %(self.name,self.age)) 
   
    p = people('Mary',10) 
    p.speak()

执行以上程序输出结果为：

    Mary is 10.
    
### 3.继承（单继承）

子类（派生类）会继承父类（基类）的属性和方法。基类必须与派生类定义在一个作用域内。除了类，还可以用表达式。

    class student(people): 
        grade = ''
        
        def __init__(self,n,a,g): 
            people.__init__(self,n,a) 
            self.grade = g 
 
        def speak(self): 
            print("%s is %d, in grade %d."%(self.name,self.age,self.grade)) 

    s = student('Tim',10,3) 
    s.speak()

执行以上程序输出结果为：

    Tim is 10, in grade 3.

### 4.继承（多继承）

Python同样支持多继承形式。多继承的类定义形如下例:

    class speaker(): 
        topic = '' 
        name = '' 
        
        def __init__(self,n,t): 
            self.name = n 
            self.topic = t 
            
        def speak(self): 
            print("I'm %s. Today I'm going to talk about %s."%(self.name,self.topic)) 

    class sample(speaker,student): 
        a ='' 
        def __init__(self,n,a,g,t): 
            student.__init__(self,n,a,g) 
            speaker.__init__(self,n,t) 

    test = sample("Lucy",25,4,"Python") 
    test.speak()

需要注意圆括号中父类的顺序，若是父类中有相同的方法名，而在子类使用时未指定，python从左至右搜索 即方法在子类中未找到时，从左到右查找父类中是否包含方法。

执行以上程序输出结果为：

    I'm Lucy. Today I'm going to talk about Python.

### 5.方法复写

super() 函数是用于调用父类(超类)的一个方法。

    class Parent:
        def myMethod(self): 
            print ('Parent') 
            
    class Child(Parent):
        def myMethod(self): 
            print ('Child') 

    c = Child()
    c.myMethod()
    super(Child,c).myMethod()

执行以上程序输出结果为：
    
    Child
    Parant

### 6.类属性与方法

1）类的私有属性

  \__private_attrs：两个下划线开头，声明该属性为私有，不能在类的外部被使用或直接访问。在类内部的方法中使用时 self.\__private_attrs。

2）类的方法

  在类的内部，使用 def 关键字来定义一个方法，与一般函数定义不同，类方法必须包含参数 self，且为第一个参数，self 代表的是类的实例。self 的名字并不是规定死的，也可以使用 this，但是最好还是按照约定使用 self。

3）类的私有方法

  \__private_method：两个下划线开头，声明该方法为私有方法，只能在类的内部调用 ，不能在类的外部调用。self.\__private_methods。

    class JustCounter: 
        __secretCount = 0
        publicCount = 0

        def count(self): 
            self.__secretCount += 1 
            self.publicCount += 1 
            print (self.__secretCount) 

    counter = JustCounter() 
    counter.count() 
    counter.count() 
    print (counter.publicCount) 
    print (counter.__secretCount) # ERROR!
    
输出为：

    1
    2
    2
    Traceback (most recent call last):
      File "test.py", line 16, in <module>
    print (counter.__secretCount)  # 报错，实例不能访问私有变量
    AttributeError: 'JustCounter' object has no attribute '__secretCount'
    
### 7.类的专有方法

\__init__ : 构造函数，在生成对象时调用  
\__del__ : 析构函数，释放对象时使用  
\__repr__ : 打印，转换  
\__setitem__ : 按照索引赋值  
\__getitem__: 按照索引获取值  
\__len__: 获得长度  
\__cmp__: 比较运算  
\__call__: 函数调用  
\__add__: 加运算  
\__sub__: 减运算  
\__mul__: 乘运算  
\__truediv__: 除运算  
\__mod__: 求余运算  
\__pow__: 乘方  

### 8.运算符重载

可以对类的专有方法进行重载，实例如下：

    class Vector: 
        def __init__(self, a, b): 
            self.a = a 
            self.b = b 

        def __str__(self): 
            return 'Vector (%d, %d)' % (self.a, self.b) 

        def __add__(self,other): 
            return Vector(self.a + other.a, self.b + other.b) 

    v1 = Vector(2,10) 
    v2 = Vector(5,-2) 
    print (v1 + v2)
    
输出为：

    Vector(7,8)
    
### 9.Python中的“多态”

一个接口，多种实现

核心：函数重载，继承的应用拓展

#### 例子1

    class Duck(object):                                  # 鸭子类
        def fly(self):
            print("鸭子沿着地面飞起来了")

    class Swan(object):                                  # 天鹅类
        def fly(self):
            print("天鹅在空中翱翔")

    class Plane(object):                                 # 飞机类
        def fly(self):
            print("飞机隆隆地起飞了")

    def fly(obj):                                        # 实现飞的功能函数
        obj.fly()

    duck = Duck()
    fly(duck)

    swan = Swan()
    fly(swan)

    plane = Plane()
    fly(plane)
    
输出结果：
    
    鸭子沿着地面飞起来了
    天鹅在空中翱翔
    飞机隆隆地起飞了
    
#### 例子2

    class gradapa(object):
        def __init__(self,money):
            self.money = money
        def p(self):
            print("this is gradapa")

    class father(gradapa):
        def __init__(self,money,job):
            super().__init__(money)
            self.job = job
        def p(self):
            print("this is father,我重写了父类的方法")

    class mother(gradapa): 
        def __init__(self, money, job):
            super().__init__(money)
            self.job = job

        def p(self):
             print("this is mother,我重写了父类的方法")
             return 100

    #定义一个函数，函数调用类中的p()方法
    def fc(obj): 
        obj.p()
    gradapa1 = gradapa(3000) 
    father1 = father(2000,"工人")
    mother1 = mother(1000,"老师")

    #这里的多态性体现是向同一个函数，传递不同参数后，可以实现不同功能.
    fc(gradapa1)
    fc(father1)
    print(fc(mother1))
    
结果：

    this is gradapa
    this is father,我重写了父类的方法
    this is mother,我重写了父类的方法
    100

## 总结

### Python特性

1. 成员变量及成员函数：
    
  默认为公有，加__前缀表示私有，_前缀表示保护
  
  多继承时，调用同名成员函数默认优先调用继承列表中靠前的类中的成员函数

2. 成员函数形参

  第一个形参一般都是self（相当于C++中的this）

  静态方法和类方法是特例（静态方法可以直接用类名调用，普通方法只能被对象调用，类方法可以被类和对象调用）

3. 继承

  仅支持公有继承

4. 多态

  多态可以应用于没有继承关系的不同类中

### C++特性

1. 成员变量与成员函数

  默认为私有

  多继承时，重名的成员函数都会被继承，之后通过作用域运算符指定特定父类的成员变量

2. 成员函数形参

  可以没有形参

3. 继承

  支持公有、私有、保护继承

4. 多态

  多态应用于有继承关系的父-子类中

## 参考资料

https://blog.csdn.net/dghggij/article/details/83513849

https://blog.csdn.net/weixin_44490853/article/details/88550076

https://blog.csdn.net/qq_43511217/article/details/88956869

https://blog.csdn.net/qq_51174011/article/details/109837257

https://www.runoob.com/python3/python3-class.html

https://blog.csdn.net/weixin_44695969/article/details/92175840
