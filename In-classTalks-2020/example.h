/**
 * @file example.h 本范例的include档案。
 *
 * 这个档案只定义example这个class。
 *
 * @author acpty
 */

#define EXAMPLE_OK  0   ///< 定义EXAMPLE_OK的宏为0。
  
/**
 * @brief Example class的简易说明
 *
 * 本范例说明Example class。
 * 这是一个极为简单的范例。
 * 
 */

class Example {
    private:
        int var1 ; ///< 这是一个private的变量
    public:
        int var2 ; ///< 这是一个public的变量
        int var3 ; ///< 这是另一个public的变量
        void ExFunc1(void); 
        int ExFunc2(int a, char b);
        char *ExFunc3(char *c) ;
};