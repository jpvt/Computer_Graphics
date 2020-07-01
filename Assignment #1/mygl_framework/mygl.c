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

    //double hypo = sqrt(pow(delta_x, 2) + pow(delta_y,2));
    int r_dist = -pf.rgba.red + pi.rgba.red;
    int g_dist = -pf.rgba.green + pi.rgba.green;
    int b_dist = -pf.rgba.blue + pi.rgba.blue;
    int a_dist = -pf.rgba.alpha + pi.rgba.alpha;

    double hypo = sqrt(pow(deltaX_aux, 2) + pow(deltaY_aux, 2)) / sqrt(pow(delta_x, 2) + pow(delta_y, 2));

    p_aux->rgba.red = pf.rgba.red + r_dist * hypo;
    p_aux->rgba.green = pf.rgba.green + g_dist * hypo;
    p_aux->rgba.blue = pf.rgba.blue + b_dist * hypo;
    p_aux->rgba.alpha = pf.rgba.alpha + a_dist * hypo;
}

void DrawPixelLineX(pixel_t pi, pixel_t pf){
    pixel_t p = pi;
	int incr_y = 1;
	int dx = pf.coord.x - pi.coord.x;
	int dy = pf.coord.y - pi.coord.y;
	int d = 2 * dy - dx;

	if(dy < 0){ // Mirror
		incr_y = -1;
		dy = -dy;
	}

	while(p.coord.x <= pf.coord.x){
		LinearColorInterpolation(pi, &p, pf);
        PutPixel(p);

		if(d > 0){ //NE
			d -= 2 * dx;
			p.coord.y += incr_y;
		}

		d += + 2 * dy; //E

		//LinearColorInterpolation(pi, &p, pf);

        p.coord.x++;
	}
}

void DrawPixelLineY(pixel_t pi, pixel_t pf){
    pixel_t p = pi;
	int incr_x = 1;
	int dx = pf.coord.x - pi.coord.x;
	int dy = pf.coord.y - pi.coord.y;
	int d = 2 * dx - dy;

	if(dx < 0){ // Mirror
		incr_x = -1;
		dx = -dx;
	}

	while(p.coord.y <= pf.coord.y){
		LinearColorInterpolation(pi, &p, pf);
        PutPixel(p);

		if(d > 0){ //NE
			d -= 2 * dy;
			p.coord.x +=incr_x;
		}

		d += 2 * dx; //E

		//LinearColorInterpolation(pi, &p, pf);

        p.coord.y++;
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

void DrawCustomTriangle(){
    pixel_t pxl1 = SetPixel(100, 300, 255, 0, 0, 0);
    pixel_t pxl2 = SetPixel(200, 150, 0, 0, 255, 0);

    pixel_t pxl3 = SetPixel(400, 300, 0, 255, 0, 0);
    pixel_t pxl4 = SetPixel(300, 150, 0, 0, 255, 0);

    pixel_t pxl5 = SetPixel(150, 450, 255, 0, 0, 0);
    pixel_t pxl6 = SetPixel(350, 450, 0, 255, 0, 0);

    pixel_t pxl7 = SetPixel(100, 400, 255, 0, 0, 0);
    pixel_t pxl8 = SetPixel(400, 400, 0, 255, 0, 0);
    pixel_t pxl9 = SetPixel(250, 150, 0, 0, 255, 0);

    DrawLine(pxl1,pxl2);
    DrawLine(pxl3,pxl4);
    DrawLine(pxl5,pxl6);

    DrawTriangle(pxl7, pxl8, pxl9);

}

void DrawColoredFrame(){
    pixel_t pxl1 = SetPixel(50, 50, 0, 0, 255, 0);//blue
    pixel_t pxl2 = SetPixel(462, 50, 255, 0, 0, 0);//red
    pixel_t pxl3 = SetPixel(462, 462, 0, 0, 255, 0);//blue
    pixel_t pxl4 = SetPixel(50, 462, 255, 0, 0, 0); //red

    DrawLine(pxl1,pxl2);
    DrawLine(pxl2,pxl3);
    DrawLine(pxl3,pxl4);
    DrawLine(pxl4,pxl1);


}


void MyGlDraw(void) {

    DrawColoredFrame();
    DrawCustomTriangle();



}
