# Complete tool list of c++ Cmath library
For me, this list is very important and usefull, previously I didn't know that some functions are already defined in Cmath, so it made me spent time on "reinventing the wheel".
1. abs( ) - returns absolute value of a number
    ```c++
    double x = -98.23, result;
    result = abs(x); // result is 98.23     
2. acos( ) - returns inverse cosine of a number (in radians) 
    ```c++
    double x = 0.0, result;
    result = acos(x); //result is 1.5708 rad
3. acosh( ) - returns inverse hyperbolic cosine (in radians)
    ```c++
    double x = 13.21, result;
    result = acosh(x); // result = 3.272 rad
    ```
4. asin() - returns inverse sine of a number
            
    ```c++
    double x = 0.5, result;
    result = asin(x); // result = 0.523599 rad
    ```

5. asinh( ) - returns inverse hyperbolic sine of a number
    ```c++
    double res = asinh(0.5); //res = 0.481212 rad
    ```
6. atan( ) -  returns inverse tangent
    ```c++
    double res = atan(1); //res = 0.785 = pi/4 rad
    ```
7. atanh() - returns inverse hyperbolic tangent
    ```c++
    double res = atanh(0.75); //res = 0.972955 rad
    ```
8. cbrt( ) - returns cube root of a number
    ```c++
    double res = cbrt(8); // res = 2.0 
    ``` 
9. ceil( ) - returns ceiling of a number
    ```c++
    int res = ceil(8.765); // res = 9
    ```
10. copysign( ) - returns num with value of first and sign of second
    ```c++
    double res = copysign(34.15, -1); // res = -34.15
    ```
11. cos( ) - cosine of a number
    ```c++
    double pi = 3.14159;
    double res = cos(pi/3); //res = 0.5
    ```
12. cosh( ) - Returns Hyperbolic Cosine of an Angle
    ```c++
    double res = cosh(4.55); //res = 47.3213
    ```
    Since the way of using is very simple and clear, thus I'll only write the names and return values of rest of the cmath functions
13. exp() - returns e^argument
14. exp1m() - returns  -1 degree of argument
15. fdim() - returns positive difference of arguments
16. floor() - returns floor value of decimanl
17. fma(a,b,c) - returns a*b+c
18. fmax(a, b) - returns largest value between two arguments
19. fmin(a, b) - returns smallest among two given arguments
20. fmod(a, b) - returns the floating point remainder of numerator/denominator
21. hypot(a, b) - returns square root of sum of square of arguments
22. ilogb(a) - returns integral part of logarithm of |a|
23. llrint(a) - rounds argument using current rounding mode
1. llround(a) - Rounds argument to nearest long long int value
1. log(a) - returns natural logarithm of a
1.log10(a) - returns base 10 logarithm of a
1. log2(a) - returns base 2 logarithm of a
1. logb(a) - returns log(|a|)
1. lround(a) - returns nearest long int value of 
1. modf() - breaks number into integral and fractional parts
    ```c++
   double x = 14.86, intPart, fractPart;
	  fractPart = modf(x, &intPart); 
   //fractPart = 0.86, intpart = 14
	  cout << x << " = " << intPart << " + " << fractPart << endl;
   ```
1. pow(a,b) - returns a^b
1. remainder(a,b) - returns remainder of a/b
1. remquo() - computes reminder and quotient of a/b
    ```c++
   int q;
   double x = 12.5, y = 2.2;   
   double result = remquo(x, y, &q);
   cout << "Remainder of " << x << "/" << y << " = " << result << endl;
   cout << "Quotient of " << x << "/" << y << " = " << q << endl << endl;  
    ```
1. round(a) - returns nearest integer value of a
1. sin(a) - returns sine of a
1. sinh(a) - returns hyperbolic sine of a
1. sqrt(a) - returns square root of a
1. tan(a) - returns tangent of a
1. tanh(a) - returns hyperbolic tangent of a 
1. trunc(a) - truncates the value after decimal and returns the integer part only
    ```c++
    int val = trunc(-34.15);  //val = -34 
    ```