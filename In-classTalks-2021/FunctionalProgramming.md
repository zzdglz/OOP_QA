# Hello! Haskell

---
author: Songtao Zhou
institute: Department of Electrical Engineering
---

## Hello Haskell~

### Hello Haskell, Hello World!
    Haskell, born in 1990, a pure functional programming language. 

    A program output Hello World would be like: 


```language=Haskell
main :: IO()
main = putStrLn "Hello World!"
```

    

    解释器(ghci) \& 编译器(ghc): .hs -> .hi -> .o -> .exe


## 


### Function - First Class
    ``函数是一等公民''——
      *  函数是变量
      *  变量是函数 (preferred)
    
    函数式编程的核心在于函数，函数之于Haskell，就像半导体管之于模拟电路、门电路之于数字电路、细胞之于生命体。
    

```language=Haskell
plus1 :: Int -> Int -- Type Declaration
plus1 m = m + 1 -- Function Definition


magicCoin :: Bool -> Bool
magicCoin = (\x -> True) -- Lambda 句法

a = ((\x -> True) :: Bool -> Bool) True
```



### Multi arguments?
Haskell-Currying. Functions as arguments.
```language=Haskell
```language=Haskell
plus :: Int -> Int -> Int
plus x y = x + y

%which equals to：
plus' :: Int -> (Int -> Int)
plus' = \x -> (\y -> x + y)
```


### Purity - Once Defined, Forever Defined
*  Haskell的第二大特性，与过程式编程不同(e.g.多次赋值、经典的变量交换的容器论)
*  一经定义，无法改变，重复调用同一个函数(同一个参数)都将是同一个返回值。
*  ``变量'':常值/无参函数 $\Rightarrow$ 不允许重复赋值。
*  没有传统的循环过程

```language=Haskell    
n = 1
n = 2 -- forbidden
```




### Higher Order Functions*
    ```language=C++
    //C++ 排序算法：sort, STL
    bool cmp(int &a, int &b){
        return f(a)<f(b);
    }
        .....
        sort(A+1,A+n+1,cmp);
        .....
    
    
    把函数作为参数的思想，Haskell的基本操作：
    'map :: (a -> b) -> [a] -> [b]'
    'arr = map (\x -> x + 1) [1..10]'
    'plus1 = map (\x -> x+1)'


### Laziness
    惰性，用多少算多少，e.g.\begin{itemize}
        * 类型判断系统:
        `a = ((\x -> True) :: Bool -> Bool) True` 和`a = (\x -> True) True` 其同样效果。
        * 无限长列表：[1..] 是一个自然数集的列表，用时计算
    



## 
### Geometric sequence
    计算并输出一个等差数列 $1,q,q^2,\dots,q^n$
    
```language=Haskell
geoSeq :: Int -> Integer -> [Integer]
geoSeq n q = map (q^) [1..n]
```


时间复杂度 $O(n^2)$？


### Laziness
```language=Haskell
geoSeq = 1 : map (2*) geoSeq
```


列表的递归定义：
'data [] a = [] | a : [a]'
'(:)是一个操作符，x:xs, 1:[], 2:[1,2]'
'head (x:xs) == x, tail (x: xs) == xs'



与之类似的还有fibonacci数列：
'fibs = 0 : 1 : zipWith (+) fibs (tail fibs)'




## 
### Functional Programming
    More than meets the eye.

    Think twice, Code once.
    
    思维方式的转换，使编程更加容易.
![](pic/filterPrime.png)
![](pic/prime.png)


### Q\&A
    Any question or doubt  is welcome.
    %(感谢$n+e$提供的latex模板)



