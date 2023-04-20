## Initialize
``` C++
 // 1 
 int arr[2][3] = {{1, 2, 3}, {4, 5, 6}};
 Matrix<2,3,int> M1(arr);
 // 2
 int arr[] = {1.6, 2.2, 3.9 , 4.7, 5.3, 6.8};
 Matrix<2,3,float> M2(arr);
 // 3
 Matrix<5,5,int> // A 5x5 Matrix filled by zeros
```
## Print to the terminal 
``` C++
  M1.print();
```
## Acces And Set Data
|Mehode|Acces|Set|
|-|--|--|
|1|`M[i][j]`|`M[i][j]=4`|
|2|`M(i,j)`|`M(i,j)=4`|
## Static Methodes 
``` C++
  int r=2,c=3;
  Matrix<r, c> z = Matrix<r, c>::zeros();
  Matrix<r, c> o = Matrix<r, c>::ones();
  Matrix<3> Id = Matrix<3>::id();
```
## Operators
``` C++
   int arr1[2][3] = {{1, 2, 3},{4, 5, 6}};
   int arr2[2][3] = {{2, 3, 4},{5, 6, 7}};
   Matrix<2,3,int> M1(arr1);
   Matrix<2,3,int> M2(arr2);
   Matrix<2,3,int> M3=M1+M2;
   Matrix<2,3,int> M4=M1-M2;
   M3+=M3;
   M4-=M3;
```
## Other Methodes 
|Methode|description|condition|
|--|--|--|
|`.reshape(r,c)`||r*c should be equal to rows * cols|
|`.transpose()`|Transposes the given matrix |void|
## Testers
|Methode|description|
|--|--|
|isSquare|determines whether a given matrix is square or not|
|isSym|determines whether a given matrix is symmetric or not|
