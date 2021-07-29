#include <cstdio>
#include <cstring>

const int BUF_SIZE = 1e5;
char buf[BUF_SIZE];
int len, ret, x, y, z;
char ch;

int main() {

	// 1 文件访问操作
	// 1.1 打开文件
	FILE *inputFile = fopen("input", "r");
	// 1.2 重新打开文件
	freopen("input2", "r", inputFile);
	// 1.3 关闭文件
	fclose(inputFile);

	// 2 文件读写操作
	// // 2.1 直接读取
	// len = fread(buf, sizeof(char), BUF_SIZE, stdin);
	// // 2.2 直接写入
	// fwrite(buf, sizeof(char), len, stdout);
	// 2.3 读\写 字符\字符串
	ch = getchar(), putchar(ch);
	ch = fgetc(stdin), putc(ch, stdout);
	gets(buf), puts(buf); // gets 在C++14中被移除
	fgets(buf, BUF_SIZE, stdin), fputs(buf, stdout);

	// 3 格式化IO
	// 3.1 格式化输入
	ret = scanf("%d%d%d", &x, &y, &z);
	printf("return value: %d\n", ret);
	ret = scanf("\n(%d,%d)", &x, &y);
	printf("return value: %d\n", ret);
	// 3.2 格式化输出
	ret = printf("%s\n", true ? "true" : "false");
	printf("return value: %d\n", ret);
	printf("%X %x\n", 114514, 114514);
	printf("%+05d\n", 233);
	printf("%.2f\n", 3.14159);

	return 0;
}