#include "ZikoMatrix.h"
double arr[4][3] = {{0,1,2}, {3,4,5},{6,7,8}, {9,10,11}};
void setup(){
  Serial.begin(9600);  
  Matrix<4, 3,double> m(arr);
  m.print();
  m.deleteRow(1);
  m.print();
  m.deleteRow(0);
  m.print();
}
