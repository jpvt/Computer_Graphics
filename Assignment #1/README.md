# Introduction to Rasterization Algorithms

## **Abstract:** 

In this activity,  I will discuss and implement algorithms or the rasterization of points and lines. The rasterization of these primitives will be done by simulating direct access to video memory. As current operating systems protect memory from direct access, I will use a framework, provided by the professor, that simulates access to video memory.

---

## The Framework

Considering current operating systems protect memory from direct access, a framework provided by the professor will be used to simulate access to video memory. The framework files can be accessed in the [myGL Framework](https://github.com/jpvt/Computer_Graphics/tree/master/Assignment%20%231/mygl_framework) repository.

The Framework structure, dependencies and compilation instructions are described in [myGL Framework](https://github.com/jpvt/Computer_Graphics/tree/master/Assignment%20%231/mygl_framework).

---
## Introduction

### Digital Images

A digital image is composed of *pixels*, each with finite, discrete quantities of numeric representation for its intensity. The digital image contains a fixed number of rows and columns of pixels, typically stored in computer memory as a *raster image*, a two-dimensional array of small integers, each represents an associated color to a specific pixel.

Therefore, in the RGB standard, each pixel consists of three channels, each representing a color (R for red, G for green and B for blue). Usually, 8 bits are reserved for each component(channel), which is distinguished in 256 different intensity levels for each color, resulting in approximately 16 million colors reproduced in total. Additionally, channel A (alpha) can be used for transparency. Consequently, the representation of the components of an RGBA space is given as follows:

<p align="center">
  <img src="imgs/Pixel-alloc.png" >
</p>
<p align="center">
<sub>Figure 1. Representation of an RGBA image storage</sub>
</p>

<p align="center">
  <img src="imgs/RGB-space.jpg" >
</p>
<p align="center">
<sub>Figure 2. Representation of an RGB color wheel</sub>
</p>

### Putting pixels in the monitor

As seen before, a raster image is composed of a two-dimensional space, although the memory is represented linearly. Therefore, it is necessary to calculate an offset so that each pixel (given its position X and Y), occupies a single space in memory.

Consequently, an algorithm was presented in the classroom that performs such allocation, as can be exemplified in the following images:
<p align="center">
  <img src="imgs/img_storage.png" >
</p>
<p align="center">
<sub>Figure 4. Representation of the image storage</sub>
</p>

Considering that the number of pixels on the screen is equal to the number of lines multiplied by the number of columns, the memory must have this same number of positions to represent the screen linearly. Therefore, the following algorithm decides the position of each pixel and each channel of a pixel in memory, considering the width in pixels of the screen:

<p align="center">
  <img src="imgs/Pixel-alloc-alg.png" >
</p>
<p align="center">
<sub>Figure 5. Representation of the offset algorithm and color buffer</sub>
</p>

<p align="center">
  <img src="imgs/vram_storg.png" >
</p>
<p align="center">
<sub>Figure 6. Representation of the video memory screen image footprint</sub>
</p>