#include <mpi.h>
#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <sys/time.h>

#define MAX 100
#define SIZE 20

/* retorna "a - b" en segundos */
double timeval_diff(struct timeval *a, struct timeval *b)
{
  return
    (double)(a->tv_sec + (double)a->tv_usec/1000000) -
    (double)(b->tv_sec + (double)b->tv_usec/1000000);
}

int main(int argc, char** argv) {
    	int rank, size, i;
    	int vector[MAX];
    	int acum = 0;
    	MPI_Status stat;

    	for (i = 1; i <= 100; i++)
            	vector[ i - 1 ] = i;

	//variables para medir el tiempo de ejecución
	struct timeval t_ini, t_fin;
	double secs;

	gettimeofday(&t_ini, NULL);

    	MPI_Init(&argc,&argv);
    	MPI_Comm_size(MPI_COMM_WORLD, &size);
    	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int b[SIZE];
	int scounts[SIZE];
	int disp[SIZE];

	for (i = 0; i < size; i++) {
            	disp[i] = i*SIZE;
            	scounts[i] = SIZE;
    	}

	MPI_Scatterv(vector, scounts, disp, MPI_INT, b, SIZE, MPI_INT, 0, MPI_COMM_WORLD);
	
	for (i = 0; i < SIZE; i++)
            	acum += b[i];

    	printf("Subtotal %d en nodo %d\n", acum, rank);
	MPI_Reduce(&acum,b,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
    	if (rank == 0)
            	printf("Total: %d\n", b[0]);
    	MPI_Finalize();

	gettimeofday(&t_fin, NULL);

	secs = timeval_diff(&t_fin, &t_ini);
	printf("%.16g milliseconds\n", secs * 1000.0);
}
