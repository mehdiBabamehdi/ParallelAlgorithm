

#ifndef CHLSKY
#define CHLSKY

  #include <stdlib.h>
  #include <stdio.h>
  #include <math.h>
  #include <time.h>
  #include <cblas.h>
  
  void chlsky_nonBlocked(double** A, int n);
  void chlsky_Blocked(double** A, int n, int nb);
  
  
#endif
