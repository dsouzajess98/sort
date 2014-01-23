#include <stdlib.h>
#include <ctime>
#include <iostream>
using namespace std;

#define N 20000
double tiempo_inicio;
double tiempo_termino;

void bubbleSort (int numbers[], int array_size)
{
    int i, j, temp;
    for (i = (array_size - 1); i >= 0; i--){
        for (j = 1; j <= i; j++){
            if (numbers[j-1] > numbers[j]){
                temp = numbers[j-1];
                numbers[j-1] = numbers[j];
                numbers[j] = temp;
            }
        }
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

    cout << "Ejecutando bubblesort secuencial..."<<endl;
    tiempo_inicio = clock();
    bubbleSort(vector,N);
    tiempo_termino = clock();
    //Imprimir(vector,N);
    cout << "Tiempo de ejecucion=" << (tiempo_termino - tiempo_inicio)/CLOCKS_PER_SEC<<" segundos"<<endl;
    return 0;
}
