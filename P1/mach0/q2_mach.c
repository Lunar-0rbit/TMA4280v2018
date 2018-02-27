
#include <stdio.h>
#include <math.h>

// Serial implementation of computing pi using the zeta function
double pi_mach_serial(int n);

int unit_test_zeta(void);

int main(void)
{
	printf("This programm compares the expected value of pi against the value via pi_mach_serial computed.\n n = 3 \n");
	
	int eval = unit_test_zeta();
	if(eval == 0)
	{
			printf("Evaluation not successfull!\n");
	}
	else
	{
			printf("Evaluation successfull!\n");
	}
	
	
	
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

int unit_test_zeta(void)
{	// returns 1 if evaluation is succesfull, otherwise 0.
	double computed = pi_mach_serial(3);
	printf("%.8f\n",computed);
	int evaluation = 0;
	if(computed - 3.14162103 < 0.0000001) // 7 digits accuracy
	{
		evaluation = 1;
	}
	return evaluation;
}
