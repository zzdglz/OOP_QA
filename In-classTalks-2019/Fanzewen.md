# Introduction to TeX Typesetting

Fanzewen | Jun 2019

## Boxes

### Boxes

Boxes in TeX are two-dimensional things with a rectangular shape.

### `\hbox`

`\hbox` creates a box in which the elements are pieced together horizontally.

For example (code and result):

```latex
\hbox{A line of type.}
```

---

![](http://latex.codecogs.com/gif.latex?\hbox{A%20line%20of%20type.})

---

### `\kern`

In horizontal mode or restricted horizontal mode, `\kern <dimen>` means to insert blank space of `<dimen>`.

For example:


```latex
\hbox{A\kern 1cm B}
\hbox{A\kern -1cm B}
```

---

![](http://latex.codecogs.com/gif.latex?\hbox{A\kern%201cm%20B})

![](http://latex.codecogs.com/gif.latex?\hbox{A\kern%20-1cm%20B})

---

### `\raise` and `\lower`

`\raise <dimen> \*box{}` means that the box `\*box{}` is to be raised by `<dimen>`.

`\lower <dimen> \*box{}` means that the box `\*box{}` is to be lowered by `<dimen>`.

For example:

```latex
\hbox{T\kern -.1667em\lower .5ex\hbox{E}\kern -.125em X}
```

---

![](http://latex.codecogs.com/gif.latex?\hbox{T\kern-.1667em\lower.5ex\hbox{E}\kern-.125em%20X})

---

### `\vbox`

`\vbox` creates a box in which the elements are pieced together vertically.

For example:

```latex
\vbox{\hbox{Two lines}\hbox{of type.}}
```

---

![](http://latex.codecogs.com/gif.latex?\vbox{\hbox{Two%20lines}\hbox{of%20type.}})

---


### `\kern`

In vertical mode or internal vertical mode, `\kern <dimen>` means to insert vertical blank space of `<dimen>`.

For example:

```latex
\vbox{\hbox{A}\kern 1cm\hbox{B}}
```

---

![](http://latex.codecogs.com/gif.latex?\vbox{\hbox{A}\kern%201cm\hbox{B}})

---

## Glues

### Glues

When TeX makes a large box from a horizontal or vertical list of smaller boxes, there often is glue between the smaller boxes.

### `\hskip` and `\vskip`

Horizontal glue is created by writing

```latex
\hskip <dimen> [plus <dimen>] [minus <dimen>]
```

Vertical glue is created by writing

```latex
\vskip <dimen> [plus <dimen>] [minus <dimen>]
```

The first `<dimen>` is called the normal-space component of glue.

### Natural Width

From now on, take horizontal boxes as example.

The natural width of the box contents is determined by adding up the widths of the boxes and kerns inside, together with the natural widths of all the glue inside.

### Restrictions

`\hbox to <dimen>{}` creates a box whose width is `<dimen>`.

`\hbox spread <dimen>{}` creates a box whose width is a `<dimen>` more than the natural width of the contents.

TeX calculates the box's natural width, stretchability and shrinkability first.

If needed, the glue will be stretched or shrinked proportionally.

For example:

```latex
\hbox spread 0cm{A\hskip 1cm plus 1cm B\hskip 1cm plus 3cm C}
\hbox spread 2cm{A\hskip 1cm plus 1cm B\hskip 1cm plus 3cm C}
\hbox spread 4cm{A\hskip 1cm plus 1cm B\hskip 1cm plus 3cm C}
```

---

![](http://latex.codecogs.com/gif.latex?\hbox%20spread%200cm{A\hskip%201cm%20plus%201cm%20B\hskip%201cm%20plus%203cm%20C})

![](http://latex.codecogs.com/gif.latex?\hbox%20spread%202cm{A\hskip%201cm%20plus%201cm%20B\hskip%201cm%20plus%203cm%20C})

![](http://latex.codecogs.com/gif.latex?\hbox%20spread%204cm{A\hskip%201cm%20plus%201cm%20B\hskip%201cm%20plus%203cm%20C})

---

### `\hfil` and `\hfill`

`\hfil` and `\hfill` are infinitely stretchable glue.

`\hfill` is more infinite than `\hfil`.

For example:

```latex
\hbox spread 10cm{A\hskip 0cm plus 1cm B\hfil C}
\hbox spread 10cm{A\hfill B\hfil C}
\hbox spread 10cm{A\hfil B\hfil\hfil C}
```

---

![](http://latex.codecogs.com/gif.latex?\hbox%20spread%2010cm{A\hskip%200cm%20plus%201cm%20B\hfil%20C})

![](http://latex.codecogs.com/gif.latex?\hbox%20spread%2010cm{A\hfill%20B\hfil%20C})

![](http://latex.codecogs.com/gif.latex?\hbox%20spread%2010cm{A\hfil%20B\hfil\hfil%20C})

---

### `\hss` and `\vss`

`\hss` and `\vss` are infinitely shrinkable glue.

## References

Donald E. Knuth. The TeX book.
