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
void MyGlDraw(void) {

    //colors_t red = {.red = 255, .green= 0, .blue = 0, .alpha = 255};
    //colors_t blue = {.red = 0, .green= 0, .blue = 255, .alpha = 255};
    //colors_t green = {.red = 0, .green= 255, .blue = 0, .alpha = 255};

    //pixel_t v1 = SetPixel(250, 50, 255, 0, 0, 255); // red
    //pixel_t v2 = SetPixel(500, 500, 0, 255, 0, 255); // green
    //pixel_t v3 = SetPixel(50, 500, 0, 0, 255, 255); // blue
    //DrawLine(v1,v2);

    pixel_t pi = SetPixel(12, 500, 255, 0, 0, 255);
    pixel_t pf = SetPixel(500, 12, 0, 0, 255, 255);
    DrawLine(pi,pf);
    //DrawTriangle(v1, v2, v3);


}
