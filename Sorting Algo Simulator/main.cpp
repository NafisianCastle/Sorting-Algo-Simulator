#include <bits/stdc++.h>
#include<GL/gl.h>
#include <GL/glut.h>
#include <windows.h>
using namespace std;

///QUICK SORT


void swap(int index1, int index2) {
    swap(arr[index1], arr[index2]);
    drawScene();
    usleep(delay);
}

int partition(int* a, int low, int high) {
    int lowIndex = low - 1;
    int pivot    = a[high];
    for(int i = low; i < high; ++i) {
        if(a[i] <= pivot) {
            ++lowIndex;
            swap(a[lowIndex], a[i]);
        }
    }
    ++lowIndex;
    swap(a[lowIndex], a[high]);
    return lowIndex;
}

void quickSortImplemented(int* a, int low, int high) {
    if(low < high) {
        int pi = partition(a, low, high);
        quickSort(a, low, pi - 1);
        quickSort(a, pi + 1, high);
    }
}

void quickSort(int* a, int length) {
    quickSortImplemented(a, 0, length - 1);
}

void visualize_array() {
}
void drawScene() {
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1.0, 1.0, 1.0);
        glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
        glFlush();
}

void randomizeArray(int* arr, int length) {
    for(int i = length - 1; i > 0; --i)
        swap(arr[i], arr[rand() % (i + 1)]);
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

int main(int argc, char** argv) {
    int sz;
    cout << "Enter the size of array::";
    cin >> sz;
    int randArray[sz];
    for(int i = 1; i <= sz; i++)
        randArray[i] = i; //assign number from 1 to size
    randomizeArray(randArray, length);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Sorting Allgo Simulator");
    glutDisplayFunc(drawScene);
    glutKeyboardFunc(keyboardEvent);
    glutMainLoop();
    return 0;
}
