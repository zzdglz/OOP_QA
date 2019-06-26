# Regex

#### Haoyang Peng

## C++ 11's New Feature

 A useful tool to process strings

## What is "Regex"?

Regex is the abbreviation of “Regular Expression”.

To be short, Regex is a kind of “match pattern”.

It’s used to match,find and replace texts that complies to the given patterns.

It’s very useful in linux text edition and long characters’ matching.

Let’s get to see an easy example. 

### For example

##### I give a string like this:

I love OOP

##### How can I match it with regex patterns?

##### We can use the pattern below:(in Windows, C++)

```c++
[A-Z]\\s\\w+\\s[A-Z]{3} \\this pattern may be different in python
```

##### But this pattern can also match these strings:

I love YOU

U AREAGOOD MAN

## So, it's very important to know some match patterns before we get to learn regex!

### Regex consists of two parts: normal characters and metacharacters.

#### Metacharacters are the reason why regex is so powerful.

### Here are some useful metacharacters.They are widely used in regex pattern.

.(dot):match all characters except \n and \r.

\w: match all characters and numbers

\d: match all numbers

\s: match tab,space,enter and other invisible chars.

+:will match as many elements as the patterns shows. [\\w](file://w)+ can match “a”,”abc”,”fdfsdfgsgdf”

(more than once!!)

{}:tell how many elements I need. \\w{3} can match “car”,”dog”,but can’t match”dfasds”.

{n,}，{n,m}: can restrict the numbers

*:match patterns before it with any times. Equals to {0,}

[]:match elements appear in it. [ABCD] can match A,B,C,D.[a-z] can match a-z.But only onr char!

[^] match elements that don’t appear in []. 

？：match patterns before it 0 or once. Equal to {0,1}

\W:match all characters except A-Za-z0-9. 

^,$:^matches the begin, $matches the end.

## Greedy Rule

#### When we use "+" in regex patterns, something happens……

oooo. Different regex:

“o+”

“o+？”

What will be the result？

#### Notice that with "?",regex patterns won't match in the greedy way!!

## C++ 11's Regex:

C++ supports ECMAscripts,awk,grep,basic and other grammar. The default one is ECMAscripts.

#### <font color=#008000>When using regex, don't forget to include "regex"!!</font>

## Useful regex functions

#### These functions make regex patterns much more useful!!

### 1.regex_match

#### It compares a string with a given regex, and returns bools.

Notice:It compares all the characters in the given strings!

Let's see an example:

```c++
#include<iostream>

#include<regex>

using namespace std;

int main(){

  string str="I love OOP";

  regex r("[A-Z]\\s\\w+\\s[A-Z]{3}");

  if(regex_match(str,r))

​	  cout<<"yes"<<endl;

  return 0;

}
```

##### The output is "yes"!!

### 2.regex_search

#### It can extract matched parts of a given string and save the data in a special class called "smatch"

Use this function we can now see greedy rules more clearly.

```c++
#include<iostream>
#include<regex>
using namespace std;

int main(){
	string s="hello";
	regex r("\\w{3,}?");//if I delete the ？,what will it match？
	smatch mat;
	if(regex_search(s,mat,r)){
		for(smatch::iterator iter=mat.begin();iter!=mat.end();++iter)
			cout<<*iter<<endl;
	}
	return 0;
} 

```

The output is "hel".

##### If  I delete the "?" then it will output "hello", which proves how greedy rule works in regex.

##### This function is overridden. There are many other ways to use it. 

<font color=red>***regex_match must match the whole string, but regex_search can only matches part of the string!!***</font>

### The class "smatch"

#### It’s a special container to store the match results.

In fact, we can store the result when using regex_match by giving arguments like this:

```C++
regex_match(string,smatch,regex)
```

Let's see how this works with smatch.

```C++
#include<regex>
#include<iostream>
#include<string.h>
using namespace std;

int main(){
	regex r("(ftp|http|https)://((\\w+\\.)*(\\w*))/(\\w{3})");
	string s="http://www.foo.com/bar"; 
	smatch mat;
	int i=0;
	regex_search(s,mat,r);
	for(smatch::iterator iter=mat.begin();iter!=mat.end();++iter){
	cout<<mat[i]<<endl;
	i+=1;
    }
	return 0;
}

```

The results are showed below:

```
regex r("(ftp|http|https)://((\\w+\\.)*(\w*))/(\\w{3})"); 

String s="http://www.foo.com/bar"; 

matches[0] = "http://www.foo.com/bar "

matches[1] = "http "

matches[2] = "www.foo.com"

matches[3] = "foo."

matches[4] = "com" 

matches[5] = "bar“
```

###### Notice that there are N+1 members, because the string itself is in it!

Smatch will store strings in"()" metacharacter in the patterns from outside to inside.

### 3.regex_replace

#### This function is used to replace a given string with a regex and a format string. 

Let's see the example!

```C++
#include <iostream>
#include <regex>
using namespace std;

int main() {
    string str = "11sigal22husigalhu33",str1="";
    str1 = regex_replace(str,regex("s(igal)h(u)"),"SS$1HH$2");
    cout<<str1<<endl;
}

```

The outputs are:

11sigal22huSSigalHHu33

##### Notice this function has to be used with "()" metacharacter. "$"+"i" means the ith strings  "()" contains in the regex patterns! It replaces the string it matches with the given format string.

#### regex_replace can also be used to change the sequences of the strings by moving strings contained in the "()" metacharacter.

### All in all, regex needs using with these aforementioned three functions. Other languages such as python also support regex.









