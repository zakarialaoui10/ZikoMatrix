#include "ZikoMatrix.h"
int arr1[2][3] = {{1,2,3}, {4,5,6}};
int arr2[2][3] = {{2,3,4}, {5,6,7}};
Matrix<2, 3,int> M1(arr1);
Matrix<2, 3,int> M2(arr2);
Matrix<2, 3,int> M3=M1+M2;
Matrix<2, 3,int> M4=M1-M2;
void setup() 
{
  Serial.begin(9600);
    M1.print();
    M2.print();
    M3.print();
    M4.print();
    M3+=M1;
    M3.print();
    M4-=M2;
    M4.print();
}
