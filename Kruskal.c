#include <stdio.h>
#include <stdlib.h>

// Structure to represent an edge in the graph
struct Edge {
    int src, dest, weight;
};

// Structure to represent a subset for union-find
struct Subset {
    int parent, rank;
};

// Function to find the set of an element using union-find
int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Function to perform union of two sets
void unionSets(struct Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    // Attach smaller rank tree under root of high rank tree
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        // If ranks are the same, make one as root and increment its rank
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Comparator function used for sorting edges based on their weight
int compare(const void* a, const void* b) {
    return ((struct Edge*)a)->weight - ((struct Edge*)b)->weight;
}

// Function to find the minimum spanning tree using Kruskal's algorithm
void kruskal(struct Edge edges[], int V, int E) {
    // Allocate memory for subsets
    struct Subset* subsets = (struct Subset*)malloc(V * sizeof(struct Subset));

    // Initialize subsets for each vertex
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    //qsort is a C standard library function that implements a sorting algorithm for arrays of arbitrary objects according to a user-provided comparison function
    // Sort edges in non-decreasing order by weight
    qsort(edges, E, sizeof(edges[0]), compare);

    // Initialize result
    struct Edge result[V - 1];

    // Index for result array
    int i = 0;

    // Index for sorted edges array
    int e = 0;

    // Build the minimum spanning tree
    while (i < V - 1 && e < E) {
        // Pick the smallest edge and increment the index for next iteration
        struct Edge next_edge = edges[e++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        // If including this edge doesn't cause a cycle, add it to the result
        if (x != y) {
            result[i++] = next_edge;
            unionSets(subsets, x, y);
        }
    }

    // Print the result
    printf("Edges in the minimum spanning tree:\n");
    for (i = 0; i < V - 1; ++i)
        printf("(%d, %d) -> %d\n", result[i].src, result[i].dest, result[i].weight);

    // Free allocated memory
    free(subsets);
}

// Driver program to test the above functions
int main() {
    // Example usage
    int V = 4;  // Number of vertices in the graph
    int E = 5;  // Number of edges in the graph

    // Create an array of edges representing the graph
    struct Edge edges[] = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };

    // Call the Kruskal's algorithm function
    kruskal(edges, V, E);

    return 0;
}
