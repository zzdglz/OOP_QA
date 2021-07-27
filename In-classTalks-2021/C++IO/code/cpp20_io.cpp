// 目前无法编译

#include <cstdio>
#include <cstring>
#include <format>
#include <iostream>
using namespace std;

int main() {

	// 1 格式化输出
	cout << format("{:s}", true) << endl		 //  true
		 << format("{:X}", 114514) << endl		 //  1BF52
		 << format("{:+05d}", 233) << endl		 //  +0233
		 << format("{:.2f}", 3 / 14159) << endl; //  3.14

	// 2 多参数输出
	cout << format("{}, {}", 1, 'a') << endl			//  1, a
		 << format("{0:},{0:+},{0:-},{0: }", 1) << endl //  1,+1,1, 1
		 << format("{1},{0},{1}", 1, 2) << endl;		//  2,1,2

	// 3 更复杂的格式
	cout << format("{:*^6}", 'x') << endl; //  **x***

	return 0;
}