# This page lists the useful C++ grammars, especially for C++11, C++14, C++17 and C++20.

## Use [Regular Expressions](https://docs.microsoft.com/en-us/dotnet/standard/base-types/regular-expressions) in C++11


Include header `<regex>` for type `regex` which records the regex string, and `smatch` which manages match results.

```cpp
string baseString("OOP_QA");
regex myRegex("([A-Z]+)");  //match strings including only uppercase letters
smatch result;

for(int i=0;regex_search(baseString,result,myRegex);i++){  //search for all matched substrings
  cout<<"Group "<<i<<":"<<result[0]<<endl;  //result
  baseString=result.suffix().str();  //skip the present substring
}
```


[Reference](http://www.cplusplus.com/reference/regex/)
