#include<mpi.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(int argc, char** argv){
    int rank, size;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    int send_data[4];
    if (rank==0){
        send_data[0]=4;
        send_data[1]=3;
        send_data[2]=2;
        send_data[3]=1;
    }
    int send_count=1;
    int recv_data[1];
    int recv_count=1;
    int root=0;
    
    MPI_Scatter(send_data, send_count, MPI_INT, recv_data, 
                recv_count, MPI_INT, root, MPI_COMM_WORLD);
    printf("rank %d, send_data %d, recv_data %d\n",rank,*(send_data+1),*recv_data);
    
    
    MPI_Finalize();
    return 0;
}
