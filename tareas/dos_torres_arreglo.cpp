// Reina vs Torres.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
/*
Realizar un programa C++ que genere los movimientos posibles (según las reglas del ajedrez) de
una Reina amenazada por dos Torres enemigas. El programa debe desplegar el tablero con las
jugadas posibles de la Reina, colocando una V donde la reina pueda moverse sin ser eliminada y
una X donde pueda moverse, pero ser eliminada por una o las dos torres enemigas.
RESTRICCIONES:
A. El programa debe solicitar al usuario las posiciones de las dos torres enemigas y la de la
reina.
B. Las posiciones de las torres no deben solaparse, es decir, no deben estar en la misma
posición. Las Torres deben estar en casillas distintas.
C. La posición de la reina no debe coincidir con las de las torres.
D. Debe desplegar el cuadro del ajedrez indicando a la reina con una R, las torres como T y
las jugadas según se establece en el enunciado.
Ejemplo de la salida del programa si la reina se ubica en la fila 2 columna 2 y las torres enemigas
en las filas 4 y 7 y columnas 1 y 5 respectivamente.

Poner una validacion, donde si se pone una fila o colunma que no sea del 1-8, sea invalida.
  1 2 3 4 5 6 7 8

Grupo 5 ------------------:

Angel De La Rosa - 1123662
Oliver Santana - 1123346
Joaquin Ramirez - 1127772
Emill Brito - 1127139
Dorian Diaz - 1122826
Justin Jimenez - 1122941
10/10/25

*/

#include <iostream>
#include <cstdlib>   // system("cls"), system("pause")
#include <cmath>     // abs()
#include <limits>    // numeric_limits

using namespace std;

bool es_valida(int f, int c) {
    return (f >= 1 && f <= 8 && c >= 1 && c <= 8);
}

int main() {
    int torre1[2], torre2[2], reina[2];
    char tablero[8][8];

    // Pedir la primera torre (valida uno a uno)
    while (true) {
        system("cls");
        cout << "Ingrese la posicion de la primera torre (fila y columna entre 1 y 8): ";
        if (!(cin >> torre1[0] >> torre1[1])) {
            cout << "\nEntrada invalida. Debe ingresar numeros enteros.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("pause");
            continue;
        }
        if (!es_valida(torre1[0], torre1[1])) {
            cout << "\n Error: la fila y columna deben estar entre 1 y 8.\n";
            system("pause");
            continue;
        }
        break;
    }

    // Pedir la segunda torre (valida contra rango y contra torre1)
    while (true) {
        system("cls");
        cout << "Primera torre: (" << torre1[0] << ", " << torre1[1] << ")\n\n";
        cout << "Ingrese la posicion de la segunda torre (fila y columna entre 1 y 8): ";
        if (!(cin >> torre2[0] >> torre2[1])) {
            cout << "\nEntrada invalida. Debe ingresar numeros enteros.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("pause");
            continue;
        }
        if (!es_valida(torre2[0], torre2[1])) {
            cout << "\n Error: la fila y columna deben estar entre 1 y 8.\n";
            system("pause");
            continue;
        }
        if (torre2[0] == torre1[0] && torre2[1] == torre1[1]) {
            cout << "\n Error: La segunda torre no puede coincidir con la primera torre.\n";
            system("pause");
            continue;
        }
        break;
    }

    // Pedir la reina (valida contra rango y ambas torres)
    while (true) {
        system("cls");
        cout << "Primera torre: (" << torre1[0] << ", " << torre1[1] << ")\n";
        cout << "Segunda torre: (" << torre2[0] << ", " << torre2[1] << ")\n\n";
        cout << "Ingrese la posicion de la reina (fila y columna entre 1 y 8): ";
        if (!(cin >> reina[0] >> reina[1])) {
            cout << "\nEntrada invalida. Debe ingresar numeros enteros.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("pause");
            continue;
        }
        if (!es_valida(reina[0], reina[1])) {
            cout << "\n Error: la fila y columna deben estar entre 1 y 8.\n";
            system("pause");
            continue;
        }
        if ((reina[0] == torre1[0] && reina[1] == torre1[1]) ||
            (reina[0] == torre2[0] && reina[1] == torre2[1])) {
            cout << "\n Error: La reina no puede coincidir con ninguna torre.\n";
            system("pause");
            continue;
        }
        break;
    }

    // Inicializar el tablero con espacios vacíos
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            tablero[i][j] = ' ';

    // Colocar las torres y la reina en el tablero
    tablero[torre1[0] - 1][torre1[1] - 1] = 'T';
    tablero[torre2[0] - 1][torre2[1] - 1] = 'T';
    tablero[reina[0] - 1][reina[1] - 1] = 'R';

    // Marcar los movimientos posibles de la reina
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            // Si está en la misma fila, columna o diagonal de la reina
            if (i == reina[0] - 1 || j == reina[1] - 1 ||
                abs(i - (reina[0] - 1)) == abs(j - (reina[1] - 1))) {

                // No sobrescribir la Reina ni las Torres
                if (tablero[i][j] == ' ') {
                    bool amenazada = false;

                    // Verificar si la casilla está amenazada por alguna torre
                    if (i == torre1[0] - 1 || j == torre1[1] - 1)
                        amenazada = true;
                    if (i == torre2[0] - 1 || j == torre2[1] - 1)
                        amenazada = true;

                    tablero[i][j] = amenazada ? 'X' : 'V';
                }
            }
        }
    }

    // Mostrar el tablero final
    system("cls");
    cout << "   TABLERO DE AJEDREZ\n\n";
    cout << "   1 2 3 4 5 6 7 8\n";
    for (int i = 0; i < 8; i++) {
        cout << i + 1 << "  ";
        for (int j = 0; j < 8; j++) {
            cout << tablero[i][j] << " ";
        }
        cout << "\n";
    }

    cout << "\nLeyenda:\nR = Reina\nT = Torre enemiga\nV = Movimiento seguro\nX = Movimiento amenazado\n";

    return 0;
}