# This page lists the useful programming skills for better efficiency, preferrably with an illustrating example (最好有代码实例展示).

## 1. Minimalize the use of if/else branches

If there are are many *else* branches, and the test-condition is very close to the last *else* branch, the CPU may spending lots of time jumping from one *else* to another *else*. If possible, convert to a *switch* statement, then CPU only need to execute one jump with a lookup table.