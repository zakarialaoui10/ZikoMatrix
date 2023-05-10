#include "ZikoMatrix.h"
double arr43[3][3] = {{0,1,2}, {3,4,5},{6,7,8}};
double arr23[3][2] = {{0,1}, {3,4},{9,10}};
void setup(){
  Serial.begin(9600);  
  Matrix<3, 3,double> M43(arr43);
  Matrix<3, 2,double> M23(arr23);
  M43.print();
  M43.hstack(M23);
  M43.print();
}
