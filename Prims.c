#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

// Structure to represent an edge in the graph
struct Edge {
    int dest;
    int weight;
    struct Edge* next;
};

// Structure to represent a vertex in the graph
struct Vertex {
    int key;
    struct Edge* list;
};

// Structure to represent the graph
struct Graph {
    int V;
    struct Vertex* array;
};

// Function to create a new graph with V vertices
struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->array = (struct Vertex*)malloc(V * sizeof(struct Vertex));

    for (int i = 0; i < V; ++i) {
        graph->array[i].key = INT_MAX;
        graph->array[i].list = NULL;
    }

    return graph;
}

// Function to add an edge to the graph
void addEdge(struct Graph* graph, int src, int dest, int weight) {
    // Add edge from src to dest
    struct Edge* newEdge = (struct Edge*)malloc(sizeof(struct Edge));
    newEdge->dest = dest;
    newEdge->weight = weight;
    newEdge->next = graph->array[src].list;
    graph->array[src].list = newEdge;

    // Add edge from dest to src (since the graph is undirected)
    newEdge = (struct Edge*)malloc(sizeof(struct Edge));
    newEdge->dest = src;
    newEdge->weight = weight;
    newEdge->next = graph->array[dest].list;
    graph->array[dest].list = newEdge;
}

// Function to find the minimum key value vertex
int minKey(int key[], bool mstSet[], int V) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++) {
        if (mstSet[v] == false && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }

    return min_index;
}

// Function to print the MST using Prim's algorithm
void primMST(struct Graph* graph) {
    int parent[graph->V]; // Array to store the constructed MST
    int key[graph->V];    // Key values used to pick the minimum weight edge
    bool mstSet[graph->V]; // To represent set of vertices included in MST

    // Initialize all keys as INFINITE
    for (int i = 0; i < graph->V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    // Always include the first vertex in MST
    key[0] = 0;
    parent[0] = -1; // First node is always the root of MST

    // The MST will have V vertices
    for (int count = 0; count < graph->V - 1; count++) {
        // Pick the minimum key vertex from the set of vertices not yet included in MST
        int u = minKey(key, mstSet, graph->V);

        // Add the picked vertex to the MST set
        mstSet[u] = true;

        // Update key value and parent index of the adjacent vertices of the picked vertex
        struct Edge* current = graph->array[u].list;
        while (current != NULL) {
            int v = current->dest;
            if (mstSet[v] == false && current->weight < key[v]) {
                parent[v] = u;
                key[v] = current->weight;
            }
            current = current->next;
        }
    }

    // Print the constructed MST
    printf("Edge   Weight\n");
    for (int i = 1; i < graph->V; i++) {
        printf("%d - %d    %d\n", parent[i], i, key[i]);
    }
}

int main() {
    int V = 5; // Number of vertices in the graph
    struct Graph* graph = createGraph(V);

    // Adding edges to the graph
    addEdge(graph, 0, 1, 2);
    addEdge(graph, 0, 3, 6);
    addEdge(graph, 1, 2, 3);
    addEdge(graph, 1, 3, 8);
    addEdge(graph, 1, 4, 5);
    addEdge(graph, 2, 4, 7);
    addEdge(graph, 3, 4, 9);

    // Print the MST
    primMST(graph);

    return 0;
}
