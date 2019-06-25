

/*
 * @name 	alg20.c
 * @brief	The code implements Alg20 of chapter 2 of course "parallel algorithm"
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>


int main()
{
   int numb_stage, arrayDim;
   float *rand_numb; 
   float sum =0;  
   clock_t start_t;
 
   printf("Enter number of stage, the total number of data would be 2^stage\n");
   printf("numb_stage = "); 
   scanf("%d", &numb_stage);
   arrayDim = pow(2,numb_stage);

   printf("numb_stageumber of data = %d \n", arrayDim);
   rand_numb = (float*) malloc(numb_stage * sizeof(float));
   
   // initializing "rand_numb" with random nunber bewteen 0-19 and 
   for (int i=0; i<arrayDim; i++)
   {
<<<<<<< HEAD
      *(rand_numb+i) = rand() % 20;
      sum += *(rand_numb+i);
    //  printf("rand_numb%d= %f\n",i,*(a+i));
=======
      *(a+i) = rand() % 20;
      sum += *(a+i);
      printf("a%d= %f\n",i,*(a+i));
>>>>>>> c2326a29447d76a65dec01e053104a7ad2cc5b3e
   }
   
   start_t = clock();
   for (int k=0; k<=numb_stage; k++)
   {
         for (int i=0; i<pow(2,(numb_stage-k)); i++)
     {
        *(rand_numb+i) = *(rand_numb+2*i) + *(rand_numb+2*i+1);
     }	     
   }

   printf("Operation time= %f\n",(float)((clock() - start_t) / CLOCKS_PER_SEC));
   printf("result= %f\n", *rand_numb);
   printf("result (correct)= %f\n",sum);
   
   return 0;
}
