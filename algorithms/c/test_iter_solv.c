

#include "iter_solv.h"
#include "aux.h"

int main()
{
    int n = 16;
    int nb = 4;
    double** A;
    double** b;
    double** x;
    double error;

    /* allocate the array */
    A = malloc(n * sizeof * A);
    for (int i = 0; i < n; ++i)
    {
        A[i] = malloc(n * sizeof *A[i]);
    }
    
    matrix_gen(A, n, n);
    
    b = malloc(n * sizeof * b);
    for (int i = 0; i < n; ++i)
    {
        b[i] = malloc(1 * sizeof *b[i]);
    }
   vector_gen(b,n);
    
    x = malloc(n * sizeof * x);
    for (int i = 0; i < n; ++i)
    {
        x[i] = malloc(1 * sizeof *x[i]);
    }
    
    for (int i = 0; i < n; ++i)
    {
        x[i][1] = 1.0;
    }
    
    jacobi_serial(A, x, b, n,1e-10);
    printf("x=\n  ");
    for (int i = 0; i < n; ++i)
    {
        printf("\t| ");
        printf("%lf | \n", x[i][1]);
        x[i][1] = 0.0;
    }
    printf("\n");
    
    SOR_serial(A, x, b, 0.9, n, 1e-10);
    printf("x=\n  ");
    for (int i = 0; i < n; ++i)
    {
        printf("\t|");
        printf("%lf | \n", x[i][1]);
    }
    printf("\n");
     
}
