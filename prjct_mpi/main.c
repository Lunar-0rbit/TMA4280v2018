#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<mpi.h>
#include<time.h>			
										
#include"comp_pi.h"
#include"pi_serial.h"
#include"verification.h"

int main(int argc, char **argv){
	     
	     
	int rank, size, tag, i;
	double glob_sum_m=0; 											//Does this need to be global? YES
	
	
	int reps =0;											//Does this need to be global? YES
	double sum_r=0;
	MPI_Status status;
		
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	tag = 100;
		
	int length=100;
	double* results;
	
	FILE *f = fopen("results.txt", "w");
	
	for(int problem_size=0;problem_size<20;problem_size++)
	{
		MPI_Barrier(MPI_COMM_WORLD);
		double riemann_pi=0;
		double machine_pi=0;
		
		double init_time=0;
		double distrib_time=0;
		double calc_time=0;
		double finalize_time=0;
		
		
		//printf("%d\n",100/ipow(2,problem_size));
		for(reps=0;reps<10;reps++)
		{
			results = compute_pi_and_time(size, rank, ipow(2,problem_size), tag);
		
			if(rank==0)
			{
			init_time+=results[0];
			distrib_time+=results[1];
			calc_time+=results[2];
			finalize_time+=results[3];
			}	
		}
		
		if(rank==0)
		{
			riemann_pi=results[4];
			machine_pi=results[5];
			init_time=init_time/(double)reps;
			distrib_time=distrib_time/(double)reps;
			calc_time=calc_time/(double)reps;
			finalize_time=finalize_time/(double)reps;
			
			fprintf(f,"%5.6lf;%5.6lf;%5.6lf;%5.6lf;%5.6lf;",init_time,distrib_time,calc_time,finalize_time);
			fprintf(f,"%1.60lf;",riemann_pi);
			fprintf(f,"%1.60lf\n", machine_pi);
		}		
	
}	
		if(rank==0)
{
	
	free(results);

}	
	fclose(f);              
	MPI_Finalize ();
	//qualiy of the code?
	//graphs just in the report?
	/*error study parallel; timing parallel*/
	//err = MPI_.....
	//execption handling?
	//mpi subroutines
	//load balance
	//how intelligent?
	return 0;
}

