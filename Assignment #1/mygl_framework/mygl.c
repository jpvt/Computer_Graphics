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

pixel_t DrawPixelLineX(pixel_t pi, pixel_t pf){
    pixel_t pixel_atual = pi;

    int delta_x = pf.coord.x - pi.coord.x;
    int delta_y = pf.coord.y - pi.coord.y;

    if(delta_y < 0){
        delta_y = -delta_y;
    }

    int decision = 2 * delta_y - delta_x;
    int incr_e = 2 * delta_y;
    int incr_ne = 2 * (delta_y - delta_x);

    if (p.coord.x < pf.coord.x){
        PutPixel(p);
        if(d<=0){
            d +=incr_e;
            p.coord.x++;
        }else{
            d += incr_ne;
            p.coord.x++;
            p.coord.y++;
        }
        LinearColorInterpolation(pi, &p, pf);

    }
}

pixel_t DrawPixelLineY(pixel_t pi, pixel_t pf){
    pixel_t pixel_atual = pi;

    int delta_x = pf.coord.x - pi.coord.x;
    int delta_y = pf.coord.y - pi.coord.y;

    if(delta_x < 0){
        delta_x = -delta_x;
    }

    int decision = 2 * delta_y - delta_x;
    int incr_e = 2 * delta_y;
    int incr_ne = 2 * (delta_y - delta_x);


    if (p.coord.y < pf.coord.y){
        PutPixel(p);
        if(d<=0){
            d +=incr_e;
            p.coord.y++;
        }else{
            d += incr_ne;
            p.coord.x++;
            p.coord.y++;
        }
        LinearColorInterpolation(pi, &p, pf);

    }
}

void DrawLine(pixel_t pi, pixel_t pf){
    int abs_deltaX = abs(pf.coord.x - pi.coord.x);
    int abs_deltaY = abs(pf.coord.y - pi.coord.y);
    
    if(abs_deltaX > abs_deltaY){
        if(pf.coord.x > pi.coord.x){
            DrawPixelLineX(pi, pf);
        }else{
            DrawPixelLineX(pf, pi);
        }
    }else{
        if(pf.coord.y > pi.coord.y){
            DrawPixelLineY(pi, pf);
        }else{
            DrawPixelLineY(pf, pi);
        }
    }
}

void DrawTriangle(pixel_t v1, pixel_t v2, pixel_t v3){
    DrawLine(v1,v2);
    DrawLine(v2,v3);
    DrawLine(v3,v1);
}
void MyGlDraw(void) {
 
 //printf("Image Width = %d\nImage Height = %d\n", IMAGE_WIDTH, IMAGE_HEIGHT);
 int x,y;
 printf("Insert coordinates:");
 scanf("%d %d", &x, &y);
 pixel_t pixel = SetPixel(x, y, 255, 0, 255, 255);
 
 PutPixel(pixel);

}
