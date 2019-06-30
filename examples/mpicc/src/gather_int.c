#include<mpi.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(int argc, char** argv){
    int rank, size;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    int sendbuf=rank;
    int sendcount=1;
    int recv_data[size];
    int recv_count=sendcount;
    int root=0;
    MPI_Gather(&sendbuf, sendcount, MPI_INT, recv_data, recv_count, MPI_INT, root, MPI_COMM_WORLD);
    printf("rank %d,sendbuf %d, recv_data %d%d%d%d\n",rank,sendbuf,recv_data[0],recv_data[1],recv_data[2],recv_data[3]);

    MPI_Finalize();
    return 0;
}
