#include "mygl.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//
// >>> Functions Implemented by me <<< 
/* Function that sets pixel coordinates and rgba values*/
pixel_t SetPixel(unsigned int x, unsigned int y, unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha){
    pixel_t pixel;

    pixel.coord.x = x; //Defines X position
    pixel.coord.y = y; //Defines y position

    pixel.rgba.red = red; //Defines red intensity
    pixel.rgba.green = green; //Defines green intensity
    pixel.rgba.blue = blue; //Defines blue intensity
    pixel.rgba.alpha = alpha; //Defines transparency intensity

    return pixel;
}
void PutPixel(pixel_t pixel){

    fb_ptr[4*pixel.coord.x + 4*pixel.coord.y*IMAGE_WIDTH + 0] = pixel.rgba.red; //Sets red intensity in the memory
    fb_ptr[4*pixel.coord.x + 4*pixel.coord.y*IMAGE_WIDTH + 1] = pixel.rgba.green; //Sets green intensity in the memory
    fb_ptr[4*pixel.coord.x + 4*pixel.coord.y*IMAGE_WIDTH + 2] = pixel.rgba.blue; //Sets blue intensity in the memory
    fb_ptr[4*pixel.coord.x + 4*pixel.coord.y*IMAGE_WIDTH + 3] = pixel.rgba.alpha; //Sets transparency intensity in the memory
}

void LinearColorInterpolation(pixel_t pi, pixel_t * p_aux, pixel_t pf){
    int delta_x = pf.coord.x - pi.coord.x;
    int delta_y = pf.coord.y - pi.coord.y;

    int deltaX_aux = pf.coord.x - p_aux->coord.x;
    int deltaY_aux = pf.coord.y - p_aux->coord.y;

    double interpol = sqrt(pow(deltaX_aux, 2) + pow(deltaY_aux, 2)) / sqrt(pow(delta_x, 2) + pow(delta_y, 2));

    p_aux->rgba.red = pf.rgba.red + (pi.rgba.red - pf.rgba.red) * interpol;
    p_aux->rgba.green = pf.rgba.green + (pi.rgba.green - pf.rgba.green) * interpol;
    p_aux->rgba.blue = pf.rgba.blue + (pi.rgba.blue - pf.rgba.blue) * interpol;
    p_aux->rgba.alpha = pf.rgba.alpha + (pi.rgba.alpha - pf.rgba.alpha) * interpol;
}

void MyGlDraw(void) {
 
 //printf("Image Width = %d\nImage Height = %d\n", IMAGE_WIDTH, IMAGE_HEIGHT);
 int x,y;
 printf("Insert coordinates:");
 scanf("%d %d", &x, &y);
 pixel_t pixel = SetPixel(x, y, 255, 0, 255, 255);
 
 PutPixel(pixel);

}
