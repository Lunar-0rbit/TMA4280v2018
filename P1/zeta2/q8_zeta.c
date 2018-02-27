#include <omp.h>
#include <stdio.h>
#include <math.h>


#define M_PI 3.14159265358979323846


void zeta_part(double *v,int n);

int main(void)
{
	int p = 4; // 2^k computations
	int n = 2;
	double Sn = 0;
	double v[(int) pow(2,p)]; //initialize for biggest size, in earlier turns, use just a part. 
	double time_start, duration, abs_error;
	int i;
	FILE *f = fopen("verification_zeta_omp.txt", "w");
	int tid;
	for(int k = 1;k<p;k++)
	{	
		time_start = omp_get_wtime();
		zeta_part(&v[0],n); // writes in just the first n cells

		#pragma omp parallel for schedule (static) reduction(+:Sn)
		for(i = 0; i<n; i++)
		{
			Sn = Sn + v[i];
			tid = omp_get_thread_num();
			printf("%i	\n", tid);
		}
		printf("\n");
		
		Sn = sqrt(Sn*6); //completing the computation of zeta
		abs_error = Sn - M_PI;
		if(abs_error < 0) //manually computing the absolute value
		{
			abs_error = -abs_error; 
		}
		duration = omp_get_wtime() -time_start;
		printf("Sn: %e   | Error: %e	| Duration: %f\n",Sn,abs_error,duration);
		fprintf(f,"%.20f	%f\n",abs_error,duration);
		n = 2*n;
		Sn = 0;
	}

	return 0;
}

void zeta_part(double *v,int n)
{
	double d_i;
	
	for(int i = 1; i<=n;i++)
	{
		d_i = (double) i;	
		v[i-1] = 1/(d_i*d_i);
	}	
}
