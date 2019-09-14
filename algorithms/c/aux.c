
#include "aux.h"

  void vector_gen(double** array, int m)
  {
    srand(time(NULL));
    printf("vector %d \n", m);
    for (int i = 0; i < m; ++i)
    {
        printf("\t");
        array[i][1] = (double) (rand() % 100);
        printf("%f  \n", array[i][1]);
    }
    printf("\n");
}

  void matrix_gen(double** array, int m, int n)
  {
    srand(time(NULL));
    printf("matrix %d*%d \n", m,n);
    for (int i = 0; i < m; ++i)
    {
        printf("\t");
        for (int j = 0; j < n; ++j)
        {
            if (i==j) 
            {
                array[i][j] = 4;
            }
            else if((i  == j - 1) ||( i ==  j + 1) || ( i == j + sqrt((double)n)) || ( i == j - sqrt((double)n)))
            {
                array[i][j] = -1;
            }
            else
            {
                array[i][j] = 0;
            }
            printf("%f  ", array[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
