#include <cstdio>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;

const int BUF_SIZE = 1e5;
char buf[BUF_SIZE];
int len, ret, x, y, z;
char ch;

struct Point {
	double x, y;
} P;
istream &operator>>(istream &is, Point &p) {
	return is >> p.x >> p.y;
}
ostream &operator<<(ostream &os, const Point &p) {
	return os << "(" << p.x << "," << p.y << ")";
}

int main() {

	// 1 流与文件
	// 1.1 创建(i/o)fstream类对象并打开文件
	ifstream inputStream("input");
	ofstream outputStream;
	outputStream.open("output");
	// 1.2 关闭文件
	inputStream.close();
	outputStream.close();

	// 2 流类中的函数
	// 2.1 istream
	(cin >> x).get(ch).ignore(2, '\n').getline(buf, BUF_SIZE, '$');
	// 2.2 ostream
	cout.put('#') << "bool(cin): " << bool(cin) << endl
				  << buf << endl;

	// 3 自定义类的输入输出
	cin >> P;
	cout << P << endl;

	// 4 流操纵算子
	cout << boolalpha << true << endl;
	cout << hex << uppercase << 114514 << dec << endl;
	cout << showpos << setw(5) << internal << setfill('0') << 233 << noshowpos << endl;
	cout << fixed << setprecision(2) << 3.14159 << endl;

	return 0;
}