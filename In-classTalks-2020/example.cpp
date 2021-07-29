 /**
 * @file example.cpp 本范例的程序代码档案。
 *
 * 这个档案用来定义example这个class的member function。
 *
 * @author acpty
 */

/**
 * @brief ExFunc1()的简易说明
 * 
 * ExFunc1()没有任何参数及返回值
 */
int Example::ExFunc1() {
    // empty function.
}

/**
 * @brief ExFunc2()的简易说明
 *
 * ExFunc2()返回两个参数相加的值。
 *
 * @param a 用来相加的参数。
 * @param b 用来相加的参数。
 * @return 返回两个参数相加的结果。
 */
int Example::ExFunc2(int a, char b)
{
    return (a+b);
}
/**
 * @brief ExFunc3()的简易说明
 *
 * ExFunc3()只返回参数输入的指标。
 *
 * @param c 传进的字符指针。
 * @retval NULL 空字符串。
 * @retval !NULL 非空字符串。
 */
char * Example::ExFunc3(char * c)
{
    return c;
}