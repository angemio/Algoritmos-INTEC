/*
/A.El primer nodo siempre será el root.
B.Al presentar el árbol debe ser de un modo intuitivo, que muestre la topología de forma
que represente en árbol.
C.Puede utilizar cualquiera de los recorridos para arboles(InOrden, PreOrden o
    PostOrden).
    D.Al eliminar un nodo debe observar las reglas para la sustitución del nodo, permitiendo
    así que el árbol se reconstruya.
    E.Al insertar un nodo deben observarse las reglas para arboles binarios de búsqueda, es
    decir, los nodos cuyo valor sea mayor que el nodo raíz a la derecha(en el subárbol
        derecho), en caso contrario a la izquierda(en el subárbol izquierdo).Recordando que
    deben ocupar el lugar que le corresponda según la topología del árbol.
    Grupo 5 ------------------:

Angel De La Rosa - 1123662
Oliver Santana - 1123346
Joaquin Ramirez - 1127772
Emill Brito - 1127139
Dorian Diaz - 1122826
Justin Jimenez - 1122941
15 / 09 / 25
* /
*/

#include <iostream>  // Para entrada y salida de datos (cout, cin)
#include <stdlib.h>  // Para usar system("pause") y system("cls")
#include <conio.h>   // Librería no estándar, a menudo usada para getch() en Windows

using namespace std;

// Estructura que define cada nodo del árbol binario
struct ArbolBinario {
    int dato;                 // El valor numérico que almacena el nodo
    ArbolBinario* izquierdo;  // Puntero al subárbol izquierdo (valores menores)
    ArbolBinario* derecho;    // Puntero al subárbol derecho (valores mayores)
    ArbolBinario* padre;      // Puntero al nodo padre, útil para la eliminación
};

// Prototipos de las funciones que se usarán en el programa.
// Es una buena práctica declararlas al principio.
ArbolBinario* crearNodo(int, ArbolBinario*);
ArbolBinario* raiz = nullptr; // Puntero global que siempre apuntará a la raíz del árbol. Inicia en nullptr porque el árbol está vacío.
void insertar(ArbolBinario*&, int, ArbolBinario*);
void mostrarArbol(ArbolBinario*, int);
bool buscarNodo(ArbolBinario*, int);
void PreOrden(ArbolBinario*);
void InOrden(ArbolBinario*);
void PostOrden(ArbolBinario*);
void eliminar(ArbolBinario*&, int);
void eliminarNodo(ArbolBinario*);
ArbolBinario* minimo(ArbolBinario*);
void Reemplazar(ArbolBinario*, ArbolBinario*);
void destruirNodo(ArbolBinario*);

// Función para crear un nuevo nodo. Es como una "fábrica" de nodos.
ArbolBinario* crearNodo(int valor, ArbolBinario* padre) {
    // 1. Reservar memoria para un nuevo nodo de tipo ArbolBinario
    ArbolBinario* nuevoNodo = new ArbolBinario();

    // 2. Asignar los valores iniciales al nodo creado
    nuevoNodo->dato = valor;
    nuevoNodo->izquierdo = nullptr; // Un nodo nuevo no tiene hijos al crearse
    nuevoNodo->derecho = nullptr;
    nuevoNodo->padre = padre;     // Se le asigna su nodo padre

    // 3. Devolver el puntero al nodo recién creado
    return nuevoNodo;
}

// Función recursiva para insertar un elemento en el árbol
// El primer parámetro se pasa por referencia (&) para poder modificar el árbol original
void insertar(ArbolBinario*& arbol, int valor, ArbolBinario* padre) {
    // Caso base: Si el árbol (o subárbol) está vacío, aquí es donde debemos insertar el nuevo nodo.
    if (arbol == nullptr) {
        ArbolBinario* nuevoNodo = crearNodo(valor, padre);
        arbol = nuevoNodo; // El puntero del árbol ahora apunta a este nuevo nodo
    }
    // Caso recursivo: Si el árbol no está vacío, decidimos si ir a la izquierda o a la derecha
    else {
        int valorRaiz = arbol->dato; // Obtenemos el valor del nodo actual para comparar

        // Si el valor ya existe, informamos y no lo insertamos para evitar duplicados.
        if (valor == valorRaiz) {
            cout << "\nEl nodo " << valor << " ya se encuentra en el arbol.\n";
            return;
        }
        // Si el valor a insertar es menor que el valor del nodo actual, vamos al subárbol izquierdo
        else if (valor < valorRaiz) {
            insertar(arbol->izquierdo, valor, arbol);
        }
        // Si el valor a insertar es mayor, vamos al subárbol derecho
        else {
            insertar(arbol->derecho, valor, arbol);
        }
    }
}

// Muestra el árbol de forma visual en la consola (acostado)
// El 'cont' aumenta en cada nivel para crear la indentación
void mostrarArbol(ArbolBinario* arbol, int cont) {
    // Caso base: si el nodo es nulo, no hay nada que mostrar, así que retornamos.
    if (arbol == nullptr) {
        return;
    }
    // Lógica de "InOrden Inverso":
    // 1. Primero vamos recursivamente al subárbol derecho (los valores más grandes)
    mostrarArbol(arbol->derecho, cont + 1);

    // 2. Imprimimos el nodo actual, con una indentación proporcional a su profundidad
    for (int i = 0; i < cont; i++) {
        cout << "   "; // Tres espacios por nivel de profundidad
    }
    cout << arbol->dato << endl;

    // 3. Finalmente, vamos recursivamente al subárbol izquierdo (los valores más pequeños)
    mostrarArbol(arbol->izquierdo, cont + 1);
}


// Función recursiva para buscar un nodo en el árbol
bool buscarNodo(ArbolBinario* arbol, int valor) {
    // Caso base 1: Si llegamos a un punto nulo, el elemento no está en el árbol
    if (arbol == nullptr) {
        return false;
    }
    // Caso base 2: Si el dato del nodo actual es el que buscamos, lo encontramos
    else if (arbol->dato == valor) {
        return true;
    }
    // Caso recursivo: Decidimos si buscar por la izquierda o la derecha
    else if (valor < arbol->dato) {
        return buscarNodo(arbol->izquierdo, valor);
    }
    else {
        return buscarNodo(arbol->derecho, valor);
    }
}

// --- RECORRIDOS DEL ÁRBOL ---

// Recorrido en PreOrden: Raíz -> Izquierda -> Derecha
void PreOrden(ArbolBinario* arbol) {
    if (arbol == nullptr) return;
    cout << arbol->dato << " - "; // 1. Procesar la raíz
    PreOrden(arbol->izquierdo);   // 2. Recorrer subárbol izquierdo
    PreOrden(arbol->derecho);     // 3. Recorrer subárbol derecho
}

// Recorrido en InOrden: Izquierda -> Raíz -> Derecha
// En un ABB, este recorrido muestra los elementos en orden ascendente.
void InOrden(ArbolBinario* arbol) {
    if (arbol == nullptr) return;
    InOrden(arbol->izquierdo);     // 1. Recorrer subárbol izquierdo
    cout << arbol->dato << " - "; // 2. Procesar la raíz
    InOrden(arbol->derecho);      // 3. Recorrer subárbol derecho
}

// Recorrido en PostOrden: Izquierda -> Derecha -> Raíz
void PostOrden(ArbolBinario* arbol) {
    if (arbol == nullptr) return;
    PostOrden(arbol->izquierdo);    // 1. Recorrer subárbol izquierdo
    PostOrden(arbol->derecho);      // 2. Recorrer subárbol derecho
    cout << arbol->dato << " - "; // 3. Procesar la raíz
}

// --- LÓGICA DE ELIMINACIÓN ---

// Función principal para eliminar. Primero busca el nodo y luego lo elimina.
void eliminar(ArbolBinario*& arbol, int valor) {
    if (arbol == nullptr) {
        // Si el árbol está vacío o no se encontró el nodo, no hay nada que hacer.
        return;
    }
    else if (valor < arbol->dato) {
        // Si el valor es menor, buscamos en el subárbol izquierdo
        eliminar(arbol->izquierdo, valor);
    }
    else if (valor > arbol->dato) {
        // Si el valor es mayor, buscamos en el subárbol derecho
        eliminar(arbol->derecho, valor);
    }
    else {
        // Si encontramos el nodo con el valor a eliminar, llamamos a la función que maneja los casos
        eliminarNodo(arbol);
    }
}

// Encuentra el nodo con el valor más pequeño en un subárbol (el sucesor inorden)
// Esto se logra yendo siempre hacia la izquierda lo más posible.
ArbolBinario* minimo(ArbolBinario* arbol) {
    if (arbol == nullptr) {
        return nullptr;
    }
    if (arbol->izquierdo) {
        return minimo(arbol->izquierdo); // Sigue yendo a la izquierda
    }
    else {
        return arbol; // Si no hay más a la izquierda, este es el mínimo
    }
}

// Reemplaza un nodo por otro. Actualiza los punteros del padre del nodo a reemplazar.
void Reemplazar(ArbolBinario* arbol, ArbolBinario* nuevoNodo) {
    // Si el nodo a reemplazar tiene un padre
    if (arbol->padre) {
        // Averiguamos si el nodo a reemplazar era el hijo izquierdo o derecho de su padre
        if (arbol == arbol->padre->izquierdo) {
            arbol->padre->izquierdo = nuevoNodo;
        }
        else if (arbol == arbol->padre->derecho) {
            arbol->padre->derecho = nuevoNodo;
        }
    }
    // Si el nuevo nodo existe, actualizamos su puntero padre
    if (nuevoNodo) {
        nuevoNodo->padre = arbol->padre;
    }
}

// Libera la memoria de un nodo
void destruirNodo(ArbolBinario* nodo) {
    nodo->izquierdo = nullptr;
    nodo->derecho = nullptr;
    delete nodo; // Libera la memoria del nodo
}

// Función que gestiona los 3 casos de eliminación de un nodo
void eliminarNodo(ArbolBinario* nodoEliminar) {
    // Caso 1: El nodo tiene dos hijos (izquierdo y derecho)
    if (nodoEliminar->izquierdo && nodoEliminar->derecho) {
        // 1. Encontrar el nodo más pequeño del subárbol derecho (el sucesor)
        ArbolBinario* menor = minimo(nodoEliminar->derecho);
        // 2. Reemplazar el valor del nodo a eliminar con el valor del sucesor
        nodoEliminar->dato = menor->dato;
        // 3. Ahora, el problema se reduce a eliminar el nodo sucesor (que es un caso más simple)
        eliminarNodo(menor);
    }
    // Caso 2: El nodo tiene solo un hijo izquierdo
    else if (nodoEliminar->izquierdo) {
        Reemplazar(nodoEliminar, nodoEliminar->izquierdo); // Su padre ahora apunta a su nieto
        destruirNodo(nodoEliminar); // Se elimina el nodo
    }
    // Caso 3: El nodo tiene solo un hijo derecho
    else if (nodoEliminar->derecho) {
        Reemplazar(nodoEliminar, nodoEliminar->derecho); // Su padre ahora apunta a su nieto
        destruirNodo(nodoEliminar); // Se elimina el nodo
    }
    // Caso 4: El nodo no tiene hijos (es una hoja)
    else {
        Reemplazar(nodoEliminar, nullptr); // Su padre ahora apunta a nulo
        destruirNodo(nodoEliminar); // Se elimina el nodo
    }
}


// --- PROGRAMA PRINCIPAL ---
int main() {
    int opcion, dato, contador = 0;
    // Bucle principal del menú. Se repite hasta que el usuario elija la opción 8 (Salir).
    do {
        cout << "\t.:MENU:." << endl;
        cout << "1. Insertar un nuevo nodo" << endl;
        cout << "2. Mostrar el arbol completo" << endl;
        cout << "3. Buscar un elemento en el arbol" << endl;
        cout << "4. Recorrer el arbol en PreOrden" << endl;
        cout << "5. Recorrer el arbol en InOrden" << endl;
        cout << "6. Recorrer el arbol en PostOrden" << endl;
        cout << "7. Eliminar un nodo del arbol" << endl;
        cout << "8. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        // Estructura switch para manejar la opción del usuario
        switch (opcion) {
        case 1:
            cout << "\nDigite un numero: ";
            cin >> dato;
            insertar(raiz, dato, nullptr); // Llama a la función para insertar
            cout << "\n";
            system("pause"); // Pausa la ejecución hasta que el usuario presione una tecla
            break;
        case 2:
            if (raiz == nullptr) {
                cout << "\nEl arbol esta vacio.\n";
            }
            else {
                cout << "\nMostrando el arbol:\n\n";
                mostrarArbol(raiz, contador); // Muestra el árbol completo
            }
            cout << "\n";
            system("pause");
            break;
        case 3:
            if (raiz == nullptr) {
                cout << "\nEl arbol esta vacio.\n";
            }
            else {
                cout << "\nDigite el elemento a buscar: ";
                cin >> dato;
                if (buscarNodo(raiz, dato)) { // Llama a la función de búsqueda
                    cout << "\nEl elemento " << dato << " si se encuentra en el arbol\n";
                }
                else {
                    cout << "\nEl elemento " << dato << " no se encuentra en el arbol\n";
                }
            }
            cout << "\n";
            system("pause");
            break;
        case 4:
            if (raiz == nullptr) {
                cout << "\nEl arbol esta vacio.\n";
            }
            else {
                cout << "\nRecorrido PreOrden: ";
                PreOrden(raiz); // Muestra recorrido PreOrden
            }
            cout << "\n\n";
            system("pause");
            break;

        case 5:
            if (raiz == nullptr) {
                cout << "\nEl arbol esta vacio.\n";
            }
            else {
                cout << "\nRecorrido InOrden: ";
                InOrden(raiz); // Muestra recorrido InOrden
            }
            cout << "\n\n";
            system("pause");
            break;

        case 6:
            if (raiz == nullptr) {
                cout << "\nEl arbol esta vacio.\n";
            }
            else {
                cout << "\nRecorrido PostOrden: ";
                PostOrden(raiz); // Muestra recorrido PostOrden
            }
            cout << "\n\n";
            system("pause");
            break;
        case 7:
            if (raiz == nullptr) {
                cout << "\nEl arbol esta vacio, no hay nodos que eliminar.\n";
            }
            else {
                cout << "\nDigite el elemento a eliminar: ";
                cin >> dato;
                eliminar(raiz, dato); // Llama a la función de eliminación
                cout << "\nNodo eliminado (si existia).\n";
            }
            cout << "\n";
            system("pause");
            break;
        case 8:
            break; // Simplemente sale del switch, y el bucle do-while terminará
        default:
            cout << "\nOpcion incorrecta\n";
            system("pause");
            break;
        }
        system("cls"); // Limpia la pantalla de la consola para mostrar el menú nuevamente
    } while (opcion != 8);

    // El programa finaliza al salir del bucle.
    return 0;
}