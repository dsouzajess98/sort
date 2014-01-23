#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

#define N 20000
double tiempo_inicio;
double tiempo_termino;

void Imprimir(int *array,int length) //print array elements
{
    int i=0;
    for(i=0;i<length;i++)
        printf("%d\n",array[i]);
}

/*function to merge vectors*/
int * merge(int *A, int asize, int *B, int bsize) {
    int ai, bi, ci, i;
    int *C;
    int csize = asize+bsize;

    ai = 0;
    bi = 0;
    ci = 0;

    C = (int *)malloc(csize*sizeof(int));
    while ((ai < asize) && (bi < bsize)) {
        if (A[ai] <= B[bi]) {
            C[ci] = A[ai];
            ci++; ai++;
        } else {
            C[ci] = B[bi];
            ci++; bi++;
        }
    }

    if (ai >= asize)
        for (i = ci; i < csize; i++, bi++)
            C[i] = B[bi];
    else if (bi >= bsize)
        for (i = ci; i < csize; i++, ai++)
            C[i] = A[ai];

    for (i = 0; i < asize; i++)
        A[i] = C[i];
    for (i = 0; i < bsize; i++)
        B[i] = C[asize+i];

    return C;
}

void swap(int *v, int i, int j)
{
    int t;
    t = v[i];
    v[i] = v[j];
    v[j] = t;
}

void m_sort(int *A, int min, int max)
{
    int *C;     /* dummy, just to fit the function */
    int mid = (min+max)/2;
    int lowerCount = mid - min + 1;
    int upperCount = max - mid;

    /* If the range consists of a single element, it's already sorted */
    if (max == min) {
        return;
    } else {
        /* Otherwise, sort the first half */
        m_sort(A, min, mid);
        /* Now sort the second half */
        m_sort(A, mid+1, max);
        /* Now merge the two halves */
        C = merge(A + min, lowerCount, A + mid + 1, upperCount);
    }
}

main(int argc, char **argv)
{
    int * data;
    int * chunk;
    int * other;
    int m,n=N;
    int id,p;
    int s = 0;
    int i;
    int step;
    MPI_Status status;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&id);
    MPI_Comm_size(MPI_COMM_WORLD,&p);


/**************************** master task ************************************/
    if(id == 0)
    {
        int r;
		s = n/p;
		r = n%p;
		data = (int *)malloc((n+p-r)*sizeof(int));
		printf("llenando vector (%d datos)...\n",N);
		for(i=0;i<n;i++)
			data[i] = N - i;
		if(r!=0)
		{
			for(i=n;i<n+p-r;i++)
  			   data[i]=0;
			s=s+1;
		}
		printf("Ejecutando mergesort paralelo...\n");
		tiempo_inicio = clock();

        MPI_Bcast(&s,1,MPI_INT,0,MPI_COMM_WORLD);
        chunk = (int *)malloc(s*sizeof(int));
        MPI_Scatter(data,s,MPI_INT,chunk,s,MPI_INT,0,MPI_COMM_WORLD);
        m_sort(chunk, 0, s-1);
    }

/**************************** worker task ************************************/
    else
    {
        MPI_Bcast(&s,1,MPI_INT,0,MPI_COMM_WORLD);
        chunk = (int *)malloc(s*sizeof(int));
        MPI_Scatter(data,s,MPI_INT,chunk,s,MPI_INT,0,MPI_COMM_WORLD);
        m_sort(chunk, 0, s-1);
    }

    step = 1;
    while(step<p)
    {
        if(id%(2*step)==0)
        {
            if(id+step<p)
            {
                MPI_Recv(&m,1,MPI_INT,id+step,0,MPI_COMM_WORLD,&status);
                other = (int *)malloc(m*sizeof(int));
                MPI_Recv(other,m,MPI_INT,id+step,0,MPI_COMM_WORLD,&status);
                chunk = merge(chunk,s,other,m);
                s = s+m;
            }
        }
        else
        {
            int near = id-step;
            MPI_Send(&s,1,MPI_INT,near,0,MPI_COMM_WORLD);
            MPI_Send(chunk,s,MPI_INT,near,0,MPI_COMM_WORLD);
            break;
        }
        step = step*2;
    }
    if(id==0)
    {
        tiempo_termino = clock();
		printf("Tiempo de ejecucion = %f segundos\n",(tiempo_termino-tiempo_inicio)/CLOCKS_PER_SEC);
		//Imprimir(chunk,N);
    }
    MPI_Finalize();
}
