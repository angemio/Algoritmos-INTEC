#include <iostream>
#include <string>
#include <queue>
using namespace std;

// Mostrar tablero
void mostrarTablero(char tablero[]) 
{
    cout << "\nTablero:\n";
    for (int i = 0; i < 9; i++) {
        cout << " " << tablero[i] << " ";
        
        if (i % 3 != 2) cout << "|";
        if (i % 3 == 2 && i != 8) cout << "\n---------\n";
    }
    cout << "\n";
}

// Verificar si un jugador ganó
bool verificarGanador(char tablero[], char ficha) 
{
    // Filas
    for (int i = 0; i < 9; i += 3)
        if (tablero[i] == ficha && tablero[i+1] == ficha && tablero[i+2] == ficha)
            return true;

    // Columnas
    for (int i = 0; i < 3; i++)
        if (tablero[i] == ficha && tablero[i+3] == ficha && tablero[i+6] == ficha)
            return true;

    // Diagonales
    if (tablero[0] == ficha && tablero[4] == ficha && tablero[8] == ficha) return true;
    if (tablero[2] == ficha && tablero[4] == ficha && tablero[6] == ficha) return true;

    return false;
}

int main() {

    char tablero[9] = {'.','.','.','.','.','.','.','.','.'};

    string jugador1, jugador2;

    cout << "Nombre del jugador 1 (X): ";
    getline(cin, jugador1);

    cout << "Nombre del jugador 2 (O): ";
    getline(cin, jugador2);

    queue<int> jugadasX; // cola para el historial de las 'X'
    queue<int> jugadasO; // cola para el historial de las 'O'
    int turno = 0;

    while (true) 
    {
        mostrarTablero(tablero);

        string jugadorActual = (turno % 2 == 0) ? jugador1 : jugador2;
        char ficha = (turno % 2 == 0) ? 'X' : 'O';

        cout << "\nTurno de: " << jugadorActual << " (" << ficha << ")\n";
        cout << "Seleccione una celda (0-8): ";

        int celda;
        cin >> celda;


        if (cin.fail() || celda < 0 || celda > 8) 
        {
            cin.clear();
            cin.ignore(9999, '\n');
            
            cout << "Por favor elegir una celda entre 0 y 8.\n";
            continue;
        }

        if (tablero[celda] != '.') 
        {
            cout << "Por favor elegir una celda no ocupada.\n";
            continue;
        }

        // LOGICA DE BORRADO

        if(ficha == 'X'){
            // si la cola de X esta llena
            if(jugadasX.size() == 3){
                int celdaAntigua = jugadasX.front(); // ver la jugada mas vieja y asignarla
                jugadasX.pop();                      // se quita la jugada de la cola
                tablero[celdaAntigua] = '.';         // se borra del tablero

            }
        } 
        else {
            // si la cola de O esta llena
            if(jugadasO.size() == 3){
                int celdaAntigua = jugadasO.front(); // ver la jugada mas vieja y asignarla
                jugadasO.pop();                      // se quita la jugada de la cola
                tablero[celdaAntigua] = '.';         // se borra del tablero
            }
        }

        tablero[celda] = ficha;

        // LOGICA DE REGISTRO 
        if(ficha == 'X'){
            jugadasX.push(celda); // se añade la nueva jugada de X
        }
        else{
            jugadasO.push(celda); // // se añade la nueva jugada de O
        }

        if (verificarGanador(tablero, ficha)) 
        {
            mostrarTablero(tablero);
            cout << "\nGanador: " << jugadorActual << "\n";
            break;
        }

        turno++;

    }

   return 0;
}