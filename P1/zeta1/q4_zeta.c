#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <math.h>
double* zeta_part(int n);
int main(int argc, char **argv)
{
	int rank, size, tag, i;
	MPI_Status status;
	
	printf("This programm computes pi using the zeta function with n steps \n");

	int n = 100;

	
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	tag = 100; //Nutzen?
	
	printf("Starting\n");
	
	if(rank ==0)
	{	
		printf("Now at worker 0\n");
		// computing summand-vector
		double*v = zeta_part(n);
		// workdistribution vector
		int work_distr[rank-2]; //cell 0 is for worker 1 etc.
		//distributing summation work on other workers
		//if(size>1)
		//{	//ELSE: TODO: Serial case
		
			int n_part = n/(size-1); //length of the vector snippet
			printf("Start calculating workload\n");
			for(int i=0; i<size-1;i++)
			{
				work_distr[i] = n_part;
			}
			if(n%(size-1)>0)
			{	//Distributing leftover work
				for(int i=0; i<n%(size-1);i++)
				{
					work_distr[i] ++;
				}
			}
			int counter = 0;
			printf("Start distributing workload");
			for(int i =1; i<size; i++)
			{	
				//Sending information about the length of the incoming vector
				MPI_Send(&work_distr[i-1],1,MPI_INT,i,tag,MPI_COMM_WORLD);
				//Sending actual Vector snippet
				MPI_Send(&v[counter],work_distr[i-1],MPI_DOUBLE,i,tag,MPI_COMM_WORLD);
				//increasing counter.
				counter = counter + work_distr[i-1];	
				printf("Data sent to worker %i\n",i);		
			}
			
			//Recieving sums from workers
			double Sn = 0;
			double sum = 0;
			for(int i =1; i<size; i++)
			{	
				MPI_Recv(&sum,1, MPI_DOUBLE,i,tag,MPI_COMM_WORLD, &status);
				printf("Data recieved by worker 0\n");
				Sn = Sn + sum;
			}
			printf("The result is: %.18f\n", sqrt(Sn*6));
			free(v);
		//}
		
	}
	else
	{
		printf("Now at worker %i\n", rank);
		int length;
		//Recieving information about the length of the vector
		MPI_Recv(&length,1, MPI_INT,0,tag,MPI_COMM_WORLD, &status);
		//Recieving actual vector snippet
		printf("Revieved array information at worker %i\n", rank);
		double vec[length];
		MPI_Recv(vec,length, MPI_DOUBLE,0,tag,MPI_COMM_WORLD, &status);
		printf("Data revieved by worker %i\n",rank);
		double sum = 0;
		for(int i = 0; i<length;i++)
		{
			sum = sum + vec[i];
		}
		
		//Sending sum back to process 0
		
		MPI_Send(&sum,1,MPI_DOUBLE,0,tag,MPI_COMM_WORLD);
		printf("Data sent back to worker 0 by worker %i\n", rank);
	}
	
	MPI_Finalize();
	
	return 0;	
}

double* zeta_part(int n)
{
	double *v = (double* ) malloc(n*sizeof(double));
	if(!v)
	{
		printf("Error: Could not allocate array. Exiting\n");
		exit(1);
	}
	double d_i;
	
	for(int i = 1; i<=n;i++)
	{
		d_i = (double) i;	
		v[i-1] = 1/(d_i*d_i);
	}
	return v;	
}
