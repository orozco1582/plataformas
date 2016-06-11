#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <mpi.h>

#define MAXRECT 1000000
#define MAXTHREAD 10
#define BASE 0.0
#define LIMIT 1.0

double length = LIMIT - BASE;
double numRectxThread = (double)(MAXRECT/MAXTHREAD);
double base_length = 0;
double sumTotal = 0;
double partialSums[MAXTHREAD];

double function(double x) {
        return x * x;
}

double calcular(double lowlimit, int rank) {

        int i;
        double sum = 0;
        for (i = 0; i < numRectxThread; i++) {
                sum += function(lowlimit + i*base_length) * base_length;
        }

        printf("Subtotal %lf en nodo %d\n", sum, rank);
        
        return sum;
}

int main(int argc, char** argv) {

        base_length = length/MAXRECT;
	
	int size, rank;

        MPI_Init(&argc,&argv);
        MPI_Comm_size(MPI_COMM_WORLD, &size);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);

        double b[1];
        int scounts[size];
        int disp[size];
        double vectorlowlimit[size];
    
        int a;

        for(a = 0; a < size; a++){
            vectorlowlimit[a] = a*base_length*numRectxThread;
            scounts[a] = 1;
            disp[a] = a*1;
        }

        MPI_Scatterv(vectorlowlimit, scounts, disp, MPI_DOUBLE, b, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

        double sum = 0;
        double lowlimit = b[0];	    

	sum = calcular(lowlimit, rank);

        MPI_Reduce(&sum,b,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);

        if (rank == 0)
            printf("Total: %lf\n", b[0]);

        MPI_Finalize();

        return 0;
}
