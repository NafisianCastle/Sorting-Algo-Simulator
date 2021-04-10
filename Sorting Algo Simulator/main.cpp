#include "GL/freeglut.h"
#include "GL/gl.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <iostream>
#include "ArrayHelper.cpp"
#include <unistd.h>

// I know this is bad, but oh well :/ Not going for best design, just
// trying to learn
int length;
int delay;
int* arr;
void (*sort)(int*, int);

// used https://www.codeproject.com/Articles/182109/Setting-up-an-OpenGL-development-environment-in-Ub
// as starting place
void renderFunction()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    float l = (float) length;
    float widthAdder = 1/l;

    for(int i = 0; i < length; ++i)
    {
        glBegin(GL_POLYGON);

        // + 1 so value of 0 has height of 1
        float arrayIndexHeightRatio = 2*(arr[i] + 1)/l;
        float widthIndexAdder = 2*i/l;

        float leftX   = -1 + widthIndexAdder;
        float rightX  = leftX + widthAdder;
        float bottomY = -1;
        float topY    = bottomY + arrayIndexHeightRatio;

        // bottom left
        glColor4f(1,0,0,0);
        glVertex2f(leftX, bottomY);

        // bottom right
        glColor4f(0,1,0,0);
        glVertex2f(rightX, bottomY);

        // top right
        glColor4f(0,0,1,0);
        glVertex2f(rightX, topY);

        // top left
        glColor4f(0,0,0,1);
        glVertex2f(leftX, topY);

        glEnd();
    }

    glFlush();
}

void swap(int index1, int index2)
{
    std::swap(arr[index1], arr[index2]);
    renderFunction();
    usleep(delay);
}

void keyboardEvent(unsigned char c, int x, int y)
{
	if(c == 27)
	{
		// exit on escape key pressed
		exit(0);
		free(arr);
	}
	else if(c == 115)
	{
		// start on `s` key pressed
		sort(arr, length);
	}
}

int setUpGlutAndArray(int argc, char** argv, void (*sortingAlgorithm)(int*, int))
{
    sort = sortingAlgorithm;
    arr = (int*) malloc(sizeof(int) * length);
    for(int i = 0; i < length; ++i)
    {
        arr[i] = i;
    }
    randomizeArray(arr, length);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(length,length);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Sort Visualization");

    glutDisplayFunc(renderFunction);
    glutKeyboardFunc(keyboardEvent);

    glutMainLoop();
}


int main(int argc,char* argv[])
{
	 srand(time(NULL));
    delay  = 1500;
    length = 500;
    setUpGlutAndArray(argc, argv, quicksort);
    free(arr);

    return 0;
}
