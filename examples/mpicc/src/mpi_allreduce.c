#include<mpi.h>
#include<stdio.h>

int main(int argc, char** argv){
    int rank, size;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int message;
    int count=1;
    
    printf("uninitialized message: %d\n",message);
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Allreduce(&rank, &message, count, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    printf("rank: %d, message: %d\n",rank,message);

    MPI_Finalize();
    return 0;
}
