#include<math.h>

int array_slice(void)
{
	return 0;
}

double riemann_zeta_sum(int* vector, int length)
{
	double sum=0;
	
	for(int i=0; i<length; i++)
	{
		sum+=1/((double)vector[i]*(double)vector[i]);
		
	}
		
	return sum;
}

double machin_formula(int* vector, int length, double value)
{
	double sum=0;
	double machin_v=0;
	
	for(int i=0; i<length; i++)
	{
		machin_v=pow(value,(double)(2*vector[i]-1));

		sum+=(2*((vector[i])%2)-1)*(machin_v)/(2*vector[i]-1);
	}
		
	
	return sum;
}


double* compute_pi_and_time(int size, int rank, int length, int tag)
{
	double* results;
	clock_t main_clock;
	main_clock = clock();
	
	double init_time=0;
	double distrib_time=0;
	double calc_time=0;
	double finalize_time=0;
	
	double gw_init_time=0;
	double gw_distrib_time=0;
	double gw_calc_time=0;
	double gw_finalize_time=0;
	
	int i=0;
	double glob_sum_m=0; 											//Does this need to be global? YES
	double sum_m=0;
	double glob_sum_r=0;
											//Does this need to be global? YES
	double sum_r=0;
	MPI_Status status;	
	
	
	results=malloc(6*sizeof(double));
	
	int distribution=0;
	int rest_distribution=0;
	tag++;														//Go-TO way for handling tags? 0 and ++ be locally consistent
	
	main_clock = clock() - main_clock;
	init_time=((double)main_clock)/CLOCKS_PER_SEC;
	
		
	if(rank == 0){
		//printf("why?\n");
		
		int* array;
	
		
		array=malloc(length*sizeof(int));
		
		for(i=0;i<length;i++)	{
		
		array[i]=i+1;
		
		}
		
				
		distribution=length/(size-1);
		//printf("information: %d\n",distribution);
		
		MPI_Request *sreq;
		sreq = malloc(size*sizeof(MPI_Request));
		
		for(i=1;i<size-1;i++){
		
			MPI_Send(&distribution,1,MPI_INT,i,102,MPI_COMM_WORLD); //Whats the SMOOTHEST MPI_Send here?
																	//Could we then run into issues? MPI SENDRECV?
			//MPI_Isend(&distribution,1,MPI_INT,i,103,MPI_COMM_WORLD,sreq + i);
			MPI_Send(&array[distribution*(i-1)],distribution ,MPI_INT,i,tag,MPI_COMM_WORLD); //GO-TO solution?
	
		}
		/*how many exceptions*/
		
		int rest_start_point=distribution*(size-2);
		distribution = length - ((size-2)*distribution);
		//MPI_Isend(&distribution,1,MPI_INT,i,103,MPI_COMM_WORLD,sreq + size-1);
		MPI_Send(&distribution,1,MPI_INT,size-1,102,MPI_COMM_WORLD);
		MPI_Send(&array[rest_start_point],distribution ,MPI_INT,size-1,tag,MPI_COMM_WORLD);
	
		//MPI_Waitall(size-1,sreq + 1,MPI_STATUS_IGNORE);
		
		main_clock = clock() - main_clock;
		distrib_time=((double)main_clock)/CLOCKS_PER_SEC;
	}
	else{
		
		int distribution=0;;
			
		MPI_Recv (&distribution,1,MPI_INT,0,102,MPI_COMM_WORLD, &status);
		//printf("%d i am number      %d\n",distribution,rank);
		//MPI_Request greq;
		//MPI_Irecv(&distribution,1,MPI_INT,0,103,MPI_COMM_WORLD, &greq);
		
		int* array;												//where and when to free?
		array=malloc(distribution*sizeof(int));
		
		
		//MPI_Wait(&greq,MPI_STATUS_IGNORE);
		MPI_Recv (array, distribution ,MPI_INT,0,tag,MPI_COMM_WORLD, &status);
		
		main_clock = clock() - main_clock;
		distrib_time=((double)main_clock)/CLOCKS_PER_SEC;
		//printf("received\n");
		sum_r=riemann_zeta_sum(array, distribution);
		sum_m=4*machin_formula(array,distribution,0.2)-machin_formula(array,distribution,1/(double)239);
		
		
		main_clock = clock() - main_clock;
		calc_time=((double)main_clock)/CLOCKS_PER_SEC;
		//printf("\n riemann_pi: %lf\n\n machine_pi: %lf\n\n",sum_r,sum_m);	
		
	}
	
	//MPI_Barrier(MPI_COMM_WORLD);	//redundend								//correct barrier?
	MPI_Reduce(&sum_r,&glob_sum_r,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
	MPI_Reduce(&sum_m,&glob_sum_m,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
	MPI_Reduce(&calc_time,&gw_calc_time,1,MPI_DOUBLE,MPI_MAX,0,MPI_COMM_WORLD);
	MPI_Reduce(&distrib_time,&gw_distrib_time,1,MPI_DOUBLE,MPI_MAX,0,MPI_COMM_WORLD);
	
	
	if(rank==0){
	
	double riemann_pi=sqrt(glob_sum_r*6);
	double machine_pi=4*glob_sum_m;
	//printf("\n riemann_pi: %lf\n\n machine_pi: %lf\n\n",riemann_pi,machine_pi);
	
	main_clock = clock() - main_clock;
	finalize_time=((double)main_clock)/CLOCKS_PER_SEC;
	
	//printf("\n\n Time taken:\n init: %lf\n distrib: %lf\n calc: %lf\n finalize: %lf\n",init_time,gw_distrib_time,gw_calc_time,finalize_time);

	results[0]=init_time;
	results[1]=gw_distrib_time;
	results[2]=gw_calc_time;
	results[3]=finalize_time;
	results[4]=riemann_pi;
	results[5]=machine_pi;
	

	return results;
}
else{
return NULL;
}
}

	
