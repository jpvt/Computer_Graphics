# Introduction to Rasterization Algorithms

## **Abstract:** 

In this activity,  I will discuss and implement algorithms or the rasterization of points and lines. The rasterization of these primitives will be done by simulating direct access to video memory. As current operating systems protect memory from direct access, I will use a framework, provided by the professor, that simulates access to video memory.

---

## The Framework

Considering current operating systems protect memory from direct access, a framework provided by the professor will be used to simulate access to video memory. The framework files can be accessed in the [myGL Framework](https://github.com/jpvt/Computer_Graphics/tree/master/Assignment%20%231/mygl_framework) repository.

The Framework structure, dependencies and compilation instructions are described in [myGL Framework](https://github.com/jpvt/Computer_Graphics/tree/master/Assignment%20%231/mygl_framework).

---

**NOTE:** This is the short version of the assignment's article. If you want the long version explaining all the details about digital images and rasterization, please access the [long version](https://github.com/jpvt/Computer_Graphics/blob/master/Assignment%20%231/article.md).

## Features

 * **PutPixel:** Rasterizes a point in the video memory that receives as parameters as x (y) coordinates of the pixel on the screen and its color (RGBA).
 * **DrawLine:** Rasterizes a line on the screen, taking as parameters the coordinates of its initial and final vertices (represented by tuples (x0, y0) and (x1, y1) respectively) and the colors (in RGBA format) of each vertex. The colors of the pixels along the rasterized line were obtained by linear interpolation of the colors of the vertices. The line rasterization was made through Bresenham's Algorithm.
 * **DrawTriangle:** Function that draws as parts of a triangle on the screen, taking as parameters as positions of three vertices (x0, y0), (x1, y1) and (x2, y2) as well the colors (RGBA) of each of the vertices. As pixel centers of the edges of the triangle, they must be activated from the linear interpolation of the colors of their vertices.