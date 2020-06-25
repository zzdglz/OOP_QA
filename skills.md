# This page lists the useful programming skills for better efficiency, preferrably with an illustrating example (最好有代码实例展示).

## Log files

When programming, especially doing large projects, log files will be helpful for debugging. Do some output at certain points to files which are called "log files" using "fstream". This allows you to keep track of the running program and get to know where it stops without changing the original output of the program. Make sure when you have fixed all the bugs, it's easy to delete or comment the output code.

## Friend classes

Friend classes are not used often, but using them between classes which are closely connected can make coding easier and also save runtime. Friend classes can directly access the members of other classes, so when you need to change some private members(for example, sorting arrays), you can do it directly instead of using the interfaces. This saves runtime when you need to do this a lot of times in the program.
