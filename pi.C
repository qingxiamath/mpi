#include <stdio.h>
#include <math.h>
#include "mpi.h"

int main(int argc, char** argv){
	int my_PE_num,n,numprocs,index;
	float mypi,pi,h,x,start,end;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_PE_num);

	if (my_PE_num==0){
		printf("How many intervals? ");
		scanf("%d", &n);
	}
	MPI_Bcast(&n,1,MPI_INT, 0, MPI_COMM_WORLD);

	mypi = 0.;
	h = (float) 2./n;
	start = (float) (my_PE_num*2./numprocs)-1;
	end = (float) ((my_PE_num+1)*2./numprocs)-1;

	for (x=start; x<end; x=x+h){
		// mypi = mypi+h*2*sqrt(1-x*x);// first order
		mypi = mypi+h*2.*sqrt(1-(x+h/2.)*(x+h/2.));// midpoint
	}
	// printf("Pi sent from PE %d is %f\n",my_PE_num,mypi);
	printf("Interval on PE %d is (%f,%f)\n",my_PE_num,start,end);

	MPI_Reduce(&mypi, &pi, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (my_PE_num == 0){
    	printf("Pi is approximately %f from %d PE.\n", pi, numprocs);
    }

	MPI_Finalize();
}