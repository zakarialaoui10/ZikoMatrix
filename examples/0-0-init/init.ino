#include "ZikoMatrix.h"
int arr[2][3] = {{1,2,3}, {4,5,6}};
Matrix<2, 3,int> m(arr);
void setup() 
{
  Serial.begin(9600);
    m.print();
}
