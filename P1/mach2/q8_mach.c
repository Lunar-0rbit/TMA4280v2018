#include <omp.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


#define M_PI 3.14159265358979323846

long int ipow(int base, int exp);
void mach_part(double*v,int n);
double mach_vi(double x, int i);


int main(void)
{
	int rounds = 27; // 2^k computations (rounds is a power of 2)
	int n = 0;
	double Sn = 0;
	double *v = (double*) malloc(ipow(2,rounds)*sizeof(double));
	double time_start,time_loop, duration,duration_loop, abs_error;
	int i;
	FILE *f = fopen("verification_zeta_omp.txt", "w");
	int tid;
	// test pragma, s.t workers are initialized
	#pragma omp parallel for schedule (static) reduction(+:Sn)
	for(int i = 0; i<n; i++)
	{
	}
	for(int k = 1;k<=rounds;k++)
	{	
		
		time_start = omp_get_wtime();
		n = ipow(2,k);
		mach_part(&v[0],n); // writes in just the first n cells
		
		time_loop = omp_get_wtime();
		//#pragma omp parallel for schedule (static) reduction(+:Sn)
		for(i = 0; i<n; i++)
		{
			Sn = Sn + v[i];
			//tid = omp_get_thread_num();
		}
		duration_loop = omp_get_wtime() -time_loop;
		abs_error = Sn - M_PI;
		if(abs_error < 0) //manually computing the absolute value
		{
			abs_error = -abs_error; 
		}
		duration = omp_get_wtime() -time_start;
		printf("Round: %i	| Sn: %e   | Error: %e	| Duration_all: %.15f |	 Duration_loop %.15f\n",k,Sn,abs_error,duration, duration_loop);
		fprintf(f,"%.20f	%f\n	%f\n",abs_error,duration,duration_loop);
		n = 2*n;
		Sn = 0;
	}
	free(v);
	return 0;
}

void mach_part(double *v,int n)
{	
	
	//double sum1,sum2 = 0;
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

long int ipow(int base, int exp)
{
    long int result = 1;
    while (exp)
    {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        base *= base;
    }

    return result;
}
