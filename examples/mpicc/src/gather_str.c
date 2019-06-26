#include<mpi.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(int argc, char** argv){
    int rank, size;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    int sendcount=1;
    char sendbuf[sendcount];
    snprintf(sendbuf, sendcount+1, "%d", rank+4);

    char recv_data[size];
    int recv_count=sendcount;
    int root=0;
    MPI_Gather(sendbuf, sendcount, MPI_CHAR, recv_data, recv_count, MPI_CHAR, root, MPI_COMM_WORLD);
    printf("rank %d, sendbuf %s, recv_char %s\n",rank,sendbuf,recv_data);

    MPI_Finalize();
    return 0;
}
