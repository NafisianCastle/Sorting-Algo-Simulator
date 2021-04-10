#include "GL/gl.h"
#include <GL/glut.h>
#include <unistd.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <iostream>
//using namespace std;
int length;
int delay;
int* arr;
void (*sort)(int*, int);
void quickSort(int*, int len);

void renderFunction() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    float l = (float) length;
    float widthAdder = 1 / l;
    for(int i = 0; i < length; ++i) {
        glBegin(GL_POLYGON);
        float arrayIndexHeightRatio = 2 * (arr[i] + 1) / l;
        float widthIndexAdder = 3 * i / l;
        float leftX   = -1 + widthIndexAdder;
        float rightX  = leftX + widthAdder;
        float bottomY = -1;
        float topY    = bottomY + arrayIndexHeightRatio;
        glColor4f(0, 0.5, 0, 0);
        glVertex2f(leftX, bottomY);
        glVertex2f(rightX, bottomY);
        glVertex2f(rightX, topY);
        glVertex2f(leftX, topY);
        glEnd();
    }
    glFlush();
}

void swap(int index1, int index2) {
    std::swap(arr[index1], arr[index2]);
    renderFunction();
    usleep(delay);
}
int partition(int* a, int low, int high)
{
    int lowIndex = low - 1;
    int pivot    = a[high];

    for(int i = low; i < high; ++i)
    {
        if(a[i] <= pivot)
        {
            ++lowIndex;
            std::swap(a[lowIndex], a[i]);
        }
    }

    ++lowIndex;
    std::swap(a[lowIndex], a[high]);

    return lowIndex;
}

void quickSortImplemented(int* a, int low, int high)
{
    if(low < high)
    {
        int pi = partition(a, low, high);

        quickSortImplemented(a, low, pi - 1);
        quickSortImplemented(a, pi + 1, high);
    }
}

void quickSort(int* a, int length)
{
    quickSortImplemented(a, 0, length - 1);
}
void keyboardEvent(unsigned char c, int x, int y) {
    if(c == 27) {
        // exit on escape key pressed
        exit(0);
        free(arr);
    } else if(c == 115) {
        // start on `s` key pressed
        sort(arr, length);
    }
}
void randomizeArray(int* arr, int length)
{
	for(int i = length - 1; i > 0; --i)
	{
		std::swap(arr[i], arr[rand() % (i+1)]);
	}
}
int setUpGlutAndArray(int argc, char** argv, void (*sortingAlgorithm)(int*, int)) {
    sort = sortingAlgorithm;
    arr = (int*) malloc(sizeof(int) * length);
    for(int i = 0; i < length; ++i)
        arr[i] = i;
    randomizeArray(arr, length);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(length, length-(length*20/100));
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Sort Algo Simulator");
    glutDisplayFunc(renderFunction);
    glutKeyboardFunc(keyboardEvent);
    glutMainLoop();
}


int main(int argc, char* argv[]) {
    srand(time(NULL));
    delay  = 3500;
    length = 600;
    setUpGlutAndArray(argc, argv, quickSort);
    free(arr);
    return 0;
}
