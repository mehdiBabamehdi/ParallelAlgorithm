

/*
 * @name 	 alg20_2c.c
 * @brief	 The code implements Alg20 of chapter 2 of course "parallel algorithm"
 * @author Mehdi
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

// (possible) TODO 's:

// ** add description/comments
// ** add error check
// ** utilities that will be also used in other implementations of algorithms,
//    such as clock-related functions, presentation of results, etc, would be
//    better to modularize them and put them in another file
// ** avoid using direct user-input like scanf. Use instead input files (e.g.
//    data.in) and read from that file

void fan_in_sum_seq(){

   int numb_stage, array_dim;
   float *rand_numb; 
   float sum =0;  

   struct timespec start_t ={0,0} , end_t={0,0};
   printf("Enter number of stage, the total number of data would be 2^stage\n");
   printf("stage number = "); 
   scanf("%d", &numb_stage);
   array_dim = pow(2,numb_stage);

   printf("number of data = %d \n", array_dim);
   rand_numb = (float*) malloc(numb_stage * sizeof(float));
   
   // initializing "rand_numb" with random nunber bewteen 0-19 and 
   for (int i=0; i<array_dim; i++)
   {
      *(rand_numb+i) = rand() % 20;
      sum += *(rand_numb+i);
   }
   
   clock_gettime(CLOCK_MONOTONIC,&start_t);
   for (int k=0; k<=numb_stage; k++)
   {
         for (int i=0; i<pow(2,(numb_stage-k)); i++)
     {
        *(rand_numb+i) = *(rand_numb+2*i) + *(rand_numb+2*i+1);
     }	     
   }

   clock_gettime(CLOCK_MONOTONIC,&end_t);
   printf("Operation time= %f nsec\n",(( double)((end_t.tv_sec + 1.0e-9*end_t.tv_nsec) - (double) (start_t.tv_sec - 1.0e-9*start_t.tv_nsec))));
   printf("result= %f\n", *rand_numb);
   printf("result (correct)= %f\n",sum);
   
   //return 0;

}
