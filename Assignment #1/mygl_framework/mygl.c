#include "mygl.h"

//
// >>> Defina aqui as funções que você implementar <<< 
void PutPixel(tuple_t coord, colors_t rgba){

    fb_ptr[4*coord.x + 4*coord.y + 0] = rgba.red;
    fb_ptr[4*coord.x + 4*coord.y + 1] = rgba.green;
    fb_ptr[4*coord.x + 4*coord.y + 2] = rgba.blue;
    fb_ptr[4*coord.x + 4*coord.y + 3] = rgba.alpha;
}
//

// Definição da função que chamará as funções implementadas pelo aluno
void MyGlDraw(void) {
 
 colors_t rgba;
 tuple_t coord;

 rgba.red = 255;
 rgba.green = 0;
 rgba.blue = 255;
 rgba.alpha = 255;

 coord.x = 800;
 coord.y = 2000;
 //
 // >>> Chame aqui as funções que você implementou <<<
 PutPixel(coord, rgba);
 //
 

}
