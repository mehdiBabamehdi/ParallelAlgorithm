#include<mpi.h>
#include<stdio.h>

int main(int argc, char** argv){
    int rank, size;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int i;
    int message=rank;
    int rec_buf;
    int count=1;
    int tag=0;
    MPI_Status status;
    double starttime, endtime;
    
    MPI_Barrier(MPI_COMM_WORLD);
    starttime=MPI_Wtime();
    for(i=0;i<10;i++){
        if (rank%2==0){
            MPI_Send(&message, count, MPI_INT, (rank+1)%size, tag, MPI_COMM_WORLD);
            MPI_Recv(&rec_buf, count, MPI_INT, (rank-1)%size, tag, MPI_COMM_WORLD,&status);
        }
        else{
            MPI_Recv(&rec_buf, count, MPI_INT, (rank-1)%size, tag, MPI_COMM_WORLD,&status);
            MPI_Send(&message, count, MPI_INT, (rank+1)%size, tag, MPI_COMM_WORLD);
        }
        printf("rank %d received message %d\n", rank, rec_buf);
        message=rec_buf;
        MPI_Barrier(MPI_COMM_WORLD);
        if (rank==0) printf("\n");
        MPI_Barrier(MPI_COMM_WORLD);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    endtime=MPI_Wtime();
    
//Fun with datatypes
    if (rank==0){
        printf("overall time: %f\n", endtime-starttime);
        int intsize;
        int charsize;
        MPI_Type_size(MPI_INT, &intsize);
        MPI_Type_size(MPI_CHAR, &charsize);
        
        printf("Size of Int: %d\nSize of Char: %d\n", intsize, charsize);
        MPI_Get_count(&status, MPI_CHAR, &count); //will be 4, as int is 4 bytes and char is 1 byte
        printf("count was %d\n",count);
    }
    
    
    MPI_Finalize();
    return 0;
}
