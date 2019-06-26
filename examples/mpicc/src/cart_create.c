#include<mpi.h>
#include<stdio.h>
#define DIM 2

int main(int argc, char** argv){
    int rank, size;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    int dim_sizes[DIM]={4,size/4};
    int wrap_around[DIM]={0,1};
    MPI_Comm grid_comm;
    int reorder=1;
    MPI_Cart_create(MPI_COMM_WORLD, DIM, dim_sizes, wrap_around, reorder, &grid_comm);
    int grank;
    MPI_Comm_rank(grid_comm, &grank);
    int coordinates[DIM];
    MPI_Cart_coords(grid_comm,grank, DIM,coordinates);
    int grid_rank;
    MPI_Cart_rank(grid_comm,coordinates,&grid_rank);
    
    int free_coords[DIM]={0,1};
    MPI_Comm row_comm;
    MPI_Cart_sub(grid_comm, free_coords,&row_comm);
    int row_size, row_rank, row_cart_rank;
    MPI_Comm_rank(row_comm, &row_rank);
    MPI_Comm_size(row_comm, &row_size);
    MPI_Cart_rank(row_comm,coordinates,&row_cart_rank);

    
    //printf("rank: %2d; grank: %2d; [%d,%2d]; grid_rank: %2d; row_rank: %2d; row_size %2d\n",rank, grank,coordinates[0],coordinates[1], grid_rank,row_rank,row_size);
    //printf("===========\n");
    int rank_source, rank_dest;
    int direction=0;
    int displacement=1;
    MPI_Cart_shift(row_comm, direction, displacement, &rank_source,&rank_dest);
    printf("rank: %2d; grank: %2d; [%d,%2d]; grid_rank: %2d; row_rank: %2d; row_size %2d; rank_source %2d; rank_dest %2d; row_cart_rank %2d\n",
           rank, grank,coordinates[0],coordinates[1], grid_rank,row_rank,row_size, rank_source, rank_dest, row_cart_rank);   
    MPI_Finalize();
    return 0;
}
