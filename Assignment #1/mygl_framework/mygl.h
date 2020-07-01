#ifndef MYGL_H
#define MYGL_H

#include "core.h"
#include "frame_buffer.h"

// Structs implemented by me
typedef struct Tuple{
    unsigned int x;
    unsigned int y;
}tuple_t;

typedef struct RGBA_Colors{
    unsigned int red;
    unsigned int green;
    unsigned int blue;
    unsigned int alpha;
}colors_t;

typedef struct Pixel{
    tuple_t coord;
    colors_t rgba;
}pixel_t;

void MyGlDraw(void);

//
// >>> Functions implemented by me <<
pixel_t SetPixel(unsigned int x, unsigned int y, unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha);
void PutPixel(pixel_t pixel);
void DrawLine(pixel_t pi, pixel_t pf);
void LinearColorInterpolation(pixel_t pi, pixel_t * p_aux ,pixel_t pf);
void DrawPixelLineY(pixel_t pi, pixel_t pf);
void DrawPixelLineX(pixel_t pi, pixel_t pf);
void DrawTriangle(pixel_t v1, pixel_t v2, pixel_t v3);
void DrawCustomTriangle();
void DrawColoredFrame();
//

#endif  // MYGL_H
