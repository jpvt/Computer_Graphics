# The Framework

## Framework Structure
 
 * **core.h:** contains macros that determine the dimensions of the window in pixels.
 * **frame_buffer.h:** declares the fb_ptr pointer, which points to the first byte of the color buffer. The position pointed to by fb_ptr corresponds to the coordinate pixel (0,0), located in the upper corner left of the window. Each pixel has 4 color components (Red, Green, Blue, Alpha), each represented by 1 byte (unsigned char).
 * **main.c and main.h:** define functions and variables necessary to simulate access to video memory.
 * **Makefile:** suggested compilation procedure for Unix systems.
 * **mygl.h:** contains the declaration of the function MyGlDraw (), responsible for invoking the raster functions that I will develop. It is also in this file that I will declare the functions developed.
 * **mygl.c:** where the raster functions will be defined. This file also contains the definition of the MyGlDraw () function, whose body I changed so that my raster functions are properly invoked.

---

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
$ ./mygl
```