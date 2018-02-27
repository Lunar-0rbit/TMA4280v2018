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

