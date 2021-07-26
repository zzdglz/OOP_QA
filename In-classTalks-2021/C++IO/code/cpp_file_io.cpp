#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

const int BUF_SIZE = 1e5;
char buf[BUF_SIZE];
int x, y;
char ch;

int main() {

	freopen("input", "r", stdin);
	freopen("temp", "w", stdout);
	cout << "(1) input an int: ";
	cin >> x;
	cout << x << endl;
	// // win:
	// freopen("CON","r",stdin);
	// freopen("CON","w",stdout);
	// linux:
	freopen("/dev/tty", "r", stdin);
	freopen("/dev/tty", "w", stdout);
	cout << "(2) input an int: ";
	cin >> x;
	cout << x << endl;

	// 打开输入文件
	ifstream fin("input");
	// 从输入文件读入
	fin.getline(buf, BUF_SIZE).get(ch) >> x;
	// 重新打开另一个输入文件
	fin.close();
	fin.open("input2");
	// 继续读入
	fin >> y;
	// 关闭输入文件
	fin.close();

	// 打开输出文件
	ofstream fout("output");
	// 向输出文件写入
	fout << buf << endl
		 << y << endl;
	// 重新打开另一个输出文件
	fout.close();
	fout.open("output2");
	// 继续写入
	(fout << x << endl).put(ch);
	// 关闭输出文件
	fout.close();

	return 0;
}