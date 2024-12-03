#ifndef __FINALMESA2021_H__
#define __FINALMESA2021_H__

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

typedef struct{
    char name[50];
    char last_name[50];
    char address[100];
    char DNI[20];
    char telefono[15];
}Cliente;

typedef struct {
    char date[11]; //dd/mm/aaaa
    double monto;
    char DNI[20];
}Consumo;

typedef struct _NodoConsumo {
    Consumo consumo;
    struct _NodoConsumo *next;
}NodoConsumo;

typedef struct {
    Cliente client;
    double total_consumido;
    NodoConsumo *consumos;
}NodoCliente;

typedef struct {
    NodoCliente ** clientes;
    int tamanio;
    int capacidad;
}ListaClientes;

ListaClientes* crear_lista_clientes(int capacidad_inicial);

NodoCliente* CrearNodoCliente(Cliente client);

void AgregarCliente(ListaClientes* lst, Cliente client);

void Agregar_consumo(NodoCliente *nodo_cliente, Consumo consumo);

NodoCliente* Buscar_cliente(ListaClientes *lst, const char *dni);

double ConsultarTotalConsumido(ListaClientes* lst, const char* dni);

void consultar_clientes_en_rango(ListaClientes* lst,double min_consumo, double max_consumo);
#endif //_FINALMESA2021_H_