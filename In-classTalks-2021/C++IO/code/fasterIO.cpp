#include "include/error.h"
#include "include/timer.cpp"
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;
Timer timer;

#ifdef USE_BUFFER
#ifdef SMALL_BUFFER
const int str = 1 << 10;
#else
const int str = 1 << 20;
#endif
inline int gc() {
	static char buf[str], *s = buf, *t = buf;
	if (s == t) s = buf, t = s + fread(buf, 1, str, stdin);
	return s == t ? EOF : *(s++);
}
char buf[str], *s = buf, *t = buf + str;
inline void flush() { fwrite(buf, 1, s - buf, stdout), s = buf; }
inline int pc(int c) {
	if (s == t) flush();
	return *(s++) = c;
}
#else
int (*gc)(void) = getchar;
int (*pc)(int) = putchar;
#endif

template <class T>
inline void read(T &x) {
	register char c = gc(), d = 0;
	while (c < '0' || c > '9')
		d = c, c = gc();
	x = 0;
	while (c >= '0' && c <= '9')
		x = (x << 1) + (x << 3) + c - '0', c = gc();
	if (d == '-') x = -x;
}
template <class T>
inline void wt(T x) {
	if (x / 10) wt(x / 10);
	pc(x % 10 + '0');
}
template <class T>
inline void wtln(T x) {
	if (x < 0) x = -x, pc('-');
	wt(x), pc('\n');
}
template <class T>
inline void wtsp(T x) {
	if (x < 0) x = -x, pc('-');
	wt(x), pc(' ');
}

const int N = 1e6 + 10;
int n = 1e6;
int a[N];

int main() {
	freopen("data", "w", stdout);
	for (int i = 1; i <= n; ++i)
		wtln(rand());
#ifdef USE_BUFFER
	flush();
#endif
	fclose(stdout);

	// scanf
	cerr << "scanf:\tbegin" << endl;
	freopen("data", "r", stdin);
	timer.reset(), timer.start();
	for (int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	timer.stop();
	cerr << "scanf:\t" << fixed << setprecision(4) << timer.time() << endl;

	// cin
	cerr << "cin:\tbegin" << endl;
	freopen("data", "r", stdin);
	timer.reset(), timer.start();
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	timer.stop();
	cerr << "cin:\t" << fixed << setprecision(4) << timer.time() << endl;

	// fasterIO
	cerr << "fIO:\tbegin" << endl;
	freopen("data", "r", stdin);
	timer.reset(), timer.start();
	for (int i = 1; i <= n; ++i)
		read(a[i]);
	timer.stop();
	cerr << "fIO:\t" << fixed << setprecision(4) << timer.time() << endl;
}
