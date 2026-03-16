#include <iostream>
using namespace std;

// Función auxiliar para imprimir los espacios
void espacios(int n)
{
    if(n == 0) return;

    cout << " ";
    espacios(n - 1);
}

// Función auxiliar para imprimir los asteriscos
void asteriscos(int n)
{
    if(n == 0) return;

    cout << "*";
    asteriscos(n - 1);
}

// Función para imprimir el triángulo isósceles
void isoscelesArriba(int nivelActual, int nivelesTotales)
{
    if(nivelActual > nivelesTotales) return;

    espacios(nivelesTotales - nivelActual);
    asteriscos((2*nivelActual) - 1);
    cout << "\n";

    isoscelesArriba(nivelActual + 1, nivelesTotales);
}

// Función para imprimir el triángulo isósceles invertido
void isoscelesAbajo(int nivelActual, int nivelesTotales)
{
    if(nivelActual == 0) return;

    espacios(nivelesTotales - nivelActual);
    asteriscos((2*nivelActual) - 1);
    cout << "\n";

    isoscelesAbajo(nivelActual - 1, nivelesTotales);
}

// Función para imprimir el triángulo rectángulo alineado a la derecha
void rectangulo(int nivelActual, int nivelesTotales)
{
    if(nivelActual > nivelesTotales) return;

    espacios(nivelesTotales - nivelActual);
    asteriscos(nivelActual);
    cout << "\n";

    rectangulo(nivelActual + 1, nivelesTotales);
}

int main()
{
    int n;
    cout << "Ingrese la cantidad de niveles: ";
    cin >> n;

    cout << "\nTriangulo isosceles:\n";
    isoscelesArriba(1, n);

    cout << "\nTriangulo isosceles invertido:\n";
    isoscelesAbajo(n, n);

    cout << "\nTriangulo rectangulo alineado a la derecha:\n";
    rectangulo(1, n);

    return 0;
}