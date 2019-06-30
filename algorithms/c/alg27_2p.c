

/*
 * @name 	alg27.c
 * @brief	The code implements Alg27 of chapter 2 of course "parallel algorithm"
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <assert.h>
#include <mpi.h>

int main(int argc, char **argv)
{
   int   num_stage, num_elements;
   float *rand_nums = NULL; 
   float sum = 0;
   int   root = 0;
   int   tag = 0;
   int   num_procs, my_id;
   int   num_elements_per_proc;
   float summand = 0;
   int dest_address, source_address;
  
   double start_ts, end_ts, start_tp, end_tp;

   // Initialize MPI
   MPI_Init(&argc, &argv);
   
   // Get ID & num of procs
   MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
   MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

   printf("Hello World! I'm process %i out of %i processes\n", my_id, num_procs);
   MPI_Barrier(MPI_COMM_WORLD);

   if (my_id == root)
   {
      printf("Enter number of stage, the total number of data would be 2^stage\n");
      printf("stage number = \n"); // without "\n" it was not printed? 
      scanf("%d", &num_stage);

      num_elements = pow(2,num_stage);
      rand_nums = (float*) malloc(num_elements * sizeof(float));
     
       
      //initilize array by random numer and calculate sum for verification
      for (int i=0; i<num_elements; ++i)
      {
         *(rand_nums+i) = rand() % 10;
      }
      
      // summation serially
      start_ts = MPI_Wtime();
      for (int i=0; i<num_elements; ++i)
      {
         sum += *(rand_nums+i);
      }
      end_ts = MPI_Wtime();

      start_tp = MPI_Wtime();
   }

   MPI_Barrier(MPI_COMM_WORLD);
   // All the nodes should have num_stage
   MPI_Bcast(&num_elements,1,MPI_INT,root,MPI_COMM_WORLD);

   MPI_Barrier(MPI_COMM_WORLD);
  

   // Send data to other procs
   // It is done by MPI_Send and MPI_Recv since in the case of MPI_Scatter 
   // number of data should be a multipication of number of processor.
   // in the code, proc 0 gets part of elemet number like other proc as well as 
   // the remain elements ,i.e.
   //      number of elements in proc 0 = number of element for every proc +
   //         (all elements - number of element for every proc * number of processor)
   
   if (my_id == root)
   {
      num_elements_per_proc = num_elements - num_elements / num_procs * (num_procs - 1);
      int num_elements_for_others = floor(num_elements / num_procs);

      // send data to othe procs
      for (int i = 1; i<num_procs; ++i)
      {
         MPI_Send((rand_nums + num_elements_per_proc + (i-1) * num_elements_for_others), num_elements_per_proc, MPI_FLOAT, i, tag, MPI_COMM_WORLD);
      }
      
      // add num in proc root
      for (int i = 1; i < num_elements_per_proc; ++i)
      {
        *rand_nums += *(rand_nums + i);
      }
    } else
    {
        num_elements_per_proc = floor((float) num_elements / (float)num_procs);
        rand_nums = (float*) malloc(sizeof(float) * num_elements_per_proc);
        assert(rand_nums != NULL);
        
        // receive data from root
        MPI_Recv(rand_nums, num_elements_per_proc, MPI_FLOAT, root, tag, \
                  MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                
        // add all data
        for (int i = 1; i < num_elements_per_proc; ++i)
        {
            *rand_nums += *(rand_nums + i);
        }

    }

   MPI_Barrier(MPI_COMM_WORLD);
   
   int steps = (int) (log(num_procs) / log(2));
   for (int k=1; k <= steps; ++k)
   {
      if (fmod(my_id,pow(2,k-1)) == 0 && fmod(my_id,pow(2,k)) != 0)
      {
          dest_address = (int) fmod(my_id - (int)pow(2,k-1) + num_procs , num_procs);
          MPI_Send(rand_nums, 1, MPI_FLOAT, dest_address \
                 , tag, MPI_COMM_WORLD);
      }
      
      if (fmod(my_id,pow(2,k)) == 0)
      {
          source_address = (int) fmod(my_id + (int)pow(2,k-1) + num_procs , num_procs);
          MPI_Recv(&summand, 1, MPI_FLOAT, source_address  \
                  ,tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
          printf("stage %d   %2d --> %2d\n", k, source_address, my_id);
          *rand_nums += summand;
      }
      MPI_Barrier(MPI_COMM_WORLD);
   }

   if (my_id == root)
   {
      end_tp = MPI_Wtime();
      printf("  +---------------------------------------------+\n");
      printf("  | %16s %-27s|\n","","Result");
      printf("  +---------------+--------------+--------------+\n");
      printf("  | %-14s| %-13s| %-13s|\n", "", "PARALLEL", "SERIAL");
      printf("  +---------------+--------------+--------------+\n");
      printf("  | %-14s| %-13d| %-13d|\n","num of Element", num_elements, num_elements);
      printf("  +---------------+--------------+--------------+\n");
      printf("  | %-14s| %-13d| %-13d|\n","num of procs", num_procs, 1);
      printf("  +---------------+--------------+--------------+\n");
      printf("  | %-14s| %-13.1f| %-13.1f|\n","Result", *rand_nums, sum);
      printf("  +---------------+--------------+--------------+\n");
      printf("  | %-14s| %-13.10f| %-13.10f|\n","Time (ns)", (end_tp - start_tp), (end_ts - start_ts));
      printf("  +---------------+--------------+--------------+\n");
      printf("  | %-14s|%-5s %-22.10f | \n","Speed up","", (end_ts - start_ts)/(end_tp - start_tp));
      printf("  +---------------+--------------+--------------+\n");

      
   }

   free (rand_nums);
   MPI_Finalize();
      
   return 0;
}
