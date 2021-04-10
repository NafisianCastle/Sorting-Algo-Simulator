#include "GL/gl.h"
#include <GL/glut.h>
#include <unistd.h>
#include <windows.h>
#include <bits/stdc++.h>

int length;
int delay;
int* arr;
void (*Sort)(int*, int, int);

void renderFunction() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glLoadIdentity(); //Reset the drawing perspective
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    float len = (float) length;
    float widthAdder = 1.7 / len;
    for(int i = 0; i < length; ++i) {
        glPushMatrix();
        glBegin(GL_POLYGON);
        float heightRatio = 1.5 * arr[i] / len;
        float positionAdder = 3 * i / len;
        float leftX   = -1 + positionAdder;
        float rightX  = leftX + widthAdder;
        float bottomY = -1;
        float topY    = bottomY + heightRatio;
        glColor3f(0, 0.5, 0);
        glVertex2f(leftX, bottomY);
        glVertex2f(rightX, bottomY);
        glVertex2f(rightX, topY);
        glVertex2f(leftX, topY);
        glEnd();
        glPopMatrix();
        glutSwapBuffers();
    }
    glFlush();
}

void swap(int index1, int index2) {
    glColor3f(1, 0, 0);
    std::swap(arr[index1], arr[index2]);
    renderFunction();
    usleep(delay);
}
int partition(int* a, int low, int high) {
    int lowIndex = low - 1, pivot    = a[high];
    for(int i = low; i < high; ++i) {
        if(a[i] <= pivot) {
            ++lowIndex;
            std::swap(a[lowIndex], a[i]);
        }
    }
    ++lowIndex;
    std::swap(a[lowIndex], a[high]);
    return lowIndex;
}

void quickSort(int* a, int low, int high) {
    if(low < high) {
        int pi = partition(a, low, high);
        quickSort(a, low, pi - 1);
        quickSort(a, pi + 1, high);
    }
}

void randomizeArray(int* arr, int length) {
    for(int i = length - 1; i > 0; --i)
        std::swap(arr[i], arr[rand() % (i + 1)]);
}
void keyboardEvent(unsigned char c, int x, int y) {
    if(c == 27) {
        // exit on escape key pressed
        exit(0);
        free(arr);
    } else if(c == 's') {
        // start on `s` key pressed
        Sort(arr, 0, length - 1);
    } else if(c == 'r')
        //randomize on 'r' key pressed
        randomizeArray(arr, length);
}

int drawScene(int argc, char** argv, void (*SortingAlgorithm)(int*, int, int)) {
    Sort = SortingAlgorithm;
    arr = (int*) malloc(sizeof(int) * length);
    for(int i = 0; i < length; ++i)
        arr[i] = i + 1;
    randomizeArray(arr, length);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(3 * length, length - (length  / 100));
    glutInitWindowPosition(300, 200);
    glutCreateWindow("Sort Algo Simulator");
    glutDisplayFunc(renderFunction);
    glutKeyboardFunc(keyboardEvent);
    glutMainLoop();
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    delay  = 1500;
    length = 300;
    drawScene(argc, argv, quickSort);
    free(arr);
    return 0;
}
