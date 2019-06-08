# A Brief Introduction to TikZ

## What is TikZ?

According to its author, 'TikZ' stands for 'TikZ ist kein Zeichenprogramm', which, in English, means 'TikZ is not a graphic software'. It's named in a recursive way like GNU (GNU is Not Unix). TikZ is a software used for drawing 2d pictures. It plays the role of the frontend with PGF serving as the internal engine. TikZ has been integrated nicely with LaTeX and Beamer. It works for PS output and PDF generation.

## Basic Usage

Like other libraries of LaTeX, users have to write the following codes first before actually using TikZ:

```latex
\usepackage{tikz}
\usetikzlibrary{arrows, shapes, trees}
```

There are two types of command in TikZ, one is online command, which is used for drawing simple pictures for convenience:

```latex
\tikz \draw (0pt, 0pt) -- (100pt, 100pt) %for a straight line
\tikz \fill[red] (0,0) circle (10ex) %for filling a circle with red colour
```

Another is environmental command, where users have to put their commands in a code block:

```latex
\begin{tikzpicture}
\draw (0pt, 0pt) -- (100pt, 100pt);
\fill[red] (50pt, 0pt) circle (5ex);
\end{tikzpicture}
```

The coordinate system of TikZ starts from the lower left corner of the canvas, and canvas is a rectangle that is automatically made large enough to hold all the pictures. TikZ library 'backgrounds' helps make the canvas visible:

```latex
\usepackage{backgrounds}
\begin{tikzpicture}[show background rectangle]
\draw (0pt, 0pt) -- (100pt, 100pt);
\fill[red] (50pt, 0pt) circle (5ex);
\end{tikzpicture}
```

There are two basic elements of TikZ: path and node. A path is a series of straight and curved line segments, which can be drawn, filled and used for clipping other drawings.

```latex
\path[draw] (0cm, 0cm) -- (2cm, 2cm) -- (4cm, 0cm);
\path[draw] (0cm, 0cm) -- (2cm, 2cm) -- (4cm, 0cm) -- cycle; %making it close
\path[draw, fill = orange] (0cm, 0cm) -- (2cm, 2cm) -- (4cm, 0cm) -- cycle; %fill the triangle with orange colour
\path[draw, clip](0cm, 0cm) -- (2cm, 2cm) -- (4cm, 0cm) -- cycle;
\path[draw] (2cm, 0cm)--(4cm, 2cm)--(6cm, 0cm) -- cycle; %clip this triangle into the last one
```

We can draw curved lines by specifying some control points to indicate the change of direction:

```latex
\path[draw, line width = 2pt] (0,0)..controls(2cm, 2cm)..(4cm, 0cm) 
```

Nodes are added to a path after the path is drawn. We can name these nodes for later reference. The protocol for using a node is:\path[Opt] (x,y) node[Opt] (node name) {TeX contents}

An example:

```latex
\path[draw] (0,0) node[draw](nodeA){$A^2$}--(2,2)--(4,0)
node[circle, fill = red](nodeB){$B^2$};
\path[draw, ->, line width = 2pt] (nodeA)..controls(2,-2)..(nodeB); 
```

We can define  named nodes first before connecting them , then the paths around the nodes are clipped.  The protocol for defining a node is:\node[Opt] (node name) at (x,y) {TeX contents}

An example:

```latex
\tikzstyle{every node} = {circle, fill=gray};
\node (a) at (0,0) {A};
\node (b) at +(0:2) {B};
\node (c) at +(60:2) {C};
\foreach \from/\to in {a/b, b/c, c/a}
	\draw[->] (\from)--(\to);
```

## Concrete Example

We can use TikZ to draw a UML class diagram:

```latex
\begin{tikzpicture}[scale = 1.5, transform shape]
\tikzstyle{class}=[rectangle, draw=black, rounded corners, fill=blue!40, drop shadow,text centered, anchor=north, text=white, text width=3cm]
\tikzstyle{adapter}=[rectangle, draw=black, rounded corners, fill=green, drop shadow,text centered, anchor=north, text=white, text width=3cm]%specify some style for class and adapter, to make it colorful and good-looking
 \node (BaseClass) [class, rectangle, rectangle split, rectangle split parts=2, text centered, text width = 3cm]
        {
            \textbf{BaseStack}
            \nodepart{second}push(...)
            \par pop()
        };%node of base class
\node (ConpClass) [class, rectangle, rectangle split, rectangle split parts=2, text centered, text width = 3cm] at(6cm, -1.5cm)
        {
            \textbf{vector$<$int$>$}
            \nodepart{second}push\_back()
            \par pop\_back()
            \par ...
        };%node of adaptee
\node (Adapter) [adapter, rectangle, rectangle split, rectangle split parts=3, text centered, text width = 3cm] at(0cm, -3cm)
        {
            \textbf{VectorStack}
            \nodepart{second}push(...)
            \par pop()
            \nodepart{third}m\_data
        };%node of adpater

%connect them together
\draw[->, >=open triangle 90, thick] (Adapter) -- (BaseClass);
\draw[->, thick] (Adapter.east) -- ++(1.5cm, 0cm) -- ++(0, 1.5cm) -- (ConpClass.west); 

\end{tikzpicture}
```

