/*
 * Algoritmo: Mochila Fraccional (Fractional Knapsack)
 * Enfoque: Greedy (Voraz)
 * Complejidad de Tiempo: O(n log n) debido al ordenamiento.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Item {
    int id;
    double peso;
    double valor;
    double ratio; // valor por unidad de peso
};

// Función modular que resuelve el problema
double resolverMochilaFraccional(double capacidad, vector<Item>& items) {
    // Ordenar por ratio de mayor a menor
    sort(items.begin(), items.end(), [](const Item &a, const Item &b){
        return a.ratio > b.ratio;
    });

    double espacio = capacidad;
    double valorTotal = 0;

    cout << fixed << setprecision(2);
    cout << "--- Resultados del Algoritmo ---\n";

    // Iterar y llenar la mochila
    for (size_t i = 0; i < items.size(); i++) {
        if (espacio == 0) break; // Mochila llena

        if (items[i].peso <= espacio) {
            // Se toma completo
            cout << "Paquete " << items[i].id << " -> 100%\n";
            espacio -= items[i].peso;
            valorTotal += items[i].valor;
        }
        else {
            // Se toma solo una fracción
            double fraccion = espacio / items[i].peso;
            cout << "Paquete " << items[i].id << " -> " << fraccion * 100 << "%\n";
            valorTotal += items[i].valor * fraccion;
            espacio = 0;
        }
    }

    return valorTotal;
}

int main() {
    int n = 5;
    double capacidad = 100;

    // Datos de prueba
    double pesos[5]   = {10, 20, 30, 40, 50};
    double valores[5] = {20, 30, 65, 40, 60};

    vector<Item> items;

    // Construir los objetos
    for (int i = 0; i < n; i++) {
        Item it;
        it.id = i + 1;
        it.peso = pesos[i];
        it.valor = valores[i];
        it.ratio = it.valor / it.peso;
        items.push_back(it);
    }

    double valorMaximo = resolverMochilaFraccional(capacidad, items);
    cout << "\nValor total obtenido: " << valorMaximo << "\n";
    
    return 0;
}