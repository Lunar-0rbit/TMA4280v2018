
#include <stdio.h>
#include <math.h>

// Serial implementation of computing pi using the mach formula
double pi_mach_serial(int n);
int main(void)
{
	printf("This programm computes pi using the mach function with n steps \n");
	printf("Please enter n: ");
	int n = 0;
	scanf("%d", &n);
	printf("\n");
	printf("The result is: %f\n", pi_mach_serial(n));
	
	
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
