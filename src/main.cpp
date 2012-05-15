/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  This is a temporary GUI test framework in OpenGL.
 *
 *        Version:  1.0
 *        Created:  05/15/2012 10:05:36 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "const.h"

void SetupRC() {
    
    glClearColor(0, 0, 0, 0);
    glEnable(GL_POINT_SMOOTH);

}

void ChangeSize(GLsizei w, GLsizei h) {

    if (h == 0)
        h = 1;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (w <= h)
        glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -100, 100);
    else
        glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -100, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

void RenderScene() {

    glClear(GL_COLOR_BUFFER_BIT);

    glColor3ub(255, 255, 255);
    glBegin(GL_QUADS);
        glVertex2i(0, 0);
        glVertex2i(WINDOW_WIDTH, 0);
        glVertex2i(WINDOW_WIDTH, WINDOW_HEIGHT);
        glVertex2i(0, WINDOW_HEIGHT);
    glEnd();

    glutSwapBuffers();

}

void OnMouseDrag(int x, int y) {

    glColor3ub(0, 0, 0);

    glPointSize(5);
    glBegin(GL_POINTS);
        glVertex2i(x, WINDOW_HEIGHT - y);
    glEnd();

    glutSwapBuffers();

}

int main(int argc, char **argv) {
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Graphite Pencil");

    SetupRC();
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    glutMotionFunc(OnMouseDrag);

    glutMainLoop();
    return 0;

}
