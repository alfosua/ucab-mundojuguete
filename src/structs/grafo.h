#include <stdio.h>
#include <stdlib.h>

// Node de lista enlazada para la lista de adyacencias por vertice
// Posee el indice del vertice a conectar dentro del arreglo principal del grafo
// También especifica un mensaje de tipo de conexión (particular al proyecto mundojuguete)
typedef struct adj_node_t {
    int vertex_index;
    const char *type;
    struct adj_node_t* next;
} adj_node_t;

// Vertice de un grafo que contiene la lista de adyacencias
// Entre el juguete especificado a lo otros vertices
typedef struct vertex_t {
    int toy_id;
    adj_node_t* first_adj;
} vertex_t;

// Grafo que contiene un conjunto de vertices no ordenados
// El conjunto de vertices es un arreglo dinamico
typedef struct graph_t {
    int vertices_count;
    vertex_t* vertices;
} graph_t;

// estas son las funciones que necesito que puedas ir implementando
// hazlo en el archivo grafo.c
// no debería ser mayor tema, apoyate de la IA 
// tambien si quieres probar, copia todo esto en tu maquina
// con una función main para irte cerciorando que funciona
// esto lo implementaré directamente en la aplicación web

// Inicializa y reserva memoria para un grafo
graph_t* create_graph();

// Crea un vertice dentro del grafo
int add_vertex(graph_t* graph, int toy_id);

// Crea una arista entre vertices
// src y dest refieren al indice de cada vertice en cuestion dentro del arreglo principal
void add_edge(graph_t* graph, int src, int dest, const char *type);

adj_node_t* new_adj_node(int dest, const char *type);

// Encuentra el indice de un vertice dentro del arreglo principal dado un ID de juguete
int find_vertex_by_toy_id(graph_t* graph, int toy_id);

// Libera la memoría de un grafo
void free_graph(graph_t* graph);