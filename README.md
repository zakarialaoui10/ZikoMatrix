## Intialise
``` C++
 //1 
 int arr[2][3] = {{1, 2, 3}, {4, 5, 6}};
 Matrix<2,3> M1(arr);
 // 2
 int arr[] = {1, 2, 3 , 4, 5, 6};
 Matrix<2,3> M2(arr);
```
## Print to the terminal 
``` C++
  M1.print();
```

## Static methodes 
``` C++
  int r=2,c=3;
  Matrix<2, 2> z = Matrix<3, 3>::zeros();
  Matrix<2, 2> o = Matrix<3, 3>::ones();
```
