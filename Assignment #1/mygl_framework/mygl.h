#ifndef MYGL_H
#define MYGL_H

#include "core.h"
#include "frame_buffer.h"

// Structs implementadas
typedef struct Tuple{
    int x;
    int y;
}tuple_t;

typedef struct RGBA_Colors{
    int red;
    int green;
    int blue;
    int alpha;
}colors_t;

// Declaração da função que chamará as funções implementadas pelo aluno
void MyGlDraw(void);

//
// >>> Declare aqui as funções que você implementar <<<
void PutPixel(tuple_t coord, colors_t rgba);
//

#endif  // MYGL_H
