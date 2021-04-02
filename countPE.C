#include <stdio.h>
#include <math.h>
#include "mpi.h"

int main(int argc, char** argv){
	int my_PE_num,numprocs,num=1,mynum,totnum;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_PE_num);

	MPI_Bcast(&num, 1, MPI_INT, 0, MPI_COMM_WORLD);

	mynum = num;

	// printf("Interval on PE %d is (%f,%f)\n",my_PE_num,start,end);

	MPI_Reduce(&mynum, &totnum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (my_PE_num == 0){
    	printf("Total number of PEs are %d PE (intrinsic) vs %d PE (reduction).\n", numprocs, totnum);
    }

	MPI_Finalize();
}