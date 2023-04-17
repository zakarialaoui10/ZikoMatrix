
#include <iostream>
#include"ZikoMatrix.h"
using namespace std;



int main()
{
    int arr1[2][3] = {{1, 2, 3}, {4, 5, 6}};
    int arr2[2][3] = {{2, 3, 4}, {5, 6, 7}};
    Matrix<2, 3> m1(arr1);
    Matrix<2, 3> m2(arr2);
    m1-=m2;
    m1.print();
    Matrix<2,3> a=m1+m1;
    Matrix<2,2> b({1,2,3,4});
    a.print();
    b.print();
    //Matrix<3, 3> ones = Matrix<3, 3>::ones();
    //ones.print();
    return 0;
}
