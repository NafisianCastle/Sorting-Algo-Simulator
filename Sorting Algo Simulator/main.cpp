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

<<<<<<< HEAD
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

=======
int partition(int array[], int low, int high) {
    int pivot = array[high];
    int i = (low - 1);
   
>>>>>>> 4732952fdeda0091fac5a5ebf77cf3538b0c0a40
    for(int j = low; j < high; j++) {
        if(arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
<<<<<<< HEAD
    swap(&arr[i + 1], &arr[high]);
=======
    swap(&array[i + 1], &array[high]);
>>>>>>> 4732952fdeda0091fac5a5ebf77cf3538b0c0a40
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if(low < high) {
<<<<<<< HEAD
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
=======
      
        int pi = partition(array, low, high);
        quickSort(array, low, pi - 1);
        quickSort(array, pi + 1, high);
>>>>>>> 4732952fdeda0091fac5a5ebf77cf3538b0c0a40
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
