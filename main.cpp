#include <GL/glut.h>
#include <GL/glu.h>
#include <stdio.h>

float anguloCubo = 0.0;

void exibir() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glPushMatrix();
    glRotatef(anguloCubo, 1.0, 1.0, 0.0);
    glColor3f(1.0, 0.0, 0.0);
    glutSolidCube(1.0);
    glPopMatrix();

    glutSwapBuffers();
}

void atualizar(int valor) { 
    anguloCubo += 2.0;
    if (anguloCubo > 360) {
        anguloCubo -= 360;
    }

    glutPostRedisplay();
    glutTimerFunc(16, atualizar, 0);
}

void inicializar() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL com FreeGLUT");

    inicializar();

    glutDisplayFunc(exibir);
    glutTimerFunc(16, atualizar, 0);

    glutMainLoop();

    return 0;
} 
