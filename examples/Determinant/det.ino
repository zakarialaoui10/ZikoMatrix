#include "ZikoMatrix.h"
double arr[3][3] = {{0,1,2},{3,4,5},{6,7,8}};
void setup(){
  Serial.begin(9600);  
  Matrix<3, 3,double> M(arr);
  Serial.print("The determinant of M is : ");
  Serial.print(M.det());
}
