#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "mpi.h"

#define M_PI 3.14159265358979323846


void mach_part(double*v,int n);
double mach_vi(double x, int i);

void reduc(double sum, double *final_sum, int rank, int size, MPI_Status* status, int tag);
int main(int argc, char **argv)
{
		
	int rank, size, tag, i;
	MPI_Status status;
	
	
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	// Deklaration of all Loop-variables
	int n = 2;
	int p = 3;
	double abs_error = 0;
	double v[(int) pow(2,p)]; //initialize for biggest size, in earlier turns, use just a part. 
	double Sn = 0;
	double sum = 0;
	double time_start, duration;
	

	tag = 100; //Nutzen?

	// Open File. 
	FILE *f = fopen("verification_mach_mp.txt", "w");
	for(int k = 1; k<p; k++)
	{
		if(rank == 0)
		{	
			time_start = MPI_Wtime();
			mach_part(&v[0],n); // writes in just the first n cells	
			
			for(int i =1; i<size; i++)
			{	
				//Sending Vector to target worker.
				MPI_Send(&v[0],n,MPI_DOUBLE,i,tag,MPI_COMM_WORLD);
			}
								
			//Reducing the sum.
			reduc(sum, &Sn, rank, size, &status, tag);
			
			abs_error = Sn - M_PI;
			if(abs_error < 0) //manually computing the absolute value
			{
				abs_error = -abs_error; 
			}
			duration = MPI_Wtime() -time_start;
			printf("Sn: %e   | Error: %e	| Duration: %f\n",Sn,abs_error,duration);
			fprintf(f,"%.20f	%f\n",abs_error,duration);		
		}
		else
		{
			//Recieving Vector from root
			MPI_Recv(v,n,MPI_DOUBLE,0,tag,MPI_COMM_WORLD, &status);
			//printf("%i\n",n);
			for(int i = rank-1; i<n;i+=(size-1))
			{
				sum = sum + v[i];
				//printf("(%i|%u) ",rank,i);
			}
			//Reducing the sum.
			reduc(sum, &Sn, rank, size, &status, tag);
			sum = 0; // resetting
		}
		n = 2*n;
	}
	
	fclose(f);
	MPI_Finalize();

	return 0;		
}

void mach_part(double *v,int n)
{	
	
	double sum1,sum2 = 0;
	for(int i = 1; i<=n;i++)
	{	
		v[i-1] = 16*mach_vi((double) 1/5, i) -4*mach_vi((double) 1/239,i);
	}
	
}

double mach_vi(double x, int i)
{	
	double vi = pow(x,2*i-1)/((double)(2*i-1)); 
	if(i%2 ==0)
	{
		vi = -vi;
	}
	return vi;
}


void reduc(double sum, double *final_sum, int rank, int size, MPI_Status* status, int tag)
{	
	*final_sum = 0;
	if(rank == 0)
	{
		for(int i = 1; i< size; i++)
		{
			MPI_Recv(&sum, 1,MPI_DOUBLE,i,tag, MPI_COMM_WORLD, status); 
			*final_sum += sum;
		}
		for(int i = 1; i< size; i++)
		{
			MPI_Send(&sum,1,MPI_DOUBLE,i,tag,MPI_COMM_WORLD);
		}
	}
	else
	{
		MPI_Send(&sum,1,MPI_DOUBLE,0,tag,MPI_COMM_WORLD);
		MPI_Recv(&sum,1,MPI_DOUBLE,0,tag, MPI_COMM_WORLD, status); 
	}
}

