# Regular Expression

Author: <u>Zhang Xinwei</u>  

Institution: <u>School of Software</u>

## What is Regular Expression

WikiPedia:

> A regular expression, regex or regexp is a sequence of characters that defien a search pattern.

It is used for

* String search algorithms
* Input validation

## Where is Regular Expression

Many languages support regex, you can use regex in the following way:

* C++

  `#include <regex>`

* python

  `import re`

* java

  `import java.util.regex;`

## Single String, Wild Card and Choose Operator

* A single string can match itself.
*  A wild card(`.`) matches any single character. 
* A choose operator(`|`) matches either the expression before or the expression after the operator.

For example

* `python` matches `python`
* `a.b` matches `acb`, `adb`
* `a.b` can’t match `ab` , `addb`
*   `abc|def` matches `abc`or `def`

## Group and Character Set

### Group

`( )` deﬁnes a marked subexpression. The string matched within the parentheses can be recalled later.

### Character Set

* `[ ]` matches a single character that is contained within the brackets. 
*  `[ˆ ]` matches a single character that is not contained within the brackets.

For example

* `a(b|c)d` matches `abd` , or `acd` .
*  `[abx-z]` matches `a` , `b` , `x` , `y` , `z` .
* `[ˆa-z]` matches any single character that is not a lowercase letter from ”a” to ”z”.

## Quantifier

A quantiﬁer after a token (such as a character) or group speciﬁes how often that a preceding element is allowed to occur.

*  `?` indicates **zero or one** occurrences of the preceding element. 
*  `*` indicates **zero or more** occurrences of the preceding element. 
*  `+` indicates **one or more** occurrences of the preceding element. 
*  `{n}` The preceding item is matched **exactly n times**. 
*  `{n, }` The preceding item is matched **n or more times**. 
*  `{n, m}` The preceding item is matched **at least n times, but not more than m times**.

For example

*  `colou?r` matches `color` and `colour` . 
* `ab*c` matches `ac` , `abc` , `abbc` , ··· 
* `ab+c` matches `abc` , `abbc` , ···, but not `ac` .
*  `(ab){3, 5}` matches `ababab` , `abababab` , `ababababab` .

## \d, \s and \w

* `\d` matches a digit, same as `[0-9]` in ASCII. 
* `\D` matches a non-digit, same as `[ˆ0-9]` in ASCII. 
* `\s` matches a whitespace character, such as tab, line feed, form feed, carriage return, and space in ASCII. 
* `\S` matches anything **BUT** a whitespace.
* `\w` matches an alphanumeric character, including `_` , same as `[A-Za-z0-9 ]` in ASCII. 
* `\W` matches a non-alphanumeric character, excluding , same as `[ˆA-Za-z0-9 ]` in ASCII.

## Locator

*  `ˆ` matches the beginning of a line or string.
* `$` matches the end of a line or string.
*  `\A` matches the beginning of a string (but not an internal line). 
*  `\z` matches the end of a string (but not an internal line). 
*  `\b` matches a zero-width boundary between a word-class character and either a non-word class character or an edge. 
*  `\B` is opposite to `\b`

## \

If we want to match those specific character? Use `\`!

Use `\` before `.` , `(` , `)` , `+` , `?` , `*` , `{`, `}`, `[` , `]` , `|`, ··· 

For example

If we want to match `python.org`

* `python.org` matches `python.org`, `pythonaorg`, `pythonborg`, ···
* `python\.org` is what we want.

## Greedy and Lazy

In Python and some other implementations (e.g. Java), `*` , `+` , `?` are greedy by default because they match as many characters as possible.

For example

The regex `”.+”` applied to the string

`”Ganymede,” he continued, ”is the largest moon in the Solar System.” `

matches the entire line instead of matching only the ﬁrst word.

By appending a `?` , the regex `”.+?”` matching as few characters as possible, only `”Ganymede,”` .

## Some Examples

### Extract argument value from url

The given url looks like:

`https://www.baidu.com/s?ie=utf-8&tn=baidu&wd=regex`

If we want to extract the argument `wd`, the regex below can be used:

`(\\?|&)wd=([ˆ&]*)(&|$)`

### IP address

An IP address looks like:

XXX.XXX.XXX.XXX, XXX $\in$ [0,255] 

The number between 250 and 255 can be written as: `25[0-5] `

Similarly, numbers between 200 and 249: `2[0-4]\d`

Numbers between 100 and 199: `1\d{2}`

Numbers between 0 and 99: `[1-9]?\d`

Therefore  each part of the IP address (XXX mentioned above) can be written as:

 `((25[0-5]|2[0-4]\d|((1\d{2})|([1-9]?\d)))`

And the entire one is:

 `(((25[0-5]|2[0-4]\d|((1\d{2})|([1-9]?\d)))\.){3}((25[0-5]|2[0-4]\d|((1\d{2})|([1-9]?\d)))`