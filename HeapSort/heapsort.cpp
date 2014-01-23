#include <stdlib.h>
#include <ctime>
#include <iostream>
using namespace std;

#define N 50000
double tiempo_inicio;
double tiempo_termino;

void siftDown(int numbers[], int root, int bottom)
{
	int done, maxChild, temp;
	done = 0;
	while ((root*2 <= bottom) && (!done))
	{
		if (root*2 == bottom)
			maxChild = root * 2;
		else if (numbers[root * 2] > numbers[root * 2 + 1])
			maxChild = root * 2;
		else
			maxChild = root * 2 + 1;
		if (numbers[root] < numbers[maxChild])
		{
			temp = numbers[root];
			numbers[root] = numbers[maxChild];
			numbers[maxChild] = temp;
			root = maxChild;
		}
		else
			done = 1;
	}
}
void heapSort (int numbers[], int array_size)
{
    int i, temp;
	for (i = (array_size / 2)-1; i >= 0; i--)
		siftDown(numbers, i, array_size);
	for (i = array_size-1; i >= 1; i--)
	{
		temp = numbers[0];
		numbers[0] = numbers[i];
		numbers[i] = temp;
		siftDown(numbers, 0, i-1);
	}
}

void Imprimir(int *array,int length) //print array elements
{
    int i=0;
    for(i=0;i<length;i++)
        cout<<array[i]<<endl;
}
int main(int argc, char **argv)
{
    int vector[N],i;
    cout << "llenando vector (" <<N<< " datos)..."<<endl;
    for(i=0;i<N;i++){  //rellena el vector en el orden contrario
        vector[i] = N - i;
    }

    cout << "Ejecutando heapsort secuencial..."<<endl;
    tiempo_inicio = clock();
    heapSort(vector,N);
    tiempo_termino = clock();
    //Imprimir(vector,N);
    cout << "Tiempo de ejecucion=" << (tiempo_termino - tiempo_inicio)/CLOCKS_PER_SEC<<" segundos"<<endl;
    return 0;
}
