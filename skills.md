# This page lists the useful programming skills for better efficiency, preferrably with an illustrating example (最好有代码实例展示).


Use this function to input variable for better efficency.
```C++
void G (int &n) {
    bool f;
    char a;
    for (f = 0, a = getchar(); !isdigit(a); a = getchar()) if (a == '-') f = 1;
    for (; isdigit(a); a = getchar()) n = n * 10 + a - '0';
    if (f) n = -n;
}
```