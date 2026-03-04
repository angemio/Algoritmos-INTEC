#include <iostream>
#include <vector>
#include <iomanip>  
#include <cstdlib> 
#include <ctime>    
#include <algorithm> 

using namespace std;

// estructura para almacenar una ruta completa y su costo
struct Ruta {
    vector<int> camino;
    int costoTotal;
};

int numVertices;
int grafo[30][30]; // matriz de adyacencia (max 30)
vector<Ruta> todasLasRutas; // almacenara todas las rutas encontradas
int mejorCostoGlobal = 999999; // variable para optimizacion (evitar bucles infinitos)

// funcion para inicializar el grafo con -1 (indicando que no hay conexion)
void inicializarGrafo() {
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 30; j++) {
            grafo[i][j] = -1; // -1 significa sin conexion
        }
    }
}

// funcion para generar el grafo aleatorio segun el mandato
void generarGrafoAleatorio() {
    // regla: cantidad de vertices aleatoria (15-30)
    numVertices = 15 + (rand() % 16); 
    
    cout << "--- Generando Grafo con " << numVertices << " vertices ---" << endl;

    int maxAristas = numVertices / 3;
    if (maxAristas < 2) maxAristas = 2; // seguridad por si N es pequeño

    for (int i = 0; i < numVertices; i++) {
        // regla: minimo 2 relaciones, maximo N/3
        int numRelaciones = 2 + (rand() % (maxAristas - 2 + 1));
        
        for (int k = 0; k < numRelaciones; k++) {
            int destino;
            int peso;
            
            // buscamos un destino que no sea el mismo nodo (bucle) y que no tenga ya conexion
            do {
                destino = rand() % numVertices;
            } while (destino == i || grafo[i][destino] != -1);

            // regla: ponderacion aleatoria (ejemplo 1 a 50)
            peso = 1 + (rand() % 50);
            
            grafo[i][destino] = peso;
        }
    }
}

// funcion para mostrar la matriz de adyacencia
void mostrarMatriz() {
    cout << "\n--- Matriz de Adyacencia (Pesos) ---\n";
    cout << "   ";
    for (int i = 0; i < numVertices; i++) cout << setw(3) << i << " ";
    cout << endl;

    for (int i = 0; i < numVertices; i++) {
        cout << setw(2) << i << "|";
        for (int j = 0; j < numVertices; j++) {
            if (grafo[i][j] == -1) 
                cout << "  - ";
            else 
                cout << setw(3) << grafo[i][j] << " ";
        }
        cout << endl;
    }
    cout << "------------------------------------\n";
}

// algoritmo DFS para encontrar TODOS los caminos (Optimizado)
void DFS(int actual, int destino, vector<int>& caminoActual, int costoActual, vector<bool>& visitado) {
    
    // FRENOS DE SEGURIDAD (Para que no se trabe)
    if (todasLasRutas.size() > 2000) return; // Limite de rutas a buscar
    if (mejorCostoGlobal != 999999 && costoActual > mejorCostoGlobal * 2) return; // Poda por costo excesivo

    // marcamos nodo actual como visitado y lo agregamos al camino
    visitado[actual] = true;
    caminoActual.push_back(actual);

    // caso base: llegamos al destino
    if (actual == destino) {
        Ruta nuevaRuta;
        nuevaRuta.camino = caminoActual;
        nuevaRuta.costoTotal = costoActual;
        todasLasRutas.push_back(nuevaRuta);
        
        // actualizamos el mejor costo encontrado
        if (costoActual < mejorCostoGlobal) mejorCostoGlobal = costoActual;

    } else {
        // explorar vecinos
        for (int i = 0; i < numVertices; i++) {
            // si hay conexion (distinto de -1) y no ha sido visitado en este camino actual
            if (grafo[actual][i] != -1 && !visitado[i]) {
                DFS(i, destino, caminoActual, costoActual + grafo[actual][i], visitado);
                
                // si ya llegamos al limite de rutas, rompemos el bucle
                if (todasLasRutas.size() > 2000) break;
            }
        }
    }

    // desmarcar para permitir otros caminos que pasen por aqui
    visitado[actual] = false;
    caminoActual.pop_back();
}

// funcion auxiliar para comparar rutas (para ordenar)
bool compararRutas(const Ruta& a, const Ruta& b) {
    return a.costoTotal < b.costoTotal; // menor costo primero
}

int main() {
    srand(time(0));

    inicializarGrafo();
    generarGrafoAleatorio();
    mostrarMatriz();

    int inicio, fin;

    // capturamos los datos
    
    cout << "\nIngrese el vertice de Inicio (0 - " << numVertices - 1 << "): ";
    cin >> inicio;
    cout << "Ingrese el vertice de Destino (0 - " << numVertices - 1 << "): ";
    cin >> fin;

    if (inicio < 0 || inicio >= numVertices || fin < 0 || fin >= numVertices) {
        cout << "Error: Vertices fuera de rango" << endl;
        return 1;
    }

    // preparar DFS
    vector<int> caminoActual;
    vector<bool> visitado(numVertices, false);
    todasLasRutas.clear();
    mejorCostoGlobal = 999999; // reiniciamos variable de optimizacion

    // ejecutamos la busqueda
    cout << "Buscando rutas..." << endl;
    DFS(inicio, fin, caminoActual, 0, visitado);

    // procesar resultados
    if (todasLasRutas.empty()) {
        cout << "\nNo existe ninguna ruta entre el vertice " << inicio << " y " << fin << "." << endl;
    } else {
        // ordenamos las rutas de menor a mayor costo
        sort(todasLasRutas.begin(), todasLasRutas.end(), compararRutas);

        cout << "\n--- Resultados: Las mejores rutas encontradas ---" << endl;
        
        // mostrar maximo las 2 mejores
        int limite = (todasLasRutas.size() < 2) ? todasLasRutas.size() : 2;

        for (int i = 0; i < limite; i++) {
            cout << "Ruta #" << (i + 1) << " (Costo: " << todasLasRutas[i].costoTotal << "): ";
            for (size_t j = 0; j < todasLasRutas[i].camino.size(); j++) {
                cout << todasLasRutas[i].camino[j];
                if (j < todasLasRutas[i].camino.size() - 1) cout << " -> ";
            }
            cout << endl;
        }
    }

    return 0;
}