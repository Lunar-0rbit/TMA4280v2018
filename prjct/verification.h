double test_riemann_pi(int n,double comp_value)
{
	double test_pi=pi_serial_riemann(n);
	
	return test_pi-comp_value;
	
}

double test_machin_pi(int n, double comp_value)
{
	
	double test_pi=pi_serial_machin(n);
	
	return test_pi-comp_value;
	

}


double* verifiy_pi_riemann(int order_of_mg)
{
	double* err_v;
	err_v=malloc(order_of_mg*sizeof(double));
	
	for(int i=0;i<order_of_mg;i++)
	{
		err_v[i]=abs(M_PI-pi_serial_machin(2^i));
	}
	
	return err_v;
	
}

double* verify_pi_machin(int order_of_mg)
{
	double* err_v;
	err_v=malloc(order_of_mg*sizeof(double));
	
	for(int i=0;i<order_of_mg;i++)
	{
		err_v[i]=abs(M_PI-pi_serial_machin(2^i));
	}
	
	return err_v;
	
	
}
