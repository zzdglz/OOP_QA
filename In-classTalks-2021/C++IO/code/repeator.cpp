#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

int n;

int main() {

#ifndef CPP

	// 1 C风格 复读机
	puts("[C style repeator]");
	while (~scanf("%d", &n)) {
		printf("%d\n", n);
	}

#else

	// 2 C++风格 复读机
	cout << "[CPP style repeator]" << endl;
	while (cin >> n) {
		cout << n << endl;
	}

#endif
	return 0;
}