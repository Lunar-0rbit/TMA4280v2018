test:
	gcc -fopenmp -o q8_mach q8_mach.c -std=c99 -lm 
	OMP_NUM_THREADS=4 ./q8_mach
q9test:
	mpicc -fopenmp -o q9_mach q9_mach.c -std=c99 -lm 
	mpirun OMP_NUM_THREADS=2 -np 2 ./q9_mach #(! OMP_NUM_THREADS=4  muss weg)

