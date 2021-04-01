#include <bits/stdc++.h>
#include<GL/gl.h>
#include <GL/glut.h>
#include <windows.h>
using namespace std;

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for(int j = low; j < high; j++) {
        if(arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if(low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

float _angle1 = 0.0f;


void visualize_array(){

}

void drawScene(){

}

int main(int argc, char** argv) {
     int sz;
   cout<<"Enter the size of array::";
   cin>>sz;
   int randArray[sz];
   for(int i=0;i<sz;i++)
      randArray[i]=rand()%100+1;  //Generate number between 0 to 99

   cout<<"\nElements of the array::"<<endl;

   for(int i=0;i<sz;i++)
      cout<<"Elements no "<<i+1<<"::"<<randArray[i]<<endl;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Sorting Allgo Simulator");
    glutDisplayFunc(drawScene);
  //  glutTimerFunc(20, update, 0); //Add a timer
    glutMainLoop();
    return 0;
}
