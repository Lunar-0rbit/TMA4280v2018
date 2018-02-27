all:
		
	mpicc -std=c99 -D_XOPEN_SOURCE=600 -D__EXTENSIONS__ -c main.c -g -O2
	mpicc -o exec main.o -lm
	mpirun -np 4 ./exec 
