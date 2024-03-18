#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// Structure to represent a graph node
struct Node {
    int vertex;
    struct Node* next;
};

// Structure to represent a graph
struct Graph {
    int numVertices;
    struct Node* adjacencyList[MAX_VERTICES];
    int visited[MAX_VERTICES];
};

// Function to create a new graph node
struct Node* createNode(int vertex) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with 'numVertices' vertices
struct Graph* createGraph(int numVertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = numVertices;

    // Initialize adjacency list and visited array
    for (int i = 0; i < numVertices; i++) {
        graph->adjacencyList[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

// Function to add an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest) {
    // Add edge from src to dest
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjacencyList[src];
    graph->adjacencyList[src] = newNode;

    // Add edge from dest to src
    newNode = createNode(src);
    newNode->next = graph->adjacencyList[dest];
    graph->adjacencyList[dest] = newNode;
}

// Breadth-First Search (BFS) traversal of the graph
void BFS(struct Graph* graph, int startVertex) {
    // Create a queue for BFS
    int queue[MAX_VERTICES];
    int front = -1, rear = -1;

    // Enqueue the starting vertex
    queue[++rear] = startVertex;
    graph->visited[startVertex] = 1;

    while (front != rear) {
        // Dequeue a vertex from the queue and print it
        int currentVertex = queue[++front];
        printf("%d ", currentVertex);

        // Traverse all adjacent vertices of the dequeued vertex
        struct Node* temp = graph->adjacencyList[currentVertex];
        while (temp != NULL) {
            int adjVertex = temp->vertex;
            if (graph->visited[adjVertex] == 0) {
                // Enqueue adjacent vertex if not visited
                queue[++rear] = adjVertex;
                graph->visited[adjVertex] = 1;
            }
            temp = temp->next;
        }
    }
}

// Depth-First Search (DFS) traversal of the graph
void DFS(struct Graph* graph, int startVertex) {
    // Mark the current vertex as visited and print it
    graph->visited[startVertex] = 1;
    printf("%d ", startVertex);

    // Traverse all adjacent vertices of the current vertex
    struct Node* temp = graph->adjacencyList[startVertex];
    while (temp != NULL) {
        int adjVertex = temp->vertex;
        if (graph->visited[adjVertex] == 0) {
            // Recursive call for the unvisited adjacent vertex
            DFS(graph, adjVertex);
        }
        temp = temp->next;
    }
}

// Driver program to test the above functions
int main() {
    int numVertices = 5;
    struct Graph* graph = createGraph(numVertices);

    // Add edges to the graph
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);

    printf("BFS traversal starting from vertex 0: ");
    BFS(graph, 0);
    printf("\n");

    // Reset visited array for DFS
    for (int i = 0; i < numVertices; i++) {
        graph->visited[i] = 0;
    }

    printf("DFS traversal starting from vertex 0: ");
    DFS(graph, 0);
    printf("\n");

    return 0;
}
