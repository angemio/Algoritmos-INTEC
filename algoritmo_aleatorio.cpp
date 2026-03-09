#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Algoritmo aleatorio de Las Vegas - Quicksort aleatorio

int partition(int arr[], int low, int high) {
    // Randomly pick pivot (Las Vegas approach)
    int random = low + rand() % (high - low + 1);
    swap(arr[random], arr[high]);
    
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quicksort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

int main() {
    srand(time(0));
    
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = 7;
    
    cout << "Original array: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    
    quicksort(arr, 0, n - 1);
    
    cout << "\nSorted array: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
    
    return 0;
}