#include "ZikoMatrix.h"
int arr[2][4] = {{1,2,3,7}, {9,4,5,6}};
Matrix<2, 4,int> m(arr);
void setup() 
{
  Serial.begin(9600);
    m.print();
}
