#include "grafo.h"

graph_t* create_graph(){
    graph_t* graph = malloc(sizeof(graph_t));
    if (graph == NULL){
        return NULL;
    }
    graph->vertices_count = 0;
    graph->vertices = NULL;

    return graph;
}

int add_vertex(graph_t* graph, int toy_id){
    if (graph == NULL){
        return -1;
    }

    if (find_vertex_by_toy_id(graph, toy_id) != -1) {
        return -1;
    }

    int new_count = graph->vertices_count + 1;
    vertex_t* temp = realloc(graph->vertices, new_count *sizeof(vertex_t));
    if (temp == NULL){
        return -1;
    }

    graph->vertices = temp;
    graph->vertices[graph->vertices_count].toy_id = toy_id;
    graph->vertices[graph->vertices_count].first_adj = NULL;
    
    return graph->vertices_count++;
}

void add_edge(graph_t* graph, int src, int dest, const char *type){
    if (graph == NULL || src < 0 || dest < 0 || src >= graph->vertices_count || dest >= graph->vertices_count){
        return;
    }

    adj_node_t* node = new_adj_node(dest, type);
    if (node == NULL){
        return;
    }
    node->next = graph->vertices[src].first_adj;
    graph->vertices[src].first_adj = node;
}

adj_node_t* new_adj_node(int dest, const char *type) {
    adj_node_t* node = malloc(sizeof(adj_node_t));
    if (node == NULL){
        return NULL;
    }
    node->vertex_index = dest;
    node->type = type;
    node->next = NULL;
    return node;
}

int find_vertex_by_toy_id(graph_t* graph, int toy_id){
    if (graph == NULL){
        return -1;
    }

    for (int i = 0; i < graph->vertices_count; i++){
        if (graph->vertices[i].toy_id == toy_id){
            return i;
        }
    }
    return -1;
}

void free_graph(graph_t* graph){
    if (graph == NULL){
        return;
    }

    for (int i = 0; i < graph->vertices_count; i++){
        adj_node_t* curr = graph->vertices[i].first_adj;
        while (curr != NULL){
            adj_node_t* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }

    free(graph->vertices);
    free(graph);
}