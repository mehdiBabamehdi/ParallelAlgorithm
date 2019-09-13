
#include "aux.h"

  void matrix_gen(double** array, int m, int n)
  {
    srand(time(NULL));
    printf("matrix %d*%d \n", m,n);
    for (int i = 0; i < m; ++i)
    {
        printf("\t");
        for (int j = 0; j < n; ++j)
        {
            array[i][j] = (double) (rand() % 100);
            printf("%f  ", array[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
