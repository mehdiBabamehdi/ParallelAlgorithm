

/*
 * @name 	alg20.c
 * @brief	The code implements Alg20 of chapter 2 ofparallel algorithm course
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main()
{
   int N, arrayDim;
   double *a; 	
   printf("number of data= ");
   scanf("%d", &arrayDim);

   N = (int)((log((double)arrayDim)) / log(2.0)) - 1;

   printf("Dimension of data = %d \n", N);
   a = (double*) malloc(N * sizeof(double));

   for (int i=0; i<arrayDim; i++)
   {
      
      *(a+i) = 1.3;	//rand() * 2;
      
      printf("a= %f\n",*(a+i));
 
   }
   
   for (int k=0; k<=N; k++)
   {
         for (int i=0; i<pow(2,(N-k)); i++)
     {
        *(a+i) = *(a+2*i) + *(a+2*i+1);
     }	     
   }

   printf("result= %f\n", *a);

   return 0;
}
