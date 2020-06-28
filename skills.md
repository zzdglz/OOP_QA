# This page lists the useful programming skills for better efficiency, preferrably with an illustrating example (最好有代码实例展示).

## vector对象的清空

对vector对象vec调用``clear``方法时，是不能释放其存储的内存的。如果要释放其内存，可以使用下面的方法：

```c++
vec.swap(vector<int>());
```

