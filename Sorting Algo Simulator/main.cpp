#include<windows.h>
#include<GL/glut.h>
#include<bits/stdc++.h>
#include<unistd.h>
#include<GL/gl.h>
const int N = 25;
int vec[N], compares = 0, exchanges = 0;
std::string sortName = "Bubble Sort";
int first = -1, second = -1, day = 1;

void initGL();
void display();
void visualization(int* arr);
void drawBitmapString(float x, float y, std::string s);

void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
void bubbleSort() {
    for(first = 0; first < N - 1; ++first)
        for(second = 0; second < N - first - 1; ++second) {
            compares++;
            usleep(1500);
            if(vec[second] > vec[second + 1]) {
                exchanges++;
                swap(&vec[second], &vec[second + 1]);
                glutPostRedisplay();
                usleep(1500);
            }
        }
}

void initGL() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void display() {
    visualization(vec);
}

void visualization(int* arr) {
    glClear(GL_COLOR_BUFFER_BIT); // sets the previous background with the current background
    drawBitmapString(600, 770, sortName);
    drawBitmapString(600, 750, "Number of Compares:" + std::to_string(compares));
    drawBitmapString(600, 730, "Number of Exchanges:" + std::to_string(exchanges));
    int x = 100;
    for(int i = 0; i < N; i++) {
        glBegin(GL_POLYGON);
        if(i == first)
            glColor3f(0.0f, 0.0f, 1.0f); //red
        else if(i == second)
            glColor3f(0.0f, 1.0f, 0.0f); //green
        else
            glColor3f(1.0f, 0.0f, 0.0f); //blue
        glVertex2f(x + 50, 450);
        glVertex2f(x, 450);
        glVertex2f(x, 500);
        glVertex2f(x + 50, 500);
        glVertex2f(x + 50, 450);
        glVertex2f(x + 50, 500);
        glVertex2f(x, 450);
        glVertex2f(x, 500);
        glEnd();
        drawBitmapString(x + 18, 470, std::to_string(vec[i]));
        x += 50;
    }
    glFlush();
    glutPostRedisplay();
    usleep(1500);
}

void drawBitmapString(float x, float y, std::string s) {
    //glColor3f(1.0f, 0.0f, 1.0f); // sets color of the text
    if(!day)
        glColor3f(1.0f, 1.0f, 1.0f); //green
    else
        glColor3f(0.0f, 0.0f, 0.0f); //blue
    glRasterPos2f(x, y);// screen coordinate at which text will appear
    int length = s.size();
    // writing charater by charater on the screen
    for(int i = 0; i < length; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
}

void randomizeArray(int* arr, int length) {
    for(int i = length - 1; i > 0; --i)
        std::swap(arr[i], arr[rand() % (i + 1)]);
}

void handleKeypress(unsigned char key, int x, int y) {
    switch(key) {
    case 'd':
        day = 1;
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glutPostRedisplay();
        break;
    case 'n':
        day = 0;
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glutPostRedisplay();
        break;
    case 'r':
        exchanges = 0, compares = 0, first = -1, second = -1;
        randomizeArray(vec, N);
        glutPostRedisplay();
        break;
    case 's':
        exchanges = 0, compares = 0, first = -1, second = -1;
        bubbleSort();
        Sleep(1);
        break;
    }
}

int main(int argc, char** argv) {
    // Generating random array within the range of N
    srand((unsigned)time(0));
    for(int i = 0; i < N; i++)
        vec[i] = (rand() % 100);
    glutInit(&argc, argv); // initializing glut
    glutInitWindowSize(1368, 760); // size of the window
    glutCreateWindow("Sorting Simulator");// name of window
    glutDisplayFunc(display); // call back function
    initGL(); // initializing GL
    glViewport(0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 1500, 0, 1000);
    glMatrixMode(GL_MODELVIEW);
    glutKeyboardFunc(handleKeypress);
    glutMainLoop(); // infinite processing loop
    return 0;
}
