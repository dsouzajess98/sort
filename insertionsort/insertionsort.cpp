#include <stdlib.h>
#include <ctime>
#include <iostream>
using namespace std;

#define N 50000
double tiempo_inicio;
double tiempo_termino;

void insertionSort (int numbers[], int array_size)
{
    int i, j, index;
    for (i=1; i < array_size; i++){
	index = numbers[i];
	j = i;
	while ((j > 0) && (numbers[j-1] > index)){
		numbers[j] = numbers[j-1];
		j = j - 1;
	}
	numbers[j] = index;
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

    cout << "Ejecutando insertionsort secuencial..."<<endl;
    tiempo_inicio = clock();
    insertionSort(vector,N);
    tiempo_termino = clock();
    //Imprimir(vector,N);
    cout << "Tiempo de ejecucion=" << (tiempo_termino - tiempo_inicio)/CLOCKS_PER_SEC<<" segundos"<<endl;
    return 0;
}
