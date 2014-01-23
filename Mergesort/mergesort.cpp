#include <stdlib.h>
#include <ctime>
#include <iostream>
using namespace std;

#define N 50000
double tiempo_inicio;
double tiempo_termino;

void merge(int numbers[], int temp[], int left, int mid, int right)
{
	int i, left_end, num_elements, tmp_pos;
	left_end = mid - 1;
	tmp_pos = left;
	num_elements = right - left + 1;
	while ((left <= left_end) && (mid <= right))
	{
		if (numbers[left] <= numbers[mid])
		{
			temp[tmp_pos] = numbers[left];
			tmp_pos = tmp_pos + 1;
			left = left +1;
		}
		else
		{
			temp[tmp_pos] = numbers[mid];
			tmp_pos = tmp_pos + 1;
			mid = mid + 1;
		}
	}
	while (left <= left_end)
	{
		temp[tmp_pos] = numbers[left];
		left = left + 1;
		tmp_pos = tmp_pos + 1;
	}
	while (mid <= right)
	{
		temp[tmp_pos] = numbers[mid];
		mid = mid + 1;
		tmp_pos = tmp_pos + 1;
	}

	for (i=0; i <= num_elements; i++)
	{
		numbers[right] = temp[right];
		right = right - 1;
	}
}

void m_sort(int numbers[], int temp[], int left, int right)
{
	int mid;
	if (right > left)
	{
		mid = (right + left) / 2;
		m_sort(numbers, temp, left, mid);
		m_sort(numbers, temp, mid+1, right);
		merge(numbers, temp, left, mid+1, right);
	}
}

void mergeSort(int numbers[], int temp[], int array_size)
{
	m_sort(numbers, temp, 0, array_size - 1);
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
    int temp[N];
    cout << "llenando vector (" <<N<< " datos)..."<<endl;
    for(i=0;i<N;i++){  //rellena el vector en el orden contrario
        vector[i] = N - i;
    }

    cout << "Ejecutando mergesort secuencial..."<<endl;
    tiempo_inicio = clock();
    mergeSort(vector,temp,N);
    tiempo_termino = clock();
    //Imprimir(vector,N);
    cout << "Tiempo de ejecucion=" << (tiempo_termino - tiempo_inicio)/CLOCKS_PER_SEC<<" segundos"<<endl;
    return 0;
}
