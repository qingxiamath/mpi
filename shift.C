#include <stdio.h>
#include "mpi.h"

int main(int argc, char** argv){
	int my_PE_num,numbertoreceive,numbertosend,numprocs,index;
	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_PE_num);

    for (index=0;index<numprocs;index++){
    	if (index==my_PE_num){
    		// MPI_Barrier(MPI_COMM_WORLD);
    		numbertosend = index;
    		printf("I am sending my PE number %d to my higher neighbor.\n", numbertosend);
    		if ((index+1)<numprocs){
    			MPI_Send(&numbertosend, 1, MPI_INT, index+1, index, MPI_COMM_WORLD);
    		}
    		else{
    			MPI_Send(&numbertosend, 1, MPI_INT, 0, index, MPI_COMM_WORLD);
    		}
    		MPI_Barrier(MPI_COMM_WORLD);
    	}
    }

    for (index=0;index<numprocs;index++){
    	if (index==my_PE_num){
    		MPI_Recv(&numbertoreceive, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    		printf("I am receiving the PE number %d from my lower neighbor on PE %d.\n", numbertoreceive,my_PE_num);
    		MPI_Barrier(MPI_COMM_WORLD);
    	}
    }

	MPI_Finalize();
}