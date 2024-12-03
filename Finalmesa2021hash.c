#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 100

// Estructura Cliente
typedef struct {
    char nombre[50];
    char apellido[50];
    char direccion[100];
    char dni[10];
    char telefono[15];
} Cliente;

// Estructura Consumo
typedef struct {
    char fecha[11]; // formato dd/mm/aaaa
    float monto;
    char dni[10];
} Consumo;

// Nodo para la lista de consumos
typedef struct Nodo {
    Consumo consumo;
    struct Nodo *siguiente;
} Nodo;

// Lista de consumos
typedef struct {
    Nodo *cabeza;
} Lista;

// Hashmap
typedef struct {
    Cliente *clientes[HASH_SIZE];
    Lista *consumos[HASH_SIZE];
} HashMap;

// Función de hash
unsigned long hashFunction(char *str) {
    unsigned long hash = 0;
    int c;
    while ((c = *str++))
        hash = c + (hash << 6) + (hash << 16) - hash;
    return hash % HASH_SIZE;
}

// Crear un nuevo hashmap
HashMap* crearHashMap() {
    HashMap *hashmap = (HashMap *)malloc(sizeof(HashMap));
    for (int i = 0; i < HASH_SIZE; i++) {
        hashmap->clientes[i] = NULL;
        hashmap->consumos[i] = NULL;
    }
    return hashmap;
}

// Crear una nueva lista
Lista* crearLista() {
    Lista *lista = (Lista *)malloc(sizeof(Lista));
    lista->cabeza = NULL;
    return lista;
}

// Insertar cliente en el hashmap
void insertarCliente(HashMap *hashmap, Cliente *cliente) {
    unsigned long hashIndex = hashFunction(cliente->dni);
    hashmap->clientes[hashIndex] = cliente;
}

// Insertar consumo en el hashmap
void insertarConsumo(HashMap *hashmap, Consumo *consumo) {
    unsigned long hashIndex = hashFunction(consumo->dni);
    if (hashmap->consumos[hashIndex] == NULL) {
        hashmap->consumos[hashIndex] = crearLista();
    }
    Nodo *nuevoNodo = (Nodo *)malloc(sizeof(Nodo));
    nuevoNodo->consumo = *consumo;
    nuevoNodo->siguiente = hashmap->consumos[hashIndex]->cabeza;
    hashmap->consumos[hashIndex]->cabeza = nuevoNodo;
}

// Consultar consumo total de un cliente
float consumoTotal(HashMap *hashmap, char *dni) {
    unsigned long hashIndex = hashFunction(dni);
    Lista *listaConsumos = hashmap->consumos[hashIndex];
    float total = 0.0;
    Nodo *actual = listaConsumos->cabeza;
    while (actual != NULL) {
        total += actual->consumo.monto;
        actual = actual->siguiente;
    }
    return total;
}

// Consultar clientes en un rango de consumo
void clientesEnRango(HashMap *hashmap, float min, float max) {
    for (int i = 0; i < HASH_SIZE; i++) {
        if (hashmap->consumos[i] != NULL) {
            Cliente *cliente = hashmap->clientes[i];
            if (cliente != NULL) {
                float total = consumoTotal(hashmap, cliente->dni);
                if (total >= min && total <= max) {
                    printf("Cliente: %s %s\n", cliente->nombre, cliente->apellido);
                    printf("Total Consumido: %.2f\n", total);
                }
            }
        }
    }
}

// Main
int main() {
    // Crear hashmap
    HashMap *hashmap = crearHashMap();

    // Insertar clientes
    Cliente cliente1 = {"Juan", "Perez", "Calle Falsa 123", "12345678", "555-1234"};
    insertarCliente(hashmap, &cliente1);

    Cliente cliente2 = {"Maria", "Gomez", "Avenida Siempre Viva 742", "87654321", "555-4321"};
    insertarCliente(hashmap, &cliente2);

    // Insertar consumos
    Consumo consumo1 = {"01/01/2023", 100.0, "12345678"};
    insertarConsumo(hashmap, &consumo1);

    Consumo consumo2 = {"02/01/2023", 200.0, "12345678"};
    insertarConsumo(hashmap, &consumo2);

    Consumo consumo3 = {"03/01/2023", 150.0, "87654321"};
    insertarConsumo(hashmap, &consumo3);

    Consumo consumo4 = {"04/01/2023", 99.99, "87654321"};
    insertarConsumo(hashmap, &consumo4);

    // Consultar consumo total de un cliente
    float total = consumoTotal(hashmap, "12345678");
    printf("Total consumido por cliente 12345678: %.2f\n", total);

    // Consultar clientes en un rango de consumo
    printf("Clientes con consumo entre 50.0 y 250.0:\n");
    clientesEnRango(hashmap, 50.0, 250.0);

    return 0;
}
