# Shell Programming
**Author**:  Biru Yang        **Date**: 2020.4.27



## *1*. Concept Introduction


### *1. 1*  Kernel and Shell

In Linux Operating systems, we have 2 opposing concepts: *kernel* and *shell*. 

+ **Kernel** is the core of the Linux system. It controls all of the hardware and software on the computer system, manages memory and file, allocates hardware, and executes software.
+ **Shell** is a special interactive utility. It provides a way for users to start programs, manage files and processes. 

---

### *1.2*  Different Shells for Different Systems

**Different operational systems have different shells** as listed below. 

+ *DOS/Windows 95/Windows 98* : command.com
+ *Windows 2000/XP/2003* : cmd.exe
+ *Linux* ：
   + Command Line Interface : Bourne shell--*sh*, Bourne again shell--*bash*, C shell--*csh*, K shell--*ksh*. 
   + Graphical User Interface : CDE, GNOME, KDE.

In this article, we’ll focus mainly on the **CLI Linux shells**, whose core is the command prompt. 
Below is a table illustrating the differences between different CLI Linux shells.
Name|Characteristics
:-:|-
Bourne Shell(/bin/sh)|1979, Stephen Bourne; The first properly programmable shell.
C Shell(/usr/bin/csh)|1980s, Bill Joy;  Easier to use for interactive designs; Similar to C.
Korn Shell(/usr/bin/ksh)|1980s, David Korn; Merges Bourne ~ with C ~.
Bourne Again ~(/bin/bash)|1987, Brian Fox; An extension of Bourne ~. (by default)


> Note: Our following examples will be built on **bash shell**, as it is the default shell for most Linux systems.
---



## *2.* Getting to Know Shell

Now let’s get more detailed and practical with shell programming.

The Linux command line (*already discussed in class*) is the basis of shell programming, and we're all familiar with using the different commands for copying/moving/renaming files, displaying the running programs or killing processes.

But shell actually has **more powerful** usage. It is a ***script language***, with which you can write shell script similar to .cpp files and perform more complicated tasks while interacting with kernel. 

The main goal of shell programming is to ***automate administrative tasks*** using *shell scripts*. 

### *2.1*  What is a Shell Script

Generally when we use the terminal, we type the command one by one, line by line and the shell provides feedback at once. But sometimes we want to run **multiple commands**. 

In the interactive shell, there is a way to implement this, which is to *separate the different commands by semi-colon* ：

> `date ; who`

However, that can be messy. Instead, we have a shell script, which simply ***lists the commands*** we want in a file that will be run by the shell.

```bash
#!/bin/bash
# THIS IS A COMMENT LINE.
# This script displays the date and who's logged in.
date
who
```

---

### *2.2*  Grammar

The grammar is rather simple. 

+ At the first line of the shell script, we specify the shell used in this session. 
`#!/bin/bash`

+ ***'#' at any line other than the first*** indicates that this is a ***comment***. 
  `# This is a comment. `

+ For the rest part, we just ***write commands the same way we used to write them***. 

  ```bash
  # echo sentences
  echo -n "The time and date are:"
  date
  ```
  ```bash
  # display user information from the system
  # use $ to print data with variables
  echo UID: $UID
  echo HOME: $HOME
  ```
  
  ```bash
  # Do most of the things we do with variables in c++.
  var1=10
  var2=-57
  var3="testing"
  
  # 1. print a variable
  echo  "The value of var3 is $var3"
  # 2. assign them to each other
  var3=$var1
  # 3. do math
  var3=[ $var2 + $var1 ]
  # 4. extract information for different uses
  today=`date +%y%m%d`
  ls /usr/bin -al > log.$today
  ```

+ We also have different conditional structures such as "if-then", "if-then-else", "for" and etc., with their pseudo code shown below:

  ```pseudocode
  //if-then structure
  if command
  then
  	command(s)
  fi
  ```

  ```pseudocode
  //if-then-else structure
  if command
  then
  	command(s)
  else
  	command(s)
  fi
  ```

  ```pseudocode
  //for structure
  for var in list
  do
  	command(s)
  done
  ```

  

---

### *2.3*  What MORE can you do

Shell script provides a lot of different features. 

For ***simple uses***, we can:

- redirect and control the format for input and output

- create functions and libraries

- add color to scripts

- use regular expressions to change or search text

With more practice, we can use it for ***more sophisticated purposes***, such as:

+ *Interact*: handle user input and present data;
+ Apply it for Database, Web and E-mail;
+ Monitor system statistics and perform backups.



## *3.* Reference

For anyone who’s planning to learn more, you can check these references listed below: 

> (1) *Linux Command Line and Shell Scripting Bible*, Richard Blum
>
> (2) commandlinefu.com – collects concise commands in Linux
>
> (3) theunixschool.com
>
> (4) BashPitfalls – a collection of common and important mistakes