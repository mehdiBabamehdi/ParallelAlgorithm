#include "aux.h"

  void func(float** array, int n)
  {
      printf("A \n");
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            array[i][j] = (float) (rand() % 100);
            printf("%f  ", array[i][j]);
        }
        printf("\n");
    }
  }
