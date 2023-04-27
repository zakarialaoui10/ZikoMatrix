#include "ZikoMatrix.h"
void setup() 
{
  Serial.begin(9600);
  int arr[2][4] = {{1,2,3,7}, {9,4,5,6}};
  Matrix<2, 4,int> m(arr);
  m.print();
  m.transpose();
  m.print();
}
