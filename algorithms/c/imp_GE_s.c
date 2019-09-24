

#include "imp_GE_s.h"

// This is a function handler developed to get functions as function pointer
// and call the desired function and calculate time of operation
// to call the function:
//      func_handler((<pointer to the function>),<argument>)
//      e.g. func_handler((*LU_kij_nonBlocked),(double**)A)
double func_handler(void (*func)(double**, int), double** A, int n)
{
   struct timespec start_t ={0,0} , end_t={0,0};
   void (*called_func) (double**, int);

   clock_gettime(CLOCK_MONOTONIC,&start_t);
   called_func = func;
   called_func(A,n);
   clock_gettime(CLOCK_MONOTONIC,&end_t);
 
   return (((double)((end_t.tv_sec + 1.0e-9*end_t.tv_nsec) -\
            (double)(start_t.tv_sec - 1.0e-9*start_t.tv_nsec))));
}


// non-blocked KIJ form of GE without column pivoting 
void LU_kij_nonBlocked(double** A, int n)
{
    for (int k = 0; k < n; ++k)
    {       
        for (int i = k + 1; i < n; ++i)
        {
            A[i][k] = A[i][k] / A[k][k];
            for (int j = k + 1; j < n; ++j)
            {
                A[i][j] -= A[i][k] * A[k][j];
            }
        }
    }
}


// non-blocked KJI form of GE without column pivoting 
void LU_kji_nonBlocked(double** A, int n)
{
    for (int k = 0; k < n; ++k)
    {
        // compute all the multiplier
        for (int i = k + 1; i < n; ++i)
        { 
            A[i][k] = A[i][k] / A[k][k];
        }
       
        for (int j = k + 1; j < n; ++j)
        {
            for (int i = k + 1; i < n; ++i)
            {
                A[i][j] -= A[i][k] * A[k][j];
            }
        }
    }
}


// non_blocked JKI form of GE without column pivoting 
void LU_jki_nonBlocked(double** A, int n)
{
    // apply earlier transformation of column j
    for (int j = 0; j < n; ++j)
    {
        for (int k = 0; k < j - 1; ++j)
        {
            for (int i = k + 1; i < n; ++i)
            {
            A[i][j] -= A[i][k] * A[k][j];
            }
        }      

        for (int i = j + 1; i < n; ++i)
        {
            A[i][j] = A[i][j] / A[i][i];
        }

        // apply all interchange to L
        for (int j = 0; j < n; ++j)
        {
            for (int k = j + 1; k < n; ++k)
            {

            }
        }
   }
}


// non-blocked KIJ form of GE with column pivoting 
void LU_kij_nonBlocked_pivoting(double** A, int n)
{
    int max;
    int* p = (int*) malloc(n * sizeof(int)); // array used for permutaion of rows in pivoting
 
    for (int k = 0; k < n; ++k)
    {   
        max = A[*(p+k)][k];
        for (int i = k; i < n; ++i)
        {
            if (A[k][i] > max) 
            {
                max = A[k][i];
                *(p+i) = k;
                *(p+k) = i;
            }
        }
        
        for (int i = k + 1; i < n; ++i)
        {
            A[*(p+i)][k] = A[*(p+i)][k] / A[*(p+i)][k];
            for (int j = k + 1; j < n; ++j)
            {
                A[*(p+i)][j] -= A[*(p+i)][k] * A[*(p+k)][j];
            }
        }
    }
}


// non-blocked KJI form of GE with column pivoting 
void LU_kji_nonBlocked_pivoting(double** A, int n)
{
    int max;
    int* p = (int*) malloc(n * sizeof(int)); // array used for permutaion of rows in pivoting

    // initialize the permutaion array    
    for (int i = 0; i < n; ++i)
    {
       *(p+i) = i;
    }

    for (int k = 0; k < n; ++k)
    {
        // column pivoting
        max = A[*(p+k)][k];
        for (int i = k; i < n; ++i)
        {
            if (A[k][i] > max) 
            {
                max = A[k][i];
                *(p+i) = k;
                *(p+k) = i;
            }
        }
        
        // compute all the multiplier
        for (int i = k + 1; i < n; ++i)
        { 
            A[*(p+i)][k] = A[*(p+i)][k] / A[*(p+k)][k];
           
        }
       
        for (int j = k + 1; j < n; ++j)
        {
            for (int i = k + 1; i < n; ++i)
            {
                A[*(p+i)][j] -= A[*(p+i)][k] * A[*(p+k)][j];
            }
        }
    }
}


// non_blocked JKI form of GE with column pivoting 
void LU_jki_nonBlocked_pivoting(double** A, int n)
{
    int max;
    int* p = (int*) malloc(n * sizeof(int)); // array used for permutaion of rows in pivoting

    // initialize the permutaion array    
    for (int i = 0; i < n; ++i)
    {
       *(p+i) = i;
    }

    // apply earlier transformation of column j
    for (int j = 0; j < n; ++j)
    {
        for (int k = 0; k < j - 1; ++j)
        {
            for (int i = k + 1; i < n; ++i)
            {
            A[i][j] -= A[i][k] * A[k][j];
            }
        }

        // column pivoting
        max = A[*(p+j)][j]; 
        for (int k = 0; k < n; ++k)
        {
            if (A[k][j] > max) 
            {
            max = A[k][j];
            *(p+j) = k;
            *(p+k) = j;
            }
        }

        for (int i = j + 1; i < n; ++i)
        {
            A[*(p+i)][j] = A[*(p+i)][j] / A[*(p+i)][*(p+i)];
        }

        // apply all interchange to L
        for (int j = 0; j < n; ++j)
        {
            for (int k = j + 1; k < n; ++k)
            {

            }
        }
   }
}


// blocked form of GE with column pivoting for given of nonblocked GE
double LU_ijk_blocked(void (*func)(double**, int), double** A, int n, int nb)
{
    struct timespec start_t ={0,0} , end_t={0,0};
    int N = floor(n / nb);
    
    void (*called_func) (double**, int);
    called_func = func;
    
    clock_gettime(CLOCK_MONOTONIC,&start_t);
    for (int k = 0; k < N; k++)
    {
        for (int l = 0; l < N; l++)
        {
            
            int x = nb * k;
            int y = nb * l;
            // Create a new outer array to hold pointers to the element of each inner array
            double** submat = (double **) calloc(nb, sizeof(double*));
            for (int i = 0; i < nb; i++)
            {
                submat[i] = A[y++] + x;
            }
                        
            called_func(submat, nb);
          }
    }
    
    clock_gettime(CLOCK_MONOTONIC,&end_t);
 
    return (((double)((end_t.tv_sec + 1.0e-9*end_t.tv_nsec) -\
             (double)(start_t.tv_sec - 1.0e-9*start_t.tv_nsec))));
}


// blocked form of GE with column pivoting for given of nonblocked GE using CBLAS lib
double LU_ijk_blocked_BLAS(void (*func)(double**, int), double** A, int n, int nb)
{
    
}

