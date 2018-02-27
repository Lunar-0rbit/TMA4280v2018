#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Serial implementation of computing pi using the zeta function
double pi_zeta_serial(int n);
int main(void)
{
	printf("This programm computes pi using the zeta function with n steps \n");
	printf("Please enter n: ");
	int n = 0;
	scanf("%d", &n);
	printf("\n");
	printf("The result is: %f\n", pi_zeta_serial(n));
	
	
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
