# Setting up Modern OpenGL on Linux

In this article I'll show how to set up Modern OpenGL on Linux and how to run a simple image.

## Dependencies
The compilation of the project requires that OpenGL headers and GLUT (The OpenGL Toolkit)
installed.

### Dependencies Installation on Linux

**Debian, Ubuntu**
```
$ sudo apt-get install build-essential libgl1-mesa-dev
$ sudo apt-get install libglew-dev libsdl2-dev libsdl2-image-dev libglm-dev libfreetype6-dev
```

**Fedora**
```
$ sudo dnf install make gcc-c++
$ sudo dnf install glew-devel SDL2-devel SDL2_image-devel glm-devel freetype-devel
```
If GLM is not available in your distribution repository, you have the option to install it manually. Make sure the headers end in the */usr/include/glm directory*. Since it's a headers-only library, you do not need to compile a .so library - just copy the code there.


### Check your OpenGL installation

```
$ glxinfo | grep OpenGL
```

---

## Compilation Instructions

**Compilation**
```
$ make
```

**Cleaning**
```
$ make clean
```

**Run**
```
$ ./moderngl_hello_world
```

## Example

<p align="center">
<strong>The result should be something like this:</strong>
</p>

<div align="center">
  <a href="https://www.youtube.com/watch?v=Ug2uIIbkVcU"><img src="https://img.youtube.com/vi/Ug2uIIbkVcU/0.jpg" alt="Modern OpenGL"></a>
</div>

<p align="center">
Click on the image to check de video
</p>

