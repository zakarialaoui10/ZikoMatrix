#include "ZikoMatrix.h"
int arr[2][3] = {{1,2,3}, {4,5,6}};
Matrix<2, 3,int> m(arr);
int multiply_by_two(int n) {
    return n * 2;
}
void setup() 
{
  Serial.begin(9600);
  m.print();
  m.foreach(multiply_by_two);
  m.print();
}
