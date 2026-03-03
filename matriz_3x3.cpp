/*
 * Algoritmo: Cuadrado Mágico 3x3
 * Enfoque: Backtracking
 * Descripción: Encuentra todas las combinaciones posibles de números del 1 al 9
 * en una matriz 3x3 tal que la suma de sus filas, columnas y diagonales sea exactamente 15.
 * Complejidad de Tiempo: O(9!) en el peor de los casos (fuerza bruta), pero optimizado 
 * drásticamente mediante poda (pruning) con la función checkParcial.
 */

#include <iostream>
#include <vector>
using namespace std;

// Variables globales para el estado del tablero
int objetivo = 15; // Suma clásica de un cuadrado mágico 3x3
int solCount = 0;
bool usado[10];
int M[3][3];

// Verifica si la matriz sigue siendo válida tras insertar un número
bool checkParcial(int r, int c){
    int suma;

    // Validar fila completa
    if(c == 2){
        suma = M[r][0] + M[r][1] + M[r][2];
        if(suma != objetivo) return false;
    }

    // Validar columna completa
    if(r == 2){
        suma = M[0][c] + M[1][c] + M[2][c];
        if(suma != objetivo) return false;
    }

    // Validar diagonales cuando se llega a la última celda (pos 2,2)
    if(r == 2 && c == 2){
        // Diagonal principal
        suma = M[0][0] + M[1][1] + M[2][2];
        if(suma != objetivo) return false;

        // Diagonal secundaria
        suma = M[0][2] + M[1][1] + M[2][0];
        if(suma != objetivo) return false;
    }

    return true;
}

// Función recursiva de Backtracking
void backtrack(int pos){
    // Caso base: Se llenaron las 9 posiciones exitosamente
    if(pos == 9){
        solCount++;
        cout << "\nSolucion #" << solCount << ":\n";
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++)
                cout << M[i][j] << " ";
            cout << "\n";
        }
        return;
    }

    // Calcular coordenadas actuales basadas en la posición lineal
    int r = pos / 3;
    int c = pos % 3;

    // Probar números del 1 al 9
    for(int n = 1; n <= 9; n++){
        if(!usado[n]){
            M[r][c] = n;       // Hacer el movimiento
            usado[n] = true;

            // Solo avanzar si el movimiento actual es válido
            if(checkParcial(r, c))
                backtrack(pos + 1);

            usado[n] = false;  // Deshacer el movimiento (Backtrack)
        }
    }
}

int main(){
    // Inicializar el arreglo de numeros usados
    for(int i = 1; i <= 9; i++) usado[i] = false;

    // Iniciar la busqueda desde la posición 0
    backtrack(0);

    if(solCount == 0)
        cout << "No se encontraron combinaciones.\n";

    return 0;
}