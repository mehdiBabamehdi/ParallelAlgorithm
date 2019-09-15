

#include "iter_solv.h"


double error_cal(double** A, double** x, double** b, int n)
{
  double error = 0;
  double s = 0;
  
  for (int i = 0; i < n; ++i)
  {
    s = 0;
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


void jacobi_serial(double** A, double** x, double** b, int n, double tol)
{
    int count = 0;
    double error = 10;
    double s;
    double** x_old;
    
    x_old = malloc(n * sizeof * x_old);
    for (int i = 0; i < n; ++i)
    {
        x_old[i] = malloc(1 * sizeof *x_old[i]);
    }
   
    while ((error >= tol))
    {   
              
        for (int i = 0; i < n; ++i)
        {
            x_old[i][1] = x[i][1];
        }    

        for (int i = 0; i < n; ++i)
        {
          s = 0;
            for (int j = 0; j < n; ++j)
            {
                if(i != j)
                {
                    s = s + A[i][j] * x_old[j][1];
                }
            }
            x[i][1] = (b[i][1] - s) / A[i][i];
        }
       error = error_cal(A,x,b,n);      
       count+=1; 
       if(count > 1e3) break;
    }
    printf("Jacobi: count= %d  error= %e\n", count, error);
}


void SOR_serial(double** A, double** x, double** b, double omega, int n, double tol)
{
    int count = 0;
    double error = 10;
    double s;
    double** x_old;
    
    x_old = malloc(n * sizeof * x_old);
    for (int i = 0; i < n; ++i)
    {
        x_old[i] = malloc(1 * sizeof *x_old[i]);
    }
    
    while ((error >= tol))
    {     
        
        for (int i = 0; i < n; ++i)
        {
          s = 0;
            for (int j = 0; j < n; ++j)
            {
                if (i != j)
                    s = s + A[i][j] * x[j][1];
            }
            x_old[i][1] = x[i][1];
            x[i][1] = omega* (b[i][1] - s) / A[i][i] + (1.0 - omega) * x_old[i][1];
        }
       error = error_cal(A,x,b,n);      
       count+=1; 
       if(count > 1e3) break;
    }
    
    // free memory
    for (int i=0; i<10; ++i) 
    {
        free(x_old[i]);
    }
    
    free(x_old);
    
    printf("SOR: count= %d  error= %e\n", count, error);
}

void jacobi_par(double** A, double** x, double** b, int n, int nb, double tol)
{





}
