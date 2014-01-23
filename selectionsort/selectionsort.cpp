#include <stdlib.h>
#include <ctime>
#include <iostream>
using namespace std;

#define N 50000
double tiempo_inicio;
double tiempo_termino;

void selectionSort (int numbers[], int array_size)
{
    int i, j;
    int min, temp;
    for (i = 0; i < array_size-1; i++){
	min = i;
	for (j = i+1; j < array_size; j++){
		if (numbers[j] < numbers[min])
			min = j;
        }
	temp = numbers[i];
	numbers[i] = numbers[min];
	numbers[min] = temp;
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

    cout << "Ejecutando selectionsort secuencial..."<<endl;
    tiempo_inicio = clock();
    selectionSort(vector,N);
    tiempo_termino = clock();
    //Imprimir(vector,N);
    cout << "Tiempo de ejecucion=" << (tiempo_termino - tiempo_inicio)/CLOCKS_PER_SEC<<" segundos"<<endl;
    return 0;
}
