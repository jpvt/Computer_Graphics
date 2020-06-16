#include "mygl.h"
#include <stdio.h>

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

    fb_ptr[4*pixel.coord.x + 4*pixel.coord.y*IMAGE_WIDTH + 0] = pixel.rgba.red;
    fb_ptr[4*pixel.coord.x + 4*pixel.coord.y*IMAGE_WIDTH + 1] = pixel.rgba.green;
    fb_ptr[4*pixel.coord.x + 4*pixel.coord.y*IMAGE_WIDTH + 2] = pixel.rgba.blue;
    fb_ptr[4*pixel.coord.x + 4*pixel.coord.y*IMAGE_WIDTH + 3] = pixel.rgba.alpha;
}

// Definição da função que chamará as funções implementadas pelo aluno
void MyGlDraw(void) {
 
 //printf("Image Width = %d\nImage Height = %d\n", IMAGE_WIDTH, IMAGE_HEIGHT);
 int x,y;
 printf("Insert coordinates:");
 scanf("%d %d", &x, &y);
 pixel_t pixel = SetPixel(x, y, 255, 0, 255, 255);
 
 PutPixel(pixel);

}
