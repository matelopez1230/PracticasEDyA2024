#include "Finalmesa2021.h"

ListaClientes* crear_lista_clientes(int capacidad_inicial){
    ListaClientes *lst = malloc(sizeof(ListaClientes));
    lst->clientes = malloc(sizeof(NodoCliente*)*capacidad_inicial);
    lst->tamanio = 0;
    lst->capacidad = capacidad_inicial;
    return lst;
}

NodoCliente* CrearNodoCliente(Cliente client) {
    NodoCliente* node = malloc(sizeof(NodoCliente));
    node->client = client;
    node->total_consumido = 0;
    node->consumos = NULL;
    return node;
}

void AgregarCliente(ListaClientes* lst, Cliente client) {
    if (lst->tamanio >= lst->capacidad) {
        lst->capacidad *= 2;
        lst->clientes= realloc(lst->clientes, sizeof(NodoCliente)* lst->capacidad);
    }
    NodoCliente* new_client = CrearNodoCliente(client);
    lst->clientes[lst->tamanio++] = new_client;
}

void Agregar_consumo(NodoCliente *nodo_cliente, Consumo consumo) {
    NodoConsumo* nuevo_consumo = malloc(sizeof(NodoConsumo));
    nuevo_consumo->consumo = consumo;
    nuevo_consumo->next = nodo_cliente->consumos;
    nodo_cliente->consumos = nuevo_consumo;
    nodo_cliente->total_consumido +=consumo.monto;
}

NodoCliente* Buscar_cliente(ListaClientes *lst, const char *dni) {
    for (int i = 0; i < lst->tamanio; i++) {
        if (strcmp(lst->clientes[i]->client.DNI,dni) == 0) {
            return lst->clientes[i];
        }
    }
    return NULL;
}

double ConsultarTotalConsumido(ListaClientes* lst, const char* dni) {
    NodoCliente* client = Buscar_cliente(lst, dni);
    if (client) {
        return client->total_consumido;
    }
    return -1;    
}

void consultar_clientes_en_rango(ListaClientes* lst,double min_consumo, double max_consumo) {
    for (int i = 0; i < lst->tamanio; i++) {
        double total_consumido = lst->clientes[i]->total_consumido;
        if (total_consumido >= min_consumo && total_consumido<= max_consumo) {
            printf("Cliente: %s %s, DNI: %s, Total consumido: %.2f\n",lst->clientes[i]->client.name,lst->clientes[i]->client.last_name,lst->clientes[i]->client.DNI,total_consumido);
        }
        
    }
    
}

int main(){
    ListaClientes *lst = crear_lista_clientes(10);

    Cliente client1 = {"Checo", "Perez","Calle falsa 123","12345678","555-1234"};
    AgregarCliente(lst,client1);

    Consumo consumo1 = {"01/01/2024", 100.50,"12345678"};
    Consumo consumo2 = {"02/01/2024", 150.75,"12345678"};


    NodoCliente* nodo_cliente = Buscar_cliente(lst, "12345678");
    if (nodo_cliente) {
        Agregar_consumo(nodo_cliente,consumo1);
        Agregar_consumo(nodo_cliente,consumo2);
    }

    printf("Total consumido por Checo: %.2f\n",ConsultarTotalConsumido(lst,"12345678"));

    Cliente client2 = {"Carlos", "Sainz jr","Calle falsa 456","12345679","555-1235"};
    AgregarCliente(lst,client2);

    Consumo consumo3 = {"01/01/2024", 100.50,"12345679"};
    Consumo consumo4 = {"02/01/2024", 50.75,"12345679"};


   
    NodoCliente* nodo_cliente2 = Buscar_cliente(lst, "12345679");
    if (nodo_cliente2) {
        Agregar_consumo(nodo_cliente2,consumo3);
        Agregar_consumo(nodo_cliente2,consumo4);
    }
    
    printf("Total consumido por Carlos: %.2f\n",ConsultarTotalConsumido(lst,"12345679"));

    
    printf("Clientes que han consumido entre 50 y 200: \n");
    consultar_clientes_en_rango(lst, 50.0, 200.0);
    return 0;
}