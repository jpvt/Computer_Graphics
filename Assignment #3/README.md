# The Graphics Pipeline


## **Abstract**

In this assignment, I will implement geometric transformations that make up the structure of the graphic pipeline. This implementation will be done with the help of the GLM library and its execution will occur in the OpenGL shaders. This activity will be done from a C++ template code provided by the professor, which is available in the [course's repository](https://github.com/capagot/icg).

NOTE: This is the short version of the assignment's article. If you want the long version explaining details about the graphics pipeline, please access the [long version](article.md) (**UNDER CONSTRUCTION**).

---
## **Dependencies and Compilation Instructions**

All requirements for this assignment are described in [Assignment #2 README](https://github.com/jpvt/Computer_Graphics/blob/master/Assignment%20%232/README.md). Check it out!

The compilation instructions are described in the README of the respective code folders.

---
## **Introduction**

In the context of computer graphics, the graphics pipeline is a conceptual model that describes what steps a graphics system needs to perform to render a 3D scene to a 2D screen. It consists of a series of algebraic transformations that are divided into a few stages.

<p align="center">
  <img src="imgs/graphicsPipeline.png" >
</p>
<p align="center">
    <sub>Figure 1. Representation of the graphics pipeline</sub>
</p>

---

## **Geometric Transformations**

To go through the graphics pipeline, geometric transformations are made from one space to another. Most of these transformations are made by a linear operator, which in this case will be a matrix over the vectors that compose an object, transforming them from one vector space to another. The main transformations that will be covered in this article are:

* Scale;
* Shear;
* Rotation;
* Translatation.

Geometric transformations can be classified as:

* **Linear transformations:**
  - Maps straight lines to straight lines;
  - Can be expressed in matrix form;
  - Examples:
    * Scale, rotation and shear.
  
* **Affine transformations:**
  - Include all linear transformations;
  - Preserves parallelism between lines;
  - Examples:
    * Scale, rotation, shear and *translation*.

* **Projective transformations:**
  - Include all affine transformations;
  - Keep straight lines straight;
  - Do not preserve parallelism between lines;
  - Examples:
    * Scale, rotation, shear, translation and *homogeneous projection*. 

<p align="center">
  <img src="imgs/classTrans.png" >
</p>
<p align="center">
    <sub>Figure 9. Geometric transformation Classification</sub>
</p>

---

## **The Assignment**

The activity consists of changing, in the template program, the contents of the MModel, MView, and MProjection matrices so that the program generates the images specified in each exercise. This assignment uses only the scene described below.


## Scene
The scene consists of two triangles (red and blue), with the red triangle slightly ahead of the blue triangle concerning the camera.

<p align="center">
  <img src="imgs/scene.png" >
</p>
<p align="center">
    <sub>Figure 10. The Scene</sub>
</p>

The geometric configuration of the rendered scene can be seen in the following images:

<p align="center">
  <img src="imgs/planoXY.png" >
</p>
<p align="center">
    <sub>Figure 11. XY plane (negative Z axis into the image plane)</sub>
</p>


<p align="center">
  <img src="imgs/XYZ.png" >
</p>
<p align="center">
    <sub>Figure 12. XYZ axes visualization</sub>
</p>


<p align="center">
  <img src="imgs/ZY.png" >
</p>
<p align="center">
    <sub>Figure 13. ZY plane (negative X axis into the image plane)</sub>
</p>

## Exercise 1: Scale

In this exercise, I had to modify the Matrix model with the following scale factors: 

<p align="center">
  <img src="https://latex.codecogs.com/gif.latex?%5Cinline%20%28x%2C%20y%2C%20z%29%20%3D%20%28%5Cfrac%7B1%7D%7B3%7D%2C%20%5Cfrac%7B3%7D%7B2%7D%2C%201%29" >
</p>

Scaling affects the dimensions of an object so that each coordinate of a vector **A** is multiplied by its scalars. So this transformation can change the length and even direction of a vector.

<p align="center">
  <img src="https://latex.codecogs.com/gif.latex?%5Cbegin%7Bbmatrix%7D%20x%27%5C%5C%20y%27%5C%5C%20z%27%5C%5C%201%20%5Cend%7Bbmatrix%7D%20%3D%20%5Cbegin%7Bbmatrix%7D%20S_x%20%260%20%260%20%260%20%5C%5C%200%26%20S_y%20%260%20%260%20%5C%5C%200%26%200%26%20S_z%260%20%5C%5C%200%26%200%26%200%20%261%20%5Cend%7Bbmatrix%7D%20%5Ccdot%20%5Cbegin%7Bbmatrix%7D%20x%5C%5C%20y%5C%5C%20z%5C%5C%201%20%5Cend%7Bbmatrix%7D" >
</p>

Then, by replacing the scalar values with those requested in the exercise

<p align="center">
  <img src="https://latex.codecogs.com/gif.latex?%5Cbegin%7Bbmatrix%7D%20%5Cfrac%7Bx%7D%7B3%7D%5C%5C%20%5Cfrac%7B3y%7D%7B2%7D%5C%5C%20z%5C%5C%201%20%5Cend%7Bbmatrix%7D%20%3D%20%5Cbegin%7Bbmatrix%7D%20%5Cfrac%7B1%7D%7B3%7D%20%260%20%260%20%260%20%5C%5C%200%26%20%5Cfrac%7B3%7D%7B2%7D%20%260%20%260%20%5C%5C%200%26%200%26%201%260%20%5C%5C%200%26%200%26%200%20%261%20%5Cend%7Bbmatrix%7D%20%5Ccdot%20%5Cbegin%7Bbmatrix%7D%20x%5C%5C%20y%5C%5C%20z%5C%5C%201%20%5Cend%7Bbmatrix%7D" >
</p>

<p align="center">
  <img src="imgs/code1.png" >
</p>
<p align="center">
    <sub>Figure 14. Matrix model modification in code</sub>
</p>

The result is:

<p align="center">
  <img src="imgs/quest1.png" >
</p>
<p align="center">
    <sub>Figure 15. Exercise 1 result</sub>
</p>

## Exercise 2: Translation

In this exercise, I had to modify the Matrix model with the following translation:

<p align="center">
  <img src="https://latex.codecogs.com/gif.latex?%28x%2C%20y%2C%20z%29%20%3D%20%281%2C%200%2C%200%29" >
</p>

The translation is an affine transformation, so to do it, it is necessary to modify the homogeneous coordinate.

<p align="center">
  <img src="https://latex.codecogs.com/gif.latex?%5Cbegin%7Bbmatrix%7D%20x%27%5C%5C%20y%27%5C%5C%20z%27%5C%5C%201%20%5Cend%7Bbmatrix%7D%20%3D%20%5Cbegin%7Bbmatrix%7D%201%20%260%20%260%20%26T_x%20%5C%5C%200%26%201%20%260%20%26T_y%20%5C%5C%200%26%200%26%201%26T_z%20%5C%5C%200%26%200%26%200%20%261%20%5Cend%7Bbmatrix%7D%20%5Ccdot%20%5Cbegin%7Bbmatrix%7D%20x%5C%5C%20y%5C%5C%20z%5C%5C%201%20%5Cend%7Bbmatrix%7D" >
</p>

Then, by modifying the Matrix model with the values specified in the exercise:

<p align="center">
  <img src="https://latex.codecogs.com/gif.latex?%5Cbegin%7Bbmatrix%7D%20x%27%5C%5C%20y%27%5C%5C%20z%27%5C%5C%201%20%5Cend%7Bbmatrix%7D%20%3D%20%5Cbegin%7Bbmatrix%7D%201%20%260%20%260%20%261%20%5C%5C%200%26%201%20%260%20%260%20%5C%5C%200%26%200%26%201%260%20%5C%5C%200%26%200%26%200%20%261%20%5Cend%7Bbmatrix%7D%20%5Ccdot%20%5Cbegin%7Bbmatrix%7D%20x%5C%5C%20y%5C%5C%20z%5C%5C%201%20%5Cend%7Bbmatrix%7D" >
</p>

<p align="center">
  <img src="imgs/code2.png" >
</p>
<p align="center">
    <sub>Figure 16. Matrix model modification in code for exercise 2</sub>
</p>

The result is:

<p align="center">
  <img src="imgs/quest2.png" >
</p>
<p align="center">
    <sub>Figure 17. Exercise 2 result</sub>
</p>

Note that:

<p align="center">
  <img src="imgs/exmp.png" >
</p>

is equal to:

<p align="center">
  <img src="imgs/exmpcode.png" >
</p>

## Exercise 3: Perspective Projection

In this exercise, I had to modify the projection matrix so that it considers the
camera at the origin of its coordinate system and that *d* is the distance from the projection center to the origin of the camera's coordinate system. *d* is equal to **0.5**.

<p align="center">
  <img src="imgs/mproj.png" >
</p>

Then, by modifying the Matrix projection as specified in the exercise:


<p align="center">
  <img src="imgs/code3.png" >
</p>
<p align="center">
    <sub>Figure 18. Matrix projection modification in code </sub>
</p>

The result is:

<p align="center">
  <img src="imgs/quest3.png" >
</p>
<p align="center">
    <sub>Figure 19. Exercise 3 result</sub>
</p>

## Exercise 4: Camera Position

In this exercise, I had to keep the modifications in the Matrix projection made in the previous exercise and modify the Matrix View so that the image results equal to the image below. 

<p align="center">
  <img src="imgs/objective.png" >
</p>
<p align="center">
    <sub>Figure 20. Camera position = (-0.1, 0.1, 0.25); Camera Up = (0, 1, 0), Camera target = (0, 0, 0)</sub>
</p>

To define a camera which will capture the scene we want, it is necessary to define its axes through the information that is necessary to generate it. That is:

* Camera position: The point relative to its position;
* Camera Target: the point where it is looking;
* Direction: The distance between target and position;
* Vector UP: a vector that represents what it would be to "lookup" in the Universe Space, which, in this case, it is taken to be equal to the unit vector that represents the y-axis of the Universe.

<p align="center">
  <img src="https://latex.codecogs.com/gif.latex?%5C%5CPosition%20%3D%20%28p_x%2C%20p_y%2C%20p_z%29%5C%5C%20Target%20%3D%20%28l_x%2C%20l_y%2C%20l_z%29%5C%5C%20Direction%20%3D%20%28l_x%20-%20p_x%2C%20l_y%20-%20p_y%2C%20l_z%20-%20p_z%29%5C%5C%20VectorUP%20%3D%20%28u_x%2C%20u_y%2C%20u_z%29" >
</p>

**Defining the axis**:

Each axis can be calculated with the following:

<p align="center">
  <img src="imgs/axisView.png" >
</p>

<p align="center">
  <img src="imgs/axisExmp.png" >
</p>

After this procedure, it is necessary to build the matrices that will form the View.

* **Matrix B:**
Represents the Universe coordinate system points in the new system related to Camera Space.

<p align="center">
  <img src="imgs/matrixB.png" >
</p>

* **Matrix T:**
Used to translate all vertices with the position point to position the camera at the origin.

<p align="center">
  <img src="imgs/matrixT.png" >
</p>

* **Matrix View:**
To combine such matrices and generate the Matrix view, it is only necessary to multiply one by the other.

<p align="center">
  <img src="imgs/mview.png" >
</p>

By doing this modifications in code:

<p align="center">
  <img src="imgs/code4.png" >
</p>
<p align="center">
    <sub>Figure 21. Matrix view modification in code </sub>
</p>

The result is:

<p align="center">
  <img src="imgs/quest4.png" >
</p>
<p align="center">
    <sub>Figure 22. Exercise 4 result</sub>
</p>


## **Credits**

* [Graphics Pipeline Wikipedia](https://en.wikipedia.org/wiki/Graphics_pipeline)
* [Pipeline Gráfico - Raul Britto](http://raulbritto.blogspot.com/2016/10/pipeline-grafico.html)
* [Chapter 6 - Fundamentals of Computer Graphics - Peter Shirley](https://www.amazon.com.br/dp/B009TG9NIQ/ref=dp-kindle-redirect?_encoding=UTF8&btkr=1s)