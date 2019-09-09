#ifndef IMP_GE_S
  #define IMP_GE_S
  
  #include <stdlib.h>
  #include <stdio.h>
  #include <math.h>
  #include <time.h>
 
  void func(float** array, int n);
  void LU_kij_nonBlocked(float** , int);
  void LU_kji_nonBlocked(float** , int);  
  void LU_jki_nonBlocked(float** , int); 
  void LU_kij_nonBlocked_pivoting(float** , int);
  void LU_kji_nonBlocked_pivoting(float** , int);
  void LU_jki_nonBlocked_pivoting(float** , int);
  double func_handler(void (*)(float**, int), float** , int);
  double LU_ijk_blocked(void (*)(float**, int), float** , int, int);
  
#endif
