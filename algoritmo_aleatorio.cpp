/*
 * Algoritmo: Randomized QuickSort (Enfoque Las Vegas)
 * Estructura de Datos: Arreglo (Array)
 * Complejidad de Tiempo: Esperado O(n log n). Peor caso O(n^2) 
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Función para particionar el arreglo usando un pivote aleatorio
int partition(int arr[], int low, int high) {
    // Elegir pivote aleatorio (Enfoque Las Vegas) para evitar el peor caso
    int random = low + rand() % (high - low + 1);
    
    // Intercambiar el pivote aleatorio con el último elemento
    swap(arr[random], arr[high]);
    
    int pivot = arr[high];
    int i = low - 1; // Índice del elemento más pequeño
    
    // Recorrer el arreglo y mover los elementos menores al pivote a la izquierda
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    
    // Colocar el pivote en su posición correcta
    swap(arr[i + 1], arr[high]);
    return i + 1; // Retornar el índice de partición
}

// Función principal recursiva de QuickSort
void quicksort(int arr[], int low, int high) {
    if (low < high) {
        // pi es el índice de partición, arr[pi] ya está en su lugar correcto
        int pi = partition(arr, low, high);
        
        // Ordenar recursivamente los sub-arreglos antes y después de la partición
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

int main() {
    // Inicializar la semilla para la generación de números aleatorios
    srand(time(0));
    
    // Datos de prueba
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = 7;
    
    cout << "Arreglo original: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    
    // Llamada al algoritmo de ordenamiento
    quicksort(arr, 0, n - 1);
    
    cout << "\nArreglo ordenado: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
    
    return 0;
}