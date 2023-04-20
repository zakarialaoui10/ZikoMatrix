#include "ZikoMatrix.h"
int arr[2][3] = {{0,1,2,3}, {4,5,6,7},{8,9,10,11},{12,13,14,15}};
Matrix<4, 4,int> M(arr);
void setup() 
{
  Serial.begin(9600);
  M.print();
  Matrix<2, 2, int> SUBM = M.slice<2, 2>(0, 1);
  M.print();
}
