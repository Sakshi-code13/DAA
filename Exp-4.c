#include <stdio.h>
#include <stdlib.h>

// Structure to represent an edge in the graph
struct Edge {
    int src, dest, weight;
};

// Structure to represent a graph
struct Graph {
    int V, E;
    struct Edge* edge;
};

// Function to create a graph with V vertices and E edges
struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edge = (struct Edge*)malloc(E * sizeof(struct Edge));
    return graph;
}

// Function to find the parent of a vertex
int find(int parent[], int i) {
    if (parent[i] == -1)
        return i;
    return find(parent, parent[i]);
}

// Function to perform union of two sets
void unionSets(int parent[], int x, int y) {
    int xset = find(parent, x);
    int yset = find(parent, y);
    parent[xset] = yset;
}

// Function to compare two edges based on their weights
int compareEdges(const void* a, const void* b) {
    struct Edge* edge1 = (struct Edge*)a;
    struct Edge* edge2 = (struct Edge*)b;
    return edge1->weight - edge2->weight;
}

// Function to find the Minimum Cost Spanning Tree using Kruskal's Algorithm
void kruskalMST(struct Graph* graph) {
    int V = graph->V;
    struct Edge result[V]; // Array to store the resultant MST
    int e = 0; // Index variable for result[]
    int i = 0; // Index variable for sorted edges array

    // Sort all the edges in non-decreasing order of their weight
    qsort(graph->edge, graph->E, sizeof(struct Edge), compareEdges);

    // Allocate memory for creating V subsets
    int* parent = (int*)malloc(V * sizeof(int));
    for (int v = 0; v < V; v++)
        parent[v] = -1;

    // Keep adding edges to the MST until V-1 edges are added
    while (e < V - 1 && i < graph->E) {
        struct Edge nextEdge = graph->edge[i++];

        int x = find(parent, nextEdge.src);
        int y = find(parent, nextEdge.dest);

        // If including this edge does not form a cycle, add it to the MST
        if (x != y) {
            result[e++] = nextEdge;
            unionSets(parent, x, y);
        }
    }

    // Print the edges of the MST and calculate the minimum cost
    int minCost = 0;
    printf("Minimum Cost Spanning Tree:\n");
    for (i = 0; i < e; i++) {
        printf("%d -- %d\tWeight: %d\n", result[i].src, result[i].dest, result[i].weight);
        minCost += result[i].weight;
    }
    printf("Minimum Cost: %d\n", minCost);
}

int main() {
    int V, E;
    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &V);
    printf("Enter the number of edges in the graph: ");
    scanf("%d", &E);

    struct Graph* graph = createGraph(V, E);

    printf("Enter the source, destination, and weight of each edge:\n");
    for (int i = 0; i < E; i++) {
        scanf("%d %d %d", &graph->edge[i].src, &graph->edge[i].dest, &graph->edge[i].weight);
    }

    kruskalMST(graph);

    return 0;
}

