#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICES 26

typedef struct Edge {
    char vertex;
    int weight;
    struct Edge *next;
} Edge;

typedef struct Vertex {
    char id;
    Edge *edges;
} Vertex;

typedef struct {
    int numVertices;
    Vertex vertices[MAX_VERTICES];
} Graph;

Graph *createGraph(int numVertices);
void addEdge(Graph *graph, char src, char dest, int weight);
void processQuery(Graph *graph, char vertex);
void freeGraph(Graph *graph);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <graph_file> <query_file>\n", argv[0]);
        return 1;
    }

    FILE *graphFile = fopen(argv[1], "r");
    if (!graphFile) {
        perror("Failed to open graph file");
        return 1;
    }

    int numVertices;
    fscanf(graphFile, "%d\n", &numVertices);
    Graph *graph = createGraph(numVertices);

    char vertex;
    for (int i = 0; i < numVertices; i++) {
        fscanf(graphFile, " %c", &vertex);
        graph->vertices[i].id = vertex;
    }

    char src, dest;
    int weight;
    while (fscanf(graphFile, " %c %c %d", &src, &dest, &weight) == 3) {
        addEdge(graph, src, dest, weight);
        addEdge(graph, dest, src, weight);
    }
    fclose(graphFile);

    FILE *queryFile = fopen(argv[2], "r");
    if (!queryFile) {
        perror("Failed to open query file");
        freeGraph(graph);
        return 1;
    }

    char query;
    while (fscanf(queryFile, " %c", &query) == 1) {
        processQuery(graph, query);
    }
    fclose(queryFile);
    freeGraph(graph);
    return 0;
}

Graph *createGraph(int numVertices) {
    Graph *graph = malloc(sizeof(Graph));
    graph->numVertices = numVertices;
    for (int i = 0; i < MAX_VERTICES; i++) {
        graph->vertices[i].id = 0;
        graph->vertices[i].edges = NULL;
    }
    return graph;
}

void addEdge(Graph *graph, char src, char dest, int weight) {
    int index;
    for (index = 0; index < graph->numVertices; index++) {
        if (graph->vertices[index].id == src) break;
    }
    Edge *newEdge = malloc(sizeof(Edge));
    newEdge->vertex = dest;
    newEdge->weight = weight;
    newEdge->next = graph->vertices[index].edges;
    graph->vertices[index].edges = newEdge;
}

void processQuery(Graph *graph, char vertex) {
    int index;
    for (index = 0; index < graph->numVertices; index++) {
        if (graph->vertices[index].id == vertex) break;
    }
    if (index == graph->numVertices) {
        printf("%c\n", vertex);
        return;
    }

    Vertex v = graph->vertices[index];
    char adj[MAX_VERTICES] = {0};
    int count = 0;
    int bandwidth = 0;
    Edge *edge = v.edges;
    while (edge) {
        adj[count++] = edge->vertex;
        bandwidth += edge->weight;
        edge = edge->next;
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (adj[j] > adj[j + 1]) {
                char temp = adj[j];
                adj[j] = adj[j + 1];
                adj[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < count; i++) {
        printf("%c ", adj[i]);
    }
    printf("%d\n", bandwidth);
}

void freeGraph(Graph *graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        Edge *edge = graph->vertices[i].edges;
        while (edge) {
            Edge *temp = edge;
            edge = edge->next;
            free(temp);
        }
    }
    free(graph);
}
