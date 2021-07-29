#include <cstdio>
#include <cstring>

const int BUF_SIZE = 1e5;
char buf[BUF_SIZE];
int x, y;
char ch;

int main() {
	freopen("input", "r", stdin);
	freopen("temp", "w", stdout);
	printf("(1) input an int: ");
	scanf("%d", &x);
	printf("%d\n", x);
	// // win:
	// freopen("CON","r",stdin);
	// freopen("CON","w",stdout);
	// linux:
	freopen("/dev/tty", "r", stdin);
	freopen("/dev/tty", "w", stdout);
	printf("(2) input an int: ");
	scanf("%d", &x);
	printf("%d\n", x);

	// 打开输入文件
	FILE *inputFile = fopen("input", "r");
	// 从输入文件读入
	fgets(buf, BUF_SIZE, inputFile);
	ch = fgetc(inputFile);
	fscanf(inputFile, "%d", &x);
	// 重新打开另一个输入文件
	freopen("input2", "r", inputFile);
	// 继续读入
	fscanf(inputFile, "%d", &y);
	// 关闭输入文件
	fclose(inputFile);

	// 打开输出文件
	FILE *outputFile = fopen("output", "w");
	// 向输出文件写入
	fputs(buf, outputFile);
	fprintf(outputFile, "%d\n", y);
	// 重新打开另一个输出文件
	freopen("output2", "w", outputFile);
	// 继续写入
	fprintf(outputFile, "%d\n", x);
	fputc(ch, outputFile);
	// 关闭输出文件
	fclose(outputFile);

	return 0;
}