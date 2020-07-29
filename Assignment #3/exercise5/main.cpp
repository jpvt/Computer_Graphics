/*****************************************************************************
 * Este programa é baseado no exemplo "Hello-Triangle" disponível 
 * em 
 *     https://learnopengl.com/Getting-started/Hello-Triangle
 * 
 *     A principal diferença entre este programa e o exemplo acima é que neste
 * os vertex e fragment shaders são carregados a partir de arquivos externos, 
 * ao inves de estarem hard coded no código fonte. 
 *     Isso da mais flexibilidade para se fazerem experimentos com os shaders, 
 * pois nao e necessario se recompilar o programa a cada vez que os shaders forem
 * alterados.
 ****************************************************************************/
#include "main.h"

#define IMAGE_WIDTH 512 // Largura da janela OpenGL em pixels.
#define IMAGE_HEIGHT 512 // Altura da janela OpenGL em pixels.

float closer_red = 0.75, closer_green = 0.0, closer_blue = 0.0;
float farther_red = 0.0, farther_green = 0.0, farther_blue = 0.75;

// Array contendo as coordenadas X,Y e Z de tres vertices (um trianglulo).
float vertices[] = {-0.25f, -0.5f, -0.1f, closer_red, closer_green, closer_blue, // red triangle (closer)
                     0.25f,  0.5f, -0.1f, closer_red, closer_green, closer_blue,
                     0.75f, -0.5f, -0.1f, closer_red, closer_green, closer_blue,
                    -0.75f, -0.5f, -0.4f, farther_red, farther_green, farther_blue, // blue triangle (farther)
                    -0.25f,  0.5f, -0.4f, farther_red, farther_green, farther_blue,
                     0.25f, -0.5f, -0.4f, farther_red, farther_green, farther_blue}; 

char* frag_shader_source = NULL;
char* vertex_shader_source = NULL;
unsigned int shader_program;
unsigned int vbo; // Vertex buffer object ID
unsigned int vao; // Vertex array object ID

float rotateY = 0.0;


// Função ChangeColors()*********************************************************************************************
void ChangeColors(){

    float factor = 0.005;
    int j = 6;
    //closer update colors
    if(closer_red >= 0.0 && closer_green == 0.0 && closer_blue == 0.0 && closer_red <= 1.0){
        closer_red += factor;
    }else if(closer_red >= 1.0){
        closer_green += factor;
        closer_red = 0.0;
    }

    if(closer_green >= 0.0 && closer_red == 0.0 && closer_blue == 0.0 && closer_green <= 1.0){
        closer_green += factor;
    }else if(closer_green >= 1.0){
        closer_blue += factor;
        closer_green = 0.0;
    }

    if(closer_blue >= 0.0 && closer_red == 0.0 && closer_green == 0.0 && closer_blue <= 1.0){
        closer_blue += factor;
    }else if(closer_blue >= 1.0){
        closer_red += factor;
        closer_blue = 0.0;
    }

    //farther update colors
    if(farther_red >= 0.0 && farther_green == 0.0 && farther_blue == 0.0 && farther_red <= 1.0){
        farther_red += factor;
    }else if(farther_red >= 1.0){
        farther_green += factor;
        farther_red = 0.0;
    }

    if(farther_green >= 0.0 && farther_red == 0.0 && farther_blue == 0.0 && farther_green <= 1.0){
        farther_green += factor;
    }else if(farther_green >= 1.0){
        farther_blue += factor;
        farther_green = 0.0;
    }

    if(farther_blue >= 0.0 && farther_red == 0.0 && farther_green == 0.0 && farther_blue <= 1.0){
        farther_blue += factor;
    }else if(farther_blue >= 1.0){
        farther_red += factor;
        farther_blue = 0.0;
    }

    
    for(int i = 0; i < 3; i++)
        vertices[3+j*i] = closer_red;

    for(int i = 0; i < 3; i++)
        vertices[4+j*i] = closer_green;

    for(int i = 0; i < 3; i++)
        vertices[5+j*i] = closer_blue;



    for(int i = 0; i < 3; i++)
        vertices[21+j*i] = farther_red;

    for(int i = 0; i < 3; i++)
        vertices[22+j*i] = farther_green;

    for(int i = 0; i < 3; i++)
        vertices[23+j*i] = farther_blue;


    // Carrega as propriedades (coordenadas + cores) dos vértices no VBO
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

    // Atributo 'posição' do vértice
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Atributo 'cor' do vértice
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Define a cor a ser utilizada para limpar o color buffer a cada novo frame
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);            

    // Habilita o teste de profundidade
    GL_CHECK(glEnable(GL_DEPTH_TEST));

}
//********************************************************************************************************************

//********************************************************************************************************************
// A função LoadShader() é baseada em https://stackoverflow.com/a/174552/6107321
void LoadShader(char* file_name, char** shader_source) {
    long length;
    FILE* f = fopen(file_name, "rb");

    if (f) {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);

        (*shader_source) = (char*)malloc(length + 1);
        if ((*shader_source)) {
            fread((*shader_source), 1, length, f);
            (*shader_source)[length] = '\0';
        }

        fclose(f);
    } else {
        printf("Could not load the shader file %s\nExiting...", file_name);
        exit(EXIT_FAILURE);
    }
}

//********************************************************************************************************************
void Display(void) {
    // Limpa a tela e o depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Define a posição da Viewport dentro da janela OpenGL
    glViewport(0, 0, IMAGE_WIDTH, IMAGE_HEIGHT);

    // Seleciona o Shader Program a ser utilizado.
    glUseProgram(shader_program);

    // Matriz Model ///////////////////////////////////////////////////////////
    // You will have to change the contents of this matrix for the exercises
    float model_array[16] = {1.0f, 0.0f, 0.0f, 0.0f, 
                             0.0f, 1.0f, 0.0f, 0.0f, 
                             0.0f, 0.0f, 1.0f, 0.0f, 
                             0.0f, 0.0f, 0.0f, 1.0f};
    glm::mat4 model_free_mat = glm::make_mat4(model_array);

    // Rotate Matrix
    glm::mat4 rotate_matrix = glm::mat4(glm::vec4(glm::cos(rotateY), 0, -glm::sin(rotateY), 0),
                                glm::vec4(0, 1, 0, 0),
                                glm::vec4(glm::sin(rotateY), 0, glm::cos(rotateY), 0),
                                glm::vec4(0, 0, 0, 1));

    rotateY += 0.01;

    ChangeColors(); 

    glm::mat4 model_mat = model_free_mat * rotate_matrix;

    // Matriz View ////////////////////////////////////////////////////////////
    // You will have to change the contents of this matrix for the exercises

    // Parameters:
    glm::vec3 camera_target = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 camera_pos    = glm::vec3(3.0f, 1.0f, 1.0f);
    glm::vec3 camera_up     =  glm::vec3(0.0f, 1.0f, 0.0f);

    glm::vec3 camera_z = -glm::normalize(camera_target - camera_pos);
    glm::vec3 camera_x = glm::normalize(glm::cross(camera_up, camera_z));
    glm::vec3 camera_y = glm::normalize(glm::cross(camera_z, camera_x));

    glm::mat4 B = glm::mat4(glm::vec4(camera_x.x, camera_y.x, camera_z.x, 0),
                            glm::vec4(camera_x.y, camera_y.y, camera_z.y, 0),
                            glm::vec4(camera_x.z, camera_y.z, camera_z.z, 0),
                            glm::vec4(0, 0, 0, 1)
    );

    glm::mat4 T = glm::mat4(glm::vec4(1, 0, 0, 0),
                            glm::vec4(0, 1, 0, 0),
                            glm::vec4(0, 0, 1, 0),
                            glm::vec4(-camera_pos.x, -camera_pos.y, -camera_pos.z, 1)
    );

    glm::mat4 view_mat = B * T;
/*
    float view_array[16] = {1.0f, 0.0f, 0.0f, 0.0f, 
                            0.0f, 1.0f, 0.0f, 0.0f, 
                            0.0f, 0.0f, 1.0f, 0.0f, 
                            0.0f, 0.0f, 0.0f, 1.0f};

    glm::mat4 view_mat = glm::make_mat4(view_array);*/

    // Matriz Projection //////////////////////////////////////////////////////
    // You will have to change the contents of this matrix for the exercises

    float d = 4.0f;

    float proj_array[16] = {1.0f, 0.0f, 0.0f, 0.0f, 
                            0.0f, 1.0f, 0.0f, 0.0f, 
                            0.0f, 0.0f, 1.0f, -1/d, 
                            0.0f, 0.0f, d, 1.0f};

    glm::mat4 proj_mat = glm::make_mat4(proj_array);

    // Thr NDC is a left handed system, so we flip along the Z axis.
    // IMPORTANT: Do not change the contents of this matrix!!!!!!
    float flip_z_array[16] = {1.0f, 0.0f,  0.0f, 0.0f, 
                              0.0f, 1.0f,  0.0f, 0.0f, 
                              0.0f, 0.0f, -1.0f, 0.0f, 
                              0.0f, 0.0f,  0.0f, 1.0f};
    glm::mat4 flip_z_mat = glm::make_mat4(flip_z_array);

    // Matriz ModelViewProjection /////////////////////////////////////////////
    glm::mat4 model_view_proj_mat = flip_z_mat * proj_mat * view_mat * model_mat;

    unsigned int transformLoc;
    GL_CHECK(transformLoc = glGetUniformLocation(shader_program, "transform"));
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model_view_proj_mat));

    // Ativa o Vertex Array Object selecionado.
    glBindVertexArray(vao);

    // Desenha as tres primeiras primitivias, comecando pela de indice 0.
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glFlush();            //
    glutSwapBuffers();    //
    glutPostRedisplay();  //
}

//********************************************************************************************************************
void ExitProg(void) {
    if (vertex_shader_source) {
        free(vertex_shader_source);
        vertex_shader_source = NULL;
    }

    if (frag_shader_source) {
        free(frag_shader_source);
        frag_shader_source = NULL;
    }

    printf("Exiting...\n");
}

//********************************************************************************************************************
int main(int argc, char** argv) {
    // Inicializa a GLUT
    glutInit(&argc, argv);

    // Cria um color buffer onde cada pixel é representado por 4 bytes (RGBA)
    // Cria um depth buffer (para resolver a oclusão)
    // Cria dois color buffers para reduzir o flickering
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);

    // Define as dimensões do color buffer (ou a área útil do OpenGL na janela)
    glutInitWindowSize(IMAGE_WIDTH, IMAGE_HEIGHT);

    // Posição do canto superior esquerdo da janela OpenGL em relação a tela do computador.
    glutInitWindowPosition(100, 100);

    // Título da janela
    glutCreateWindow("Modern OpenGL: Assignment 3");

    // Load the OpenGL extensions
    GLenum err = glewInit();
    if (GLEW_OK != err) {
      /* Problem: glewInit failed, something is seriously wrong. */
      fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
      return EXIT_FAILURE; 
    }

    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

    // Carrega o codigo fonte do Vertex shader
    LoadShader("vertex_shader.glsl", &vertex_shader_source);

    printf("%s\n", vertex_shader_source);

    unsigned int vertex_shader;

    // Cria um identificador para o Vertex Shader
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);

    // Vincula o código fonte do Vertex Shader ao seu identificador
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);

    // Compila dinamicamente (em tempo de execucao) o Vertex Shader
    glCompileShader(vertex_shader);

    // Imprime eventuais mensagens de erro de compilacao do Vertex Shader
    int success;
    char info_log[512];
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", info_log);
    }

    // Carrega o codigo fonte do Fragment shader
    LoadShader("fragment_shader.glsl", &frag_shader_source);

    printf("%s\n", frag_shader_source);

    unsigned int fragment_shader;

    // Cria um identificador para o Fragment Shader
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    // Vincula o código fonte do Fragment Shader ao seu identificador
    glShaderSource(fragment_shader, 1, &frag_shader_source, NULL);

    // Compila dinamicamente (em tempo de execucao) o Fragment Shader
    glCompileShader(fragment_shader);

    // Imprime eventuais mensagens de erro de compilacao do Fragment Shader
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", info_log);
    }

    // Cria um identificador para um Shader program (vertex + fragment shader)
    shader_program = glCreateProgram();

    // Vincula os Fragment e Vertex Shaders ao Program Shader
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);

    // Linka o Fragment e Vertex Shader para formarem o Program Shader 
    glLinkProgram(shader_program);

    // Imprime eventuais mensagens de erro de linkagem do Program Shader
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader_program, 512, NULL, info_log);
        printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", info_log);
    }

    // Deleta os Fragment e Vertex Shaders, já que eles já foram incorporados 
    // ao Program Shader e não são mais necessários.
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    // Ativa o Vertex Array Object (VAO)
    glBindVertexArray(vao);

    // Cria um novo identificador de buffer 
    glGenBuffers(1, &vbo);

    // Vincula o buffer criado a um Vertex Buffer Object (VBO)
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Carrega as propriedades (coordenadas + cores) dos vértices no VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Atributo 'posição' do vértice
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Atributo 'cor' do vértice
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Define a cor a ser utilizada para limpar o color buffer a cada novo frame
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);            

    // Habilita o teste de profundidade (oclusão).
    GL_CHECK(glEnable(GL_DEPTH_TEST));

    atexit(ExitProg);          // deifne o callback de saída do programa
    glutDisplayFunc(Display);  // define o callback que renderizará cada frame

    // Framebuffer scan loop.
    glutMainLoop();

    return EXIT_SUCCESS;
}
