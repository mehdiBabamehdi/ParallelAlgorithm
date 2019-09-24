#ifndef IMP_GE_S
  #define IMP_GE_S
  
  #include <stdlib.h>
  #include <stdio.h>
  #include <math.h>
  #include <time.h>
  #include <cblas.h>
 
  void func(double** array, int n);
  void LU_kij_nonBlocked(double** , int);
  void LU_kji_nonBlocked(double** , int);  
  void LU_jki_nonBlocked(double** , int); 
  void LU_kij_nonBlocked_pivoting(double** , int);
  void LU_kji_nonBlocked_pivoting(double** , int);
  void LU_jki_nonBlocked_pivoting(double** , int);
  double func_handler(void (*)(double**, int), double** , int);
  double LU_ijk_blocked(void (*)(double**, int), double** , int, int);
  double LU_ijk_blocked_BLAS(void (*func)(double**, int), double** , int , int );
  
#endif
