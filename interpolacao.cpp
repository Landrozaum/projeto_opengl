// Computação Gráfica — Semana 2 — Bloco 4 (FreeGLUT)
// Compilar: g++ -std=c++17 interpolacao.cpp -o interpolacao.exe -lfreeglut -lopengl32 -lglu32

#include <GL/glut.h>       
#include <GL/freeglut.h>  
#include <cstdio>
#include <array>

constexpr int N_VERTICES   = 6;
constexpr int N_PRIMITIVAS = 10;

struct Primitiva {
    const char *nome;
    GLenum      modo;
};

constexpr std::array<Primitiva, N_PRIMITIVAS> catalogo{{
    { "GL_POINTS",         GL_POINTS         },
    { "GL_LINES",          GL_LINES          },
    { "GL_LINE_STRIP",     GL_LINE_STRIP     },
    { "GL_LINE_LOOP",      GL_LINE_LOOP      },
    { "GL_TRIANGLES",      GL_TRIANGLES      },
    { "GL_TRIANGLE_STRIP", GL_TRIANGLE_STRIP },
    { "GL_TRIANGLE_FAN",   GL_TRIANGLE_FAN   },
    { "GL_QUADS",          GL_QUADS          },
    { "GL_QUAD_STRIP",     GL_QUAD_STRIP     },
    { "GL_POLYGON",        GL_POLYGON        }
}};

constexpr std::array<std::array<float, 2>, N_VERTICES> vertices{{
    { -0.80f, -0.30f },
    { -0.20f, -0.70f },
    {  0.60f, -0.50f },
    {  0.80f,  0.30f },
    {  0.10f,  0.80f },
    { -0.60f,  0.50f }
}};

/* Uma cor distinta por vértice. Nenhuma cor intermediária foi
 * declarada — as transições aparecem na rasterização. */
constexpr std::array<std::array<float, 3>, N_VERTICES> cores{{
    { 1.00f, 0.15f, 0.15f },   // vermelho
    { 1.00f, 0.90f, 0.15f },   // amarelo
    { 0.20f, 0.90f, 0.30f },   // verde
    { 0.20f, 0.85f, 0.95f },   // ciano
    { 0.30f, 0.40f, 1.00f },   // azul
    { 0.90f, 0.30f, 0.95f }    // magenta
}};

static int  atual           = 0;
static bool arame           = false;
static bool coresPorVertice = true;

static void atualizarTitulo()
{
    char titulo[128];
    std::snprintf(titulo, sizeof(titulo), "Bloco 4 - %s%s%s",
                  catalogo[atual].nome,
                  coresPorVertice ? "   [cor por vértice]" : "   [cor sólida]",
                  arame ? "   [arame]" : "");
    glutSetWindowTitle(titulo);
}

static void aoTeclar(unsigned char tecla, int /*x*/, int /*y*/)
{
    if (tecla >= '1' && tecla <= '9') {
        atual = tecla - '1';
    } else if (tecla == '0') {
        atual = 9;
    } else if (tecla == 'w' || tecla == 'W') {
        arame = !arame;
    } else if (tecla == 'c' || tecla == 'C') {
        coresPorVertice = !coresPorVertice;
    } else if (tecla == 27) {
        glutLeaveMainLoop();
        return;
    } else {
        return;
    }
    atualizarTitulo();
    glutPostRedisplay();
}

static void aoTeclarEspecial(int tecla, int /*x*/, int /*y*/)
{
    if (tecla == GLUT_KEY_RIGHT || tecla == GLUT_KEY_DOWN) {
        atual = (atual + 1) % N_PRIMITIVAS;
    } else if (tecla == GLUT_KEY_LEFT || tecla == GLUT_KEY_UP) {
        atual = (atual + N_PRIMITIVAS - 1) % N_PRIMITIVAS;
    } else {
        return;
    }
    atualizarTitulo();
    glutPostRedisplay();
}

static void exibir()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(10.0f);
    glLineWidth(3.0f);
    glPolygonMode(GL_FRONT_AND_BACK, arame ? GL_LINE : GL_FILL);

    glBegin(catalogo[atual].modo);
        for (std::size_t i = 0; i < vertices.size(); ++i) {
            /* A cor é ESTADO CORRENTE: vale para o próximo vértice
             * informado. Por isso ela vem imediatamente antes do glVertex2f. */
            if (coresPorVertice)
                glColor3f(cores[i][0], cores[i][1], cores[i][2]);
            else
                glColor3f(1.0f, 1.0f, 1.0f);

            glVertex2f(vertices[i][0], vertices[i][1]);
        }
    glEnd();

    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bloco 4");

    glClearColor(0.10f, 0.12f, 0.16f, 1.0f);

    /* padrão da biblioteca, mas declarado de propósito:
     * é o modo que interpola a cor entre os vértices. */
    glShadeModel(GL_SMOOTH);

    glutDisplayFunc(exibir);
    glutKeyboardFunc(aoTeclar);
    glutSpecialFunc(aoTeclarEspecial);

    atualizarTitulo();
    glutMainLoop();
    return 0;
}