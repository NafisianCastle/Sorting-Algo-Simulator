#include<windows.h>
#include<GL/glut.h>
#include<bits/stdc++.h>
#include<unistd.h>
#include<GL/gl.h>
const int N = 25;
int vec[N], compares = 0, exchanges = 0;
std::string sortName = "Bubble Sort";
int first = -1, second = -1, day = 1, a = -1, b = -1, sortingAlgo = 0, visArray = 1;
int _move = 1000;

void initGL();
void display();
void visualization(int* vec);
void drawBitmapString(float x, float y, std::string s);

void banner() {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(_move, 0, 0);
    drawBitmapString(600, 970, "WELCOME TO SORTING SIMULATOR !!!");
    glPopMatrix();
    glutSwapBuffers();
}

void update(int value) {
    _move -= 1;
    if(_move < -1200)
        _move = 1200;
    glutPostRedisplay(); //Notify GLUT that the display has changed
    glutTimerFunc(20, update, 0); //Notify GLUT to call update again in 25 milliseconds
}

void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
void bubbleSort() {
    for(first = 0; first < N - 1; ++first)
        for(second = 0; second < N - first - 1; ++second) {
            compares++;
            usleep(10);
            visualization(vec);
            a = -1, b = -1;
            if(vec[second] > vec[second + 1]) {
                exchanges++;
                a = second, b = second + 1;
                swap(&vec[second], &vec[second + 1]);
                usleep(100000);
                visualization(vec);
            }
        }
}

void insertionSort() {
    for(first = 1; first < N; first++) {
        for(second = first; second >= 1; second--) {
            compares++;
            usleep(100000);
            visualization(vec);
            a = -1, b = -1;
            if(vec[second] < vec[second - 1]) {
                exchanges++;
                swap(&vec[second], &vec[second - 1]);
                usleep(100000);
                visualization(vec);
            } else
                break;
        }
    }
}

void sort(int lo, int hi);
void sort_shuffle(int i, int j);
int part(int lo, int hi);
void exchange(int i, int j);

void quickSort() {
    int i = 0, j = N;
    sort_shuffle(i, j);
}

void sort_shuffle(int i, int j) {
    std::random_shuffle(vec, vec + j);
    sort(i, j);
}
void  sort(int lo, int hi) {
    usleep(100000);
    visualization(vec);
    if(lo >= hi)
        return;
    int j = part(lo, hi);
    sort(lo, j - 1);
    visualization(vec);
    sort(j + 1, hi);
    visualization(vec);
}

int part(int lo, int hi) {
    first = lo, second = hi + 1;
    while(true) {
        while(vec[++first] < vec[lo]) {
            compares++;
            if(first == hi)
                break;
        }
        while(vec[lo] < vec[--second]) {
            compares++;
            if(second == lo)
                break;
        }
        if(first >= second)
            break;
        exchanges++;
        swap(&vec[first], &vec[second]);
        usleep(100000);
        visualization(vec);
    }
    exchanges++;
    swap(&vec[lo], &vec[second]);
    usleep(100000);
    visualization(vec);
    return second;
}

void sort(int* arr, int* aux, int lo, int hi);
void merge(int* arr, int* aux, int low, int mid, int high);

void mergeSort() {
    int aux[N];
    for(int i = 0; i < N; i++)
        aux[i] = vec[i];
    sort(vec, aux, 0, N - 1);
}

void sort(int* arr, int* aux, int low, int high) {
    compares++;
    if(low >= high)
        return;
    int mid = low + (high - low) / 2;
    sort(arr, aux, low, mid);
    usleep(100000);
    visualization(arr);
    sort(arr, aux, mid + 1, high);
    usleep(100000);
    visualization(arr);
    merge(arr, aux, low, mid, high);
    usleep(100000);
    visualization(arr);
}
void merge(int* arr, int* aux, int low, int mid, int high) {
    first = low, second = mid + 1;
    for(int first = 0; first < N; first++)
        aux[first] = arr[first];
    for(int k = low; k <= high; k++) {
        if(first > mid) {
            arr[k] = aux[second++];
            compares++;
            exchanges++;
        } else if(second > high) {
            arr[k] = aux[first++];
            compares++;
            exchanges++;
        } else if(aux[first] > aux[second]) {
            arr[k] = aux[second++];
            compares++;
            exchanges++;
        } else {
            arr[k] = aux[first++];
            compares++;
            exchanges++;
        }
        usleep(100000);
        visualization(arr);
    }
}


void initGL() {
    glClearColor(1.0f, 0.75f, 1.0f, 1.0f);
}

void display() {
    visualization(vec);
}

void navigate(int value) {
    if(value < sortingAlgo) {
    } else {
    }
    sortingAlgo = value;
    visualization(vec);
}

void visualizeByArray(int* vec) {
    glClear(GL_COLOR_BUFFER_BIT); // sets the previous background with the current background
    banner();
    if(sortingAlgo == 0)
        sortName = "Bubble Sort";
    else if(sortingAlgo == 1)
        sortName = "Insertion Sort";
    else if(sortingAlgo == 2)
        sortName = "Quick Sort";
    else
        sortName = "Merge Sort";
    drawBitmapString(600, 770, sortName);
    drawBitmapString(600, 750, "Number of Compares:" + std::to_string(compares));
    drawBitmapString(600, 730, "Number of Exchanges:" + std::to_string(exchanges));
    int x = 100;
    for(int i = 0; i < N; i++) {
        glBegin(GL_POLYGON);
        if(i % 2)
            glColor3f(1.0f, 0.2f, 0.0f); //red
        if(i % 2 == 0)
            glColor3f(1.0f, 0.0f, 0.0f); //red
        if(i == first)
            glColor3f(0.0f, 0.0f, 1.0f); //blue
        else if(i == second)
            glColor3f(0.0f, 0.5f, 0.0f); //green
        glVertex2f(x + 50, 450);
        glVertex2f(x, 450);
        glVertex2f(x, 500);
        glVertex2f(x + 50, 500);
        //          glVertex2f(x + 50, 0);
//        glVertex2f(x, 0);
//        glVertex2f(x, 10*(vec[i] + 1));
//        glVertex2f(x + 50,10*(vec[i] + 1));
        glEnd();
        drawBitmapString(x + 18, 470, std::to_string(vec[i]));
        drawBitmapString(520, 370, "Press 's' to start the SORTING SIMULATION !");
        drawBitmapString(570, 300, "Press 'r' to randomize the array");
        drawBitmapString(430, 270, "Use LEFT/RIGHT arrow key to change the sorting algorithm ;-)");
        drawBitmapString(1250, 130,  "Press 'd' for Light mode");
        drawBitmapString(1250, 100,  "Press 'n' for Dark mode");
        x += 50;
        if(sortingAlgo < 1 && first >= 0 && second >= 0) {
            drawBitmapString(180, 320, "Compare(" + std::to_string(vec[first]) + ", " + std::to_string(vec[second]) + ")");
            glBegin(GL_POLYGON);
            glColor3f(0, 1, 0); glVertex3f(250, 250, 0);
            glColor3f(1, 0, 0); glVertex3f(200, 250, 0);
            glColor3f(0, 0, 1); glVertex3f(225, 300, 0);
            glEnd();
        }
    }
//   glutTimerFunc(20, update, 0);
//   glutSwapBuffers();
    glFlush();
    glutPostRedisplay();
}

void visualizeByBar(int* vec) {
    glClear(GL_COLOR_BUFFER_BIT); // sets the previous background with the current background
    banner();
    if(sortingAlgo == 0)
        sortName = "Bubble Sort";
    else if(sortingAlgo == 1)
        sortName = "Insertion Sort";
    else if(sortingAlgo == 2)
        sortName = "Quick Sort";
    else
        sortName = "Merge Sort";
    drawBitmapString(600, 870, sortName);
    drawBitmapString(600, 850, "Number of Compares:" + std::to_string(compares));
    drawBitmapString(600, 830, "Number of Exchanges:" + std::to_string(exchanges));
    int x = 100;
    for(int i = 0; i < N; i++) {
        glBegin(GL_POLYGON);
        if(i % 2)
            glColor3f(1.0f, 0.2f, 0.0f); //red
        if(i % 2 == 0)
            glColor3f(1.0f, 0.0f, 0.0f); //red
        if(i == first)
            glColor3f(0.0f, 0.0f, 1.0f); //blue
        else if(i == second)
            glColor3f(0.0f, 0.5f, 0.0f); //green
        glVertex2f(x + 50, 0);
        glVertex2f(x, 0);
        glVertex2f(x, 10 * (vec[i] + 1));
        glVertex2f(x + 50, 10 * (vec[i] + 1));
        glEnd();
        drawBitmapString(x + 18, 10, std::to_string(vec[i]));
//        drawBitmapString(520, 370, "Press 's' to start the SORTING SIMULATION !");
//        drawBitmapString(570, 300, "Press 'r' to randomize the array");
//        drawBitmapString(430, 270, "Use LEFT/RIGHT arrow key to change the sorting algorithm ;-)");
        drawBitmapString(1250, 930,  "Press 'd' for Light mode");
        drawBitmapString(1250, 900,  "Press 'n' for Dark mode");
        x += 50;
        if(sortingAlgo < 1 && first >= 0 && second >= 0) {
            drawBitmapString(180, 920, "Compare(" + std::to_string(vec[first]) + ", " + std::to_string(vec[second]) + ")");
            glBegin(GL_POLYGON);
            glColor3f(0, 1, 0); glVertex3f(250, 850, 0);
            glColor3f(1, 0, 0); glVertex3f(200, 850, 0);
            glColor3f(0, 0, 1); glVertex3f(225, 900, 0);
            glEnd();
        }
    }
//   glutTimerFunc(20, update, 0);
//   glutSwapBuffers();
    glFlush();
    glutPostRedisplay();
}

void visualization(int* vec) {
    if(visArray)
        visualizeByArray(vec);
    else
        visualizeByBar(vec);
}

void drawBitmapString(float x, float y, std::string s) {
    if(!day)
        glColor3f(1.0f, 1.0f, 1.0f);
    else
        glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos2f(x, y);// screen coordinate at which text will appear
    int length = s.size();
    // writing charater by charater on the screen
    for(int i = 0; i < length; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
}

void randomizearray(int* vec, int length) {
    for(int i = length - 1; i > 0; --i)
        std::swap(vec[i], vec[rand() % (i + 1)]);
}

void handleKeypress(unsigned char key, int x, int y) {
    switch(key) {
    case 'd':
        day = 1;
        glClearColor(1.0, 0.75, 1.0, 1.0);
        glutPostRedisplay();
        break;
    case 'n':
        day = 0;
        glClearColor(0.0, 0.0, 0.2, 1.0);
        glutPostRedisplay();
        break;
    case 'r':
        exchanges = 0, compares = 0, first = -1, second = -1;
        randomizearray(vec, N);
        glutPostRedisplay();
        break;
    case 's':
        exchanges = 0, compares = 0, first = -1, second = -1;
        if(sortingAlgo == 0) {
            bubbleSort();
            first = -1, second = -1;
            visualization(vec);
        } else if(sortingAlgo == 1) {
            insertionSort();
            first = -1, second = -1;
            visualization(vec);
        } else if(sortingAlgo == 2) {
            quickSort();
            first = -1, second = -1;
            visualization(vec);
        } else {
            mergeSort();
            first = -1, second = -1;
            visualization(vec);
        }
        glutPostRedisplay();
        break;
    case 'a':
        visArray = 1;
//        visualization(vec);
        glutPostRedisplay();
        break;
    case 'b':
        visArray = 0;
//        visualization(vec);
        glutPostRedisplay();
        break;
    }
}

void SpecialInput(int key, int x, int y) {
    switch(key) {
    case GLUT_KEY_LEFT:
        if(sortingAlgo)
            navigate(sortingAlgo - 1);
        break;
    case GLUT_KEY_RIGHT:
        if(sortingAlgo < 3)
            navigate(sortingAlgo + 1);
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    srand((unsigned)time(0));
    for(int i = 0; i < N; i++)
        vec[i] = (rand() % 70) + 10;
    glutInit(&argc, argv); // initializing glut
    glutInitWindowSize(1268, 700); // size of the window
    glutCreateWindow("Sorting Algo Simulator");// name of window
    glutDisplayFunc(display); // call back function
    initGL(); // initializing GL
    glViewport(0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 1500, 0, 1000);
    glutKeyboardFunc(handleKeypress);
    glutSpecialFunc(SpecialInput);
//    glutTimerFunc(20, update, 0); //Add a timer
    glutMainLoop(); // infinite processing loop
    return 0;
}
