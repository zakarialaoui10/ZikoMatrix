#include "ZikoMatrix.h"
double arr[2][3] = {{1,2,3}, {4,5,6}};
void setup() 
{
  Serial.begin(9600);
  Matrix<2, 3,double> m(arr);
  m.lerp(0,10);
  m.print();
}
