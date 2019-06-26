#include<mpi.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(int argc, char** argv){
    int rank, size;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    char send_data[5];
    if (rank==0){
        send_data[0]='A';
        send_data[1]='B';
        send_data[2]='C';
        send_data[3]='D';
    }
    int send_count=1;
    char recv_data[2];
    recv_data[1]='\0';
    int recv_count=1;
    int root=0;
    
    MPI_Scatter(send_data, send_count, MPI_CHAR, recv_data, 
                recv_count, MPI_CHAR, root, MPI_COMM_WORLD);
    printf("rank %d, send_data %s, recv_data %s\n",rank,send_data,recv_data);
    
    
    MPI_Finalize();
    return 0;
}
