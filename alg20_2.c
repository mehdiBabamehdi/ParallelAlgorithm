

/*
 * @name 	alg20.c
 * @brief	The code implements Alg20 of chapter 2 of course "parallel algorithm"
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main()
{
   int N, arrayDim;
   double *a; 
   double sum =0;   
   printf("number of data (power of 2 e.g. 4,8,16,...)= ");
   scanf("%d", &arrayDim);

   N = (int)((log((double)arrayDim)) / log(2.0)) - 1;

   printf("Dimension of data = %d \n", N);
   a = (double*) malloc(N * sizeof(double));

   for (int i=0; i<arrayDim; i++)
   {
      *(a+i) = rand() % 20;
      sum += *(a+i);
      printf("a%d= %f\n",i,*(a+i));
   }
   
   for (int k=0; k<=N; k++)
   {
         for (int i=0; i<pow(2,(N-k)); i++)
     {
        *(a+i) = *(a+2*i) + *(a+2*i+1);
     }	     
   }

   printf("result= %f\n", *a);
   printf("result (correct)= %f\n",sum);

   return 0;
}
