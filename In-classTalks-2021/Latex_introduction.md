# Latex 快速入门

Latex是一种基于ΤΕΧ的排版系统。

## Latex 代码的基本构成

```latex
\documentclass{article}

%omitted content

\begin{document}

Hello LaTex!

\end{document}

ungrammatical, but the complier doesn't care!

```



## Latex 基本版式操作

```latex
\documentclass[UTF8]{ctexart}

\title{Hello LaTex!}

\author{LambdaX}

\date{2021年3月9日}

\begin{document}
\maketitle

\tableofcontents

\section{基本排版：section和paragraph}
排版让内容有条理。

\subsection{这是“subsection”}
凡是Section，都会自动加上节号

\subsubsection{这是“subsubsection”}

\paragraph{这是个段标题}
上面是个段标题

\subparagraph{子段落：subparagraph}
Bla Bla Bla……

\subsection{又一个subsection}

\paragraph{YHL yyds！} Let's get down to the next skill.


\end{document}
```

其中，`\maketitle`生成标题、作者、日期信息；`\tableofcontents`自动生成目录

## Latex 基本数学操作

学 \LaTex ​ 大概还是用来写数学公式吧，别忘了使用

```latex
\usepackage{amsmath}
\usepackage{amsfonts}
```

### 上下标

```latex
多字母加大括号！\\
单字母：$x^2 + y^2 = z^2$ \ $x_1 + y_2 = z_3$\\
多字母:$e^{\pi i} + 1 = 0$，$y_{01} = k_{sth}^{3} \cdot x + b$\\
```

### 希腊字母

```latex
大写 A B $\Gamma \Delta $…… 
小写$\alpha \ \beta \ \gamma \ \delta$……
```

### 分式

```latex
行内：$  \frac{dy}{dx} = \frac{dy}{dt}  \frac{dt}{dx}  $  \\
行间：\[  \frac{dy}{dx} = \frac{dy}{dt}  \frac{dt}{dx}  \]
```

### 根式

```latex
$\sqrt{3} \approx 1.732$……
```

### 运算符

```latex
$\pm\; 
\times \; 
\div\; 
\cdot\; 
\cap\; 
\cup\;
\geq\; 
\leq\; 
\neq\; 
\approx \; 
\equiv$
```

### 矩阵

```latex
\[
\begin{pmatrix} a&b\\c&d \end{pmatrix} \quad
\begin{bmatrix} a&b\\c&d \end{bmatrix} \quad
\begin{Bmatrix} a&b\\c&d \end{Bmatrix} \quad
\begin{vmatrix} a&b\\c&d \end{vmatrix} \quad
\begin{Vmatrix} a&b\\c&d \end{Vmatrix} \]

\[
\begin{pmatrix} long word&b\\c&d \end{pmatrix} \]
```

### 公式组

```latex
\begin{gather}
a = b+c+d \\
x = y+z
\end{gather}

\begin{align}
a &= b+c+d \\
x &= y+z
\end{align}

\begin{gather*}
a = b+c+d \\
x = y+z
\end{gather*}

\begin{align*}
a &= b+c+d \\
x &= y+z
\end{align*}
```

### 分段函数/大括号

```latex
\[ y=
\begin{cases}
-x, \quad x \leq 0 \\
x, \quad x > 0
\end{cases} \]
```

### 集合符号

```latex
$\mathbb{R} \quad \mathbb{Q} \quad \mathbb{C} \quad \mathbb{N}$
```

## 数学之外

其他一些好玩的东西，比如代码高亮，插入图片，插入表格等等。贴上Tex源码。

```latex
\documentclass[UTF8]{ctexart}

\usepackage{graphicx}

\usepackage{listings} 
\usepackage{xcolor}
\lstset{
    columns=fixed,       
    numbers=left,                                        % 在左侧显示行号
    frame=none,                                          % 不显示背景边框
    backgroundcolor=\color[RGB]{245,245,244},            % 设定背景颜色
    keywordstyle=\color[RGB]{40,40,255},                 % 设定关键字颜色
    numberstyle=\footnotesize\color{darkgray},           % 设定行号格式
    commentstyle=\it\color[RGB]{0,96,96},                % 设置代码注释的格式
    stringstyle=\rmfamily\slshape\color[RGB]{128,0,0},   % 设置字符串格式
    showstringspaces=false,                              % 不显示字符串中的空格
    language=C++,                                        % 设置语言
}


\title{Interesting Stuff}

\author{LambdaX}

\date{2021年3月9日}

\begin{document}
\maketitle

\newpage

\section{Some Advanced Commands}

\subsection{Image Insertion}

\includegraphics[width = .8\textwidth]{test.png}

\subsection{Syntax High Light}

\begin{lstlisting}
#include <iostream>

using namespace std;

int main()
{
	cout<<"Hello from CPP!";

	return 0;
}
\end{lstlisting}

\subsection{Table}
\begin{tabular}{|l|c|r|}
 \hline
操作系统& 发行版& 编辑器\\
 \hline
Windows & MikTeX & TexMakerX \\
 \hline
Unix/Linux & teTeX & Kile \\
 \hline
Mac OS & MacTeX & TeXShop \\
 \hline
通用& TeX Live & TeXworks \\
 \hline
\end{tabular}

\end{document}

```

可以把它们复制进Tex文档中编译一下，就可以看到最终效果（Github 的Markdown不能直接兼容Latex qwq……）。



