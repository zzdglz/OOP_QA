#Why I'm not "using namespace std"
Previously, I was thinking that its very convenient to write ```using namespace std;``` and after that use any function or data structure in STL without writing ```std::```.
And there can be illusion that the code looks cleaner with ```using namespace std;```.

Lets see an example
```c++
    using namespace std;
    vector<int> str = {1,9, 7, 81, 12, 2, 5, 0};
    sort(str.begin(), str.end());
    cout<<"Size of array  is "<<str.size()<<endl;
    cout<<"Elements of this array are` ";
    for(int i:str)  cout<<i<<", ";
    cout<<endl;
```
now, without using the namespace`
```c++
    std::vector<int> str = {1,9, 7, 81, 12, 2, 5, 0};
    std::sort(str.begin(), str.end());
    std::cout<<"Size of array  is "<<str.size()<<std::endl;
    std::cout<<"Elements of this array are` ";
    for(int i:str)  std::cout<<i<<", ";
    std::cout<<std::endl;
```
First of all, of course first one is shorter and simpler to write, but there are certain problems behind it.
The real problem can happen when we include external libraries for some big projects and there will be function or operator with the same name, the compiler will no longer be able to choose which one choose and execute, and it can lead to errors, or in the worst case the wrong one will be called, and in future it will be extremely hard to debug and find where is the mistake.

Another problem of using it is that by looking agt the code we can't determine which functions are defined by us and which are in stl.
Of course this is not big issue when we write small exercises or tasks, but dealing with big projects and many people working together, it will cause many misunderstandings. This is why companies mostly dont recomend to their programmers to ```using namespace std;```. And at the end, if we want to write everything in google coding style, then should never write that part in out code, especially in header files.