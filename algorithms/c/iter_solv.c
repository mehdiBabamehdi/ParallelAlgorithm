

#include "iter_solv.h"


double error_cal(double** A, double** x, double** b, int n)
{
  //int n = sizeof(A[0]) / sizeof(A[0][0]);
  double error = 0;
  double s = 0;
  
  for (int i = 0; i < n; ++i)
  {
    for (int j = 0; j < n; ++j)
    {
      s = s + A[i][j] * x[j][1];
    }       
    s = s - b[i][1];
    error += s*s;
  }
        
  error = sqrt(error);

  return error;
}


double jacobi_serial(double** A, double** x, double** b, int n, double tol)
{
    int count = 0;
    double error = 10;
    double s;
    
    //int n = sizeof(A[0]) / sizeof(A[0][0]);
    printf("%d =\n", n);
    while ((error >= tol) | (count < 1e2))
    {        
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if(i != j)
                {
                    s = A[i][j] * x[j][1];
                }
            }
            x[i][1] = (b[i][1] - s) / A[i][i];
        }
       error = error_cal(A,x,b,n);      
       count+=1; 
    }
    
    printf("x=\n  ");
    for (int i = 0; i < n; ++i)
    {
        printf("\t");
        printf("%lf  \n", x[i][1]);
    }
    printf("\n");
    
    printf("error = %lf\n", error);
    return error;
}

double jacobi_par(double** A, double** x, double** b, int n, int nb, double tol)
{





}
