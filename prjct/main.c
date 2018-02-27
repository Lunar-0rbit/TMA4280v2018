#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<mpi.h>			
										
#include"array_part.h"
#include"pi_serial.h"
#include"verification.h"

int main(int argc, char **argv){
 
	int rank, size;
	MPI_Status status;
	
	
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	if(rank==0)
	{		
		double numbro_1=pi_serial_riemann(40);
		numbro_1=sqrt(numbro_1*6);
		double numbro_2=pi_serial_machin(40);
		printf("%e\n%e\n%e\n\n",M_PI,numbro_1,numbro_2);
		
			
		double err_1_r=test_riemann_pi(1,1);
		double err_2_r=test_riemann_pi(2,1+0.25);
		double err_3_r=test_riemann_pi(3,1+0.25+1/(double)9);
		printf("%e\n%e\n%e\n\n",err_1_r,err_2_r,err_3_r);
		
		double err_1_m=test_machin_pi(1,0);
		double err_2_m=test_machin_pi(2,0);
		double err_3_m=test_machin_pi(3,0);
		printf("%e\n%e\n%e\n\n",err_1_m,err_2_m,err_3_m);
		
		/*free the error*/
		
		double* err_riemann;
		double* err_machin;
		
		err_riemann = verifiy_pi_riemann(24);
		err_machin=verify_pi_machin(24);
		
		free(err_riemann);
		free(err_machin);
	}	

	MPI_Finalize();
	return 0;
}

