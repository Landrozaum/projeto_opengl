// Computação Gráfica — Semana 2 — Bloco 5 (parte 2) (FreeGLUT)
// Compilar: g++ -std=c++17 cena.cpp -o cena.exe -lfreeglut -lopengl32 -lglu32

#include <GL/glut.h>       
#include <GL/freeglut.h>  
#include <array>
#include <cmath>

constexpr float PI        = 3.14159265f;
constexpr float Y_BASE    = -0.75f;
constexpr int   N_COLUNAS = 6;

static bool arame = false;   // recurso extra: ver a malha interna

/* -----------------------------------------------------------------
 * Base sob as colunas — GL_QUADS
 * ----------------------------------------------------------------- */
static void desenharBase()
{
    glColor3f(0.25f, 0.25f, 0.30f);
    glBegin(GL_QUADS);
        glVertex2f(-0.95f, -0.95f);
        glVertex2f( 0.95f, -0.95f);
        glVertex2f( 0.95f, Y_BASE);
        glVertex2f(-0.95f, Y_BASE);
    glEnd();
}

/* -----------------------------------------------------------------
 * Fileira de colunas — GL_QUAD_STRIP
 * Cada par (base, topo) acrescenta um quadrilátero à faixa.
 * ----------------------------------------------------------------- */
constexpr std::array<float, N_COLUNAS + 1> alturaColuna{
    -0.30f, -0.05f, -0.45f, 0.10f, -0.20f, 0.25f, -0.35f
};

static void desenharColunas()
{
    glColor3f(0.45f, 0.50f, 0.62f);
    glBegin(GL_QUAD_STRIP);
        for (int i = 0; i <= N_COLUNAS; ++i) {
            float x = -0.90f + (1.80f * static_cast<float>(i) / static_cast<float>(N_COLUNAS));
            glVertex2f(x, Y_BASE);              // lado de baixo
            glVertex2f(x, alturaColuna[i]);     // lado de cima
        }
    glEnd();
}

/* -----------------------------------------------------------------
 * Objeto retangular — GL_QUADS
 * ----------------------------------------------------------------- */
static void desenharObjetoRetangular()
{
    glColor3f(0.85f, 0.55f, 0.20f);
    glBegin(GL_QUADS);
        glVertex2f(-0.60f, -0.32f);
        glVertex2f(-0.30f, -0.32f);
        glVertex2f(-0.30f,  0.03f);
        glVertex2f(-0.60f,  0.03f);
    glEnd();
}

/* -----------------------------------------------------------------
 * Objeto triangular — GL_TRIANGLES
 * ----------------------------------------------------------------- */
static void desenharObjetoTriangular()
{
    glColor3f(0.20f, 0.65f, 0.45f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.05f, -0.35f);
        glVertex2f( 0.25f, -0.35f);
        glVertex2f( 0.10f,  0.05f);
    glEnd();
}

/* -----------------------------------------------------------------
 * Objeto circular — GL_TRIANGLE_FAN
 * O primeiro vértice (centro) é comum a todos os triângulos.
 * ----------------------------------------------------------------- */
static void desenharObjetoCircular()
{
    constexpr float cx = 0.55f, cy = 0.45f, raio = 0.20f;
    constexpr int   fatias = 32;

    glColor3f(0.95f, 0.80f, 0.25f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);                     // centro, comum a todos
        for (int i = 0; i <= fatias; ++i) {
            float ang = 2.0f * PI * static_cast<float>(i) / static_cast<float>(fatias);
            glVertex2f(cx + raio * std::cos(ang), cy + raio * std::sin(ang));
        }
    glEnd();
}

/* -----------------------------------------------------------------
 * Objeto alongado — GL_TRIANGLE_STRIP
 * ----------------------------------------------------------------- */
static void desenharObjetoAlongado()
{
    constexpr std::array<std::array<float, 2>, 10> faixa{{
        { -0.90f, -0.55f }, { -0.95f, -0.68f },
        { -0.45f, -0.28f }, { -0.52f, -0.45f },
        { -0.05f, -0.50f }, { -0.10f, -0.62f },
        {  0.35f, -0.20f }, {  0.28f, -0.38f },
        {  0.75f, -0.45f }, {  0.70f, -0.62f }
    }};

    glColor3f(0.70f, 0.30f, 0.55f);
    glBegin(GL_TRIANGLE_STRIP);
        for (const auto &v : faixa)
            glVertex2f(v[0], v[1]);
    glEnd();
}

/* -----------------------------------------------------------------
 * Contorno de um dos objetos — GL_LINE_LOOP
 * ----------------------------------------------------------------- */
static void desenharContorno()
{
    glColor3f(1.00f, 1.00f, 0.35f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.65f, -0.37f);
        glVertex2f(-0.25f, -0.37f);
        glVertex2f(-0.25f,  0.08f);
        glVertex2f(-0.65f,  0.08f);
    glEnd();
}

/* -----------------------------------------------------------------
 * Marcadores de posição — GL_POINTS
 * ----------------------------------------------------------------- */
static void desenharMarcadores()
{
    glColor3f(0.95f, 0.95f, 0.95f);
    glPointSize(8.0f);
    glBegin(GL_POINTS);
        glVertex2f(-0.90f, Y_BASE);
        glVertex2f( 0.00f, Y_BASE);
        glVertex2f( 0.90f, Y_BASE);
        glVertex2f(-0.45f, -0.15f);
        glVertex2f( 0.55f,  0.45f);
    glEnd();
}

/* -----------------------------------------------------------------
 * Cena — a ORDEM das chamadas é a ordem de sobreposição.
 * ----------------------------------------------------------------- */
static void exibir()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, arame ? GL_LINE : GL_FILL);

    desenharBase();               // 1º — fundo
    desenharColunas();            // 2º — fileira de colunas
    desenharObjetoRetangular();   // 3º
    desenharObjetoTriangular();   // 4º
    desenharObjetoCircular();     // 5º
    desenharObjetoAlongado();     // 6º
    desenharContorno();           // 7º — contorno por cima
    desenharMarcadores();         // 8º — por cima de tudo

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glutSwapBuffers();
}

static void aoTeclar(unsigned char tecla, int /*x*/, int /*y*/)
{
    if (tecla == 'w' || tecla == 'W') {
        arame = !arame;
        glutPostRedisplay();
    } else if (tecla == 27) {                       // ESC
        glutLeaveMainLoop();
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bloco 5 - cena");

    glClearColor(0.10f, 0.12f, 0.16f, 1.0f);

    glutDisplayFunc(exibir);
    glutKeyboardFunc(aoTeclar);

    glutMainLoop();
    return 0;
}