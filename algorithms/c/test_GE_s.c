

#include "imp_GE_s.h"
#include "aux.h"


int main()
{
    int n = 8;
    int nb = 4;
    float** A;

    /* allocate the array */
    A = malloc(n * sizeof * A);
    for (int i = 0; i < n; ++i)
    {
        A[i] = malloc(n * sizeof *A[i]);
    }

    /* use the array */
    func(A, n);

    printf ("time of operation = %lf \n", LU_ijk_blocked((*LU_kij_nonBlocked), A, n,nb));
    printf("A \n");
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            printf("%f  ", A[i][j]);
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
