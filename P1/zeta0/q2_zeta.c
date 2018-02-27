
#include <stdio.h>
#include <math.h>

// Serial implementation of computing pi using the zeta function
double pi_zeta_serial(int n);
int unit_test_zeta(void);

int main(void)
{
	printf("This programm compares the expected value of pi against the value via pi_zeta_serial computed.\n n = 3 \n");
	
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

int unit_test_zeta(void)
{	// returns 1 if evaluation is succesfull, otherwise 0.
	double computed = pi_zeta_serial(3);
	int evaluation = 0;
	if(computed - 2.8577380332 < 0.0000001) // 7 digits accuracy
	{
		evaluation = 1;
	}
	return evaluation;
}
