#ifndef ITER_SOLV
  #define ITER_SOLV
  
  #include <stdlib.h>
  #include <stdio.h>
  #include <math.h>
  #include <time.h>
 
  double error_cal(double** A, double** x, double** b, int n); 
  void jacobi_serial(double** A, double** x,double** b, int n, double tol);
  void SOR_serial(double** A, double** x, double** b, double omega, int n, double tol);
  void jacobi_par(double** A, double** x, double** b, int n, int nb, double tol);
  
#endif 
