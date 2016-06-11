#include <mpi.h>
#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <sys/time.h>

#define MAX 100

/* retorna "a - b" en segundos */
double timeval_diff(struct timeval *a, struct timeval *b)
{
  return
    (double)(a->tv_sec + (double)a->tv_usec/1000000) -
    (double)(b->tv_sec + (double)b->tv_usec/1000000);
}

int main(int argc, char** argv) {
    	int rank, size, i;
    	int vector[MAX], *miparte, stride;
    	int data;
    	int dest;
    	int source;
    	int tag = 1;
    	int acum = 0;
    	int total = 0;
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
    	stride = MAX/(size - 1);
    	if (rank == 0) {
            	for (i = 1; i < size; i++)
                    	MPI_Send(&vector[stride*(i - 1)],stride,MPI_INT, i, tag, MPI_COMM_WORLD);
    	} else {
            	acum = 0;
            	miparte = (int*)malloc(sizeof(int)*stride);
            	MPI_Recv(miparte, stride, MPI_INT, 0, tag, MPI_COMM_WORLD, &stat);
            	for (i = 0, acum = 0; i < stride; i++)
                    	acum += miparte[i];
    	}
    	MPI_Reduce(&acum,&total,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
    	if (rank == 0)
            	printf("Total: %d\n", total);
    	MPI_Finalize();

	gettimeofday(&t_fin, NULL);

	secs = timeval_diff(&t_fin, &t_ini);
	printf("%.16g milliseconds\n", secs * 1000.0);
}
