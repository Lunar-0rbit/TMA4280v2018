double pi_serial_riemann(int n)
{
	double serial_pi=0;;
	
	int* base_array;
	
	base_array=malloc(n*sizeof(int));
	
	
	for(int i=0;i<n;i++)
	{
		base_array[i]=i+1;
	}
	serial_pi=riemann_zeta_sum(base_array,n);
	
	free(base_array);
	
	return serial_pi;
	
}

double pi_serial_machin(int n)
{
	double serial_pi=0;
	
	int* base_array;
	
	base_array=malloc(n*sizeof(int));

	
	for(int i=0;i<n;i++)
	{
		base_array[i]=i+1;
	}
	serial_pi=4*(4*machin_formula(base_array,n,0.2)-machin_formula(base_array,n,1/(double)239));
	
	free(base_array);
	
	return serial_pi;
}
