

#include "imp_GE_s.h"
#include "aux.h"


int main()
{
    int n = 8;
    int nb = 4;
    double** A;

    /* allocate the array */
    A = malloc(n * sizeof * A);
    for (int i = 0; i < n; ++i)
    {
        A[i] = malloc(n * sizeof *A[i]);
    }

    matrix_gen(A, n, n);

    printf ("time of operation = %lf \n", LU_ijk_blocked((*LU_kij_nonBlocked), A, n,nb));
    printf("A \n");
    for (int i = 0; i < n; ++i)
    {
        printf("\t");
        for (int j = 0; j < n; ++j)
        {
            printf("%lf  ", A[i][j]);
        }
        printf("\n");
    }
    
    /* deallocate the array */
    for (int i = 0; i < n; ++i)
    {
        free(A[i]);
    }
        
    free(A);
}
