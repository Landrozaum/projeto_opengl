// Computação Gráfica — Semana 2 — Bloco 3 (FreeGLUT)
// Compilar: g++ -std=c++17 primitivas.cpp -o primitivas.exe -lfreeglut -lopengl32 -lglu32

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

/* Quadro de referência do bloco 2.
 * Incluir uma primitiva nova aqui já a coloca na varredura. */
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

/* Vértices do hexágono dispostos no padrão do slide (3 colunas: 1-2 esq, 3-4 centro, 5-6 dir).
 * Mantém o hexágono simétrico e produz os padrões didáticos (ex: 3 linhas verticais em GL_LINES). */
constexpr std::array<std::array<float, 2>, N_VERTICES> vertices{{
    { -0.606f,  0.35f },   // 1: superior esquerdo
    { -0.606f, -0.35f },   // 2: inferior esquerdo
    {  0.000f,  0.70f },   // 3: ponta superior (eixo central)
    {  0.000f, -0.70f },   // 4: ponta inferior (eixo central)
    {  0.606f,  0.35f },   // 5: superior direito
    {  0.606f, -0.35f }    // 6: inferior direito
}};

static int  atual = 0;          // índice da primitiva corrente
static bool arame = false;      // exercício de sondagem (bloco 3.4)

static void atualizarTitulo()
{
    char titulo[128];
    std::snprintf(titulo, sizeof(titulo), "Bloco 3 - %s%s",
                  catalogo[atual].nome, arame ? "   [arame]" : "");
    glutSetWindowTitle(titulo);
}

/* teclas comuns: 1..0, W, ESC */
static void aoTeclar(unsigned char tecla, int /*x*/, int /*y*/)
{
    if (tecla >= '1' && tecla <= '9') {
        atual = tecla - '1';                        // 1..9 -> índices 0..8
    } else if (tecla == '0') {
        atual = 9;                                  // 0    -> GL_POLYGON
    } else if (tecla == 'w' || tecla == 'W') {
        arame = !arame;
    } else if (tecla == 27) {                       // ESC
        glutLeaveMainLoop();
        return;
    } else {
        return;
    }
    atualizarTitulo();
    glutPostRedisplay();
}

/* teclas especiais: setas para avançar e voltar */
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

    glColor3f(1.0f, 1.0f, 1.0f);
    glPointSize(8.0f);
    glLineWidth(2.0f);
    glPolygonMode(GL_FRONT_AND_BACK, arame ? GL_LINE : GL_FILL);

    /* ÚNICO bloco de especificação de vértices, parametrizado
     * pela primitiva corrente. */
    glBegin(catalogo[atual].modo);
        for (const auto &v : vertices)
            glVertex2f(v[0], v[1]);
    glEnd();

    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bloco 3");

    glClearColor(0.10f, 0.12f, 0.16f, 1.0f);

    glutDisplayFunc(exibir);
    glutKeyboardFunc(aoTeclar);
    glutSpecialFunc(aoTeclarEspecial);

    atualizarTitulo();
    glutMainLoop();
    return 0;
}