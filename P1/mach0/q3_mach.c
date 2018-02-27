#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define M_PI 3.14159265358979323846
// Serial implementation of computing pi using the zeta function
double pi_mach_serial(int n);
void verification_test_mach(void);

int main(void)
{
	printf("This programm executes a varification test on pi_mach_serial \n");
	
	verification_test_mach();
	
	
	
	
return 0;	
}

double pi_mach_serial(int n)
{
	double Sn1 = 0;
	double Sn2 = 0;
	for(int i = 1; i<=n;i++)
	{	
		if(i%2 == 0)
		{
			Sn1 = Sn1 -(pow(0.2, (double) 2*i-1))/((double) 2*i-1); //x = 1/5
			Sn2 = Sn2 -(pow((double) 1/239, (double) 2*i-1))/((double) 2*i-1); //x = 1/239
		}
		else
		{
			Sn1 = Sn1 +(pow(0.2, (double) 2*i-1))/((double) 2*i-1); //x = 1/5
			Sn2 = Sn2 +(pow((double) 1/239, (double) 2*i-1))/((double) 2*i-1); //x = 1/239
		}
	}
	Sn1 = 4*(4*Sn1 -Sn2);
	return Sn1;	
}

void verification_test_mach(void)
{	
	double Sn = 0; 
	double abs_error = 0;
	
	FILE *f = fopen("verification_mach.txt", "w");
	if (f == NULL)
	{
		printf("Error opening file!\n");
		exit(1);
	}
	fprintf(f,"Absolute approximation error for the mach approach\n");
	for(int k = 1; k<=24;k++)
	{	
		abs_error = pi_mach_serial((int) pow(2,(double) k))-M_PI;
		if(abs_error < 0) //manually computing the absolute value
		{
			abs_error = -abs_error; 
		}
		//printf(" %.20f | %.20f | %.20f \n  ",pi_mach_serial(pow(2,(double) k)),M_PI, abs_error);
		fprintf(f,"n = 2^%i. Error:%.20f\n",k,abs_error);
	}
	fclose(f);
}
