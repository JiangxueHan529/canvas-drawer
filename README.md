# canvas-drawer

Implements a simple drawing api

![](https://github.com/JiangxueHan529/canvas-drawer/blob/main/images/cute-cat-photo.jpg)

## How to build

*Windows*

Open git bash to the directory containing this repository.

```
canvas-drawer $ mkdir build
canvas-drawer $ cd build
canvas-drawer/build $ cmake -G "Visual Studio 16 2019" ..
canvas-drawer/build $ start Draw-2D.sln
```

Your solution file should contain two projects: `pixmap_art` and `pixmap_test`.
To run from the git bash command shell, 

```
canvas-drawer/build $ ../bin/Debug/draw_test
canvas-drawer/build $ ../bin/Debug/draw_art
```

*macOS*

Open terminal to the directory containing this repository.

```
canvas-drawer $ mkdir build
canvas-drawer $ cd build
canvas-drawer/build $ cmake ..
canvas-drawer/build $ make
```

To run each program from build, you would type

```
canvas-drawer/build $ ../bin/draw_test
canvas-drawer/build $ ../bin/draw_art
```

## Supported primitives

The supported extra operations are:\
 1) Drawing circles: \
    //takes in coordinates of center of circle and radius, and calls drawC() below. The circles are hollow.\
    void draw_circle(int x, int y, int radius, int color_index);\
    void drawC(int x, int y, int x1, int y1, ppm_pixel* our_color);\
 2)Drawing Rectangles:\
     //draw_rectangle takes coordinates of center and width and height of rectangle. It is hollow.\
     //If the user wants to, call fill_rectangle to fill it with color.\
     void draw_rectangle(int cx, int xy, int w, int h);\
     void fill_rectangle(int cx, int xy, int w, int h);\
 3)Added point Primitive\
 4)User can specify line width:\
    void input_line_width(int lw);\
      

## Results

A. test images for my additional features \
test rectangle:\
![](https://github.com/JiangxueHan529/canvas-drawer/blob/main/images/test_rectangle.png)\
test circle:\
![](https://github.com/JiangxueHan529/canvas-drawer/blob/main/images/test_circle.png)\
test points:\
![](https://github.com/JiangxueHan529/canvas-drawer/blob/main/images/test_points.png)\
test wide line:\
![](https://github.com/JiangxueHan529/canvas-drawer/blob/main/images/horizontal-line-wide.png)\

B. art works\
![](https://github.com/JiangxueHan529/canvas-drawer/blob/main/images/my_art.png)\
![](https://github.com/JiangxueHan529/canvas-drawer/blob/main/images/my_art2.png)

