#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define M_PI 3.14159265358979323846
// Serial implementation of computing pi using the zeta function
double pi_zeta_serial(int n);
void verification_test_zeta(void);

int main(void)
{
	printf("This programm executes a varification test on pi_zeta_serial \n");
	
	verification_test_zeta();
	
	
	
	
return 0;	
}

double pi_zeta_serial(int n)
{
	double Sn = 0;
	for(int i = 1; i<=n;i++)
	{
		double d_i = (double) i;
		Sn = Sn + 1/(d_i*d_i);
	}
	Sn = sqrt(Sn*6);
	return Sn;	
}

void verification_test_zeta(void)
{	
	double Sn = 0; 
	double abs_error = 0;
	
	FILE *f = fopen("verification_zeta.txt", "w");
	if (f == NULL)
	{
		printf("Error opening file!\n");
		exit(1);
	}
	fprintf(f,"Absolute approximation error for the zeta approach\n");
	for(int k = 1; k<=24;k++)
	{
		abs_error = pi_zeta_serial((int) pow(2,(double) k))-M_PI;
		//printf("%f\n", pow(2,(double) k));
		if(abs_error < 0) //manually computing the absolute value
		{
			abs_error = -abs_error; 
		}
		//printf(" %.20f | %.20f | %.20f \n  ",pi_zeta_serial(pow(2,(double) k)),M_PI, abs_error);
		fprintf(f,"n = 2^%i. Error:%.20f\n",k,abs_error);
	}
	fclose(f);
}
