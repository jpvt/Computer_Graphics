#include "main.h"

#define IMAGE_WIDTH 512
#define IMAGE_HEIGHT 512

//********************************************************************************************************************
void Display(void) {
    // Limpa a tela e o depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Define a posição da Viewport dentro da janela OpenGL
    glViewport(0, 0, IMAGE_WIDTH, IMAGE_HEIGHT);

    // Desenha um triângulo
    glBegin(GL_TRIANGLES);          // Inicio do desenho do triângulo
    glColor3f(1.0f, 0.0f, 0.0f);    // cor do vértice 0
    glVertex3f(-0.5f, -0.5f, 0.0f); // posição do vértice 0
    glColor3f(0.0f, 1.0f, 0.0f);    // cor do vértice 1
    glVertex3f(0.0f, 0.5f, 0.0f);   // posição do vértice 1
    glColor3f(0.0f, 0.0f, 1.0f);    // cor do vértice 2
    glVertex3f(0.5f, -0.5f, 0.0f);  // posição do vértice 2
    glEnd();                        // Fim do desenho do triângulo

    glFlush();              //
    glutSwapBuffers();      //
    glutPostRedisplay();    //
}

//********************************************************************************************************************
void ExitProg(void) {
    printf("Exiting...\n");
}

//********************************************************************************************************************
int main(int argc, char **argv) {
    // 
    glutInit(&argc, argv);
    // Cria um color buffer onde cada pixel é representado por 4 bytes (RGBA)
    // Cria um depth buffer (para rsoslver oclusão)
    // Cria dois color buffers, para reduzir o flickering
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    // Define as dimensões do color buffer (ou a área útil do OpenGL na janela)
    glutInitWindowSize(IMAGE_WIDTH, IMAGE_HEIGHT);
    // POsição do canto superior esquerdo da janela OpenGL
    glutInitWindowPosition(100, 100);
    // Título da janela
    glutCreateWindow("Simple OpenGL");

    // Ajusta a projeção ortográfica.
    glMatrixMode(GL_PROJECTION);    // ativa a matriz de projeção
    glLoadIdentity();               // carrega a identidade
    glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f); // Define a matriz de projeção
    glMatrixMode(GL_MODELVIEW);     // troca a matriz ativa para a ModelView
    glLoadIdentity();               // carrega a identidade
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // define a cor para limpar o color buffer

    atexit(ExitProg);   // deifne o callback de saída do programa
    glutDisplayFunc(Display);   // define o callback que renderizará cada frame

    // Framebuffer scan loop.
    glutMainLoop();

    return 0;
}
