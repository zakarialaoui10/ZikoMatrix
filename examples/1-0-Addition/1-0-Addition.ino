#include "ZikoMatrix.h"
int arr1[2][3] = {{1,2,3}, {4,5,6}};
int arr2[2][3] = {{2,3,4}, {5,6,7}};
Matrix<2, 3,int> M1(arr1);
Matrix<2, 3,int> M2(arr2);
Matrix<2, 3,int> M3=M1+M2;
void setup() 
{
  Serial.begin(9600);
    Serial.println("M1 : ");
    M1.print();
    Serial.println("M2 : ");
    M2.print();
    Serial.println("M3=M1+M2 : ");
    M3.print();
    M3+=10;
    Serial.println("M3+=10 : ");
    M3.print();
    M2+=M1;
    Serial.println("M2+=M1 : ");
    M2.print();
}
