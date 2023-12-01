#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent an edge in the graph
typedef struct {
    int src, dest, weight;
} Edge;

// Structure to represent a subset for union-find
typedef struct {
    int parent, rank;
} Subset;

// Function prototypes
int find(Subset subsets[], int i);
void unionSets(Subset subsets[], int x, int y);
int compareEdges(const void* a, const void* b);
void kruskalMSTMatrix(int graph[][100], int vertices, int edges);
void kruskalMSTList(Edge* edges, int vertices, int edgesCount);

int main() {
    int vertices, edges;
    int choice;

    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &vertices);

    printf("Enter the number of edges in the graph: ");
    scanf("%d", &edges);

    Edge* edgesList = (Edge*)malloc(edges * sizeof(Edge));
    int adjacencyMatrix[100][100] = {0};

    printf("Choose representation (1 for Matrix / 2 for List): ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter the edges and weights (format: source destination weight):\n");
        for (int i = 0; i < edges; i++) {
            scanf("%d %d %d", &edgesList[i].src, &edgesList[i].dest, &edgesList[i].weight);
            adjacencyMatrix[edgesList[i].src][edgesList[i].dest] = edgesList[i].weight;
            adjacencyMatrix[edgesList[i].dest][edgesList[i].src] = edgesList[i].weight;
        }
        kruskalMSTMatrix(adjacencyMatrix, vertices, edges);
    } else if (choice == 2) {
        printf("Enter the edges and weights (format: source destination weight):\n");
        for (int i = 0; i < edges; i++) {
            scanf("%d %d %d", &edgesList[i].src, &edgesList[i].dest, &edgesList[i].weight);
        }
        kruskalMSTList(edgesList, vertices, edges);
    } else {
        printf("Invalid choice. Exiting.\n");
        return 1;
    }

    free(edgesList);

    return 0;
}

// Find set of an element i
int find(Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);

    return subsets[i].parent;
}

// Union of two sets x and y
void unionSets(Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    // Attach the smaller rank tree under the root of the high rank tree
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        // If ranks are the same, then make one as root and increment its rank by one
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Compare function for qsort
int compareEdges(const void* a, const void* b) {
    return ((Edge*)a)->weight - ((Edge*)b)->weight;
}

// Kruskal's algorithm for graph represented using adjacency matrix
void kruskalMSTMatrix(int graph[][100], int vertices, int edges) {
    Edge result[100]; // Stores the resulting MST
    int resultIndex = 0; // Index used for result[]

    // Sort all the edges in non-decreasing order of their weight
    Edge* edgesList = (Edge*)malloc(edges * sizeof(Edge));
    int edgeCount = 0;
    for (int i = 0; i < vertices; i++) {
        for (int j = i + 1; j < vertices; j++) {
            if (graph[i][j] != 0) {
                edgesList[edgeCount].src = i;
                edgesList[edgeCount].dest = j;
                edgesList[edgeCount].weight = graph[i][j];
                edgeCount++;
            }
        }
    }
    qsort(edgesList, edgeCount, sizeof(Edge), compareEdges);

    // Allocate memory for subsets
    Subset* subsets = (Subset*)malloc(vertices * sizeof(Subset));

    // Create subsets with single elements
    for (int i = 0; i < vertices; i++) {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

    // Number of edges to be taken is equal to vertices-1
    for (int i = 0; resultIndex < vertices - 1; i++) {
        int x = find(subsets, edgesList[i].src);
        int y = find(subsets, edgesList[i].dest);

        // Include the edge if it doesn't form a cycle
        if (x != y) {
            result[resultIndex++] = edgesList[i];
            unionSets(subsets, x, y);
        }
    }

    // Print the constructed MST
    printf("Edge \tWeight\n");
    for (int i = 0; i < resultIndex; i++)
        printf("%d - %d \t%d \n", result[i].src, result[i].dest, result[i].weight);

    free(subsets);
    free(edgesList);
}

// Kruskal's algorithm for graph represented using adjacency list
void kruskalMSTList(Edge* edgesList, int vertices, int edgesCount) {
    Edge result[100]; // Stores the resulting MST
    int resultIndex = 0; // Index used for result[]

    // Sort all the edges in non-decreasing order of their weight
    qsort(edgesList, edgesCount, sizeof(Edge), compareEdges);

    // Allocate memory for subsets
    Subset* subsets = (Subset*)malloc(vertices * sizeof(Subset));

    // Create subsets with single elements
    for (int i = 0; i < vertices; i++) {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

    // Number of edges to be taken is equal to vertices-1
    for (int i = 0; resultIndex < vertices - 1; i++) {
        int x = find(subsets, edgesList[i].src);
        int y = find(subsets, edgesList[i].dest);

        // Include the edge if it doesn't form a cycle
        if (x != y) {
            result[resultIndex++] = edgesList[i];
            unionSets(subsets, x, y);
        }
    }

    // Print the constructed MST
    printf("Edge \tWeight\n");
    for (int i = 0; i < resultIndex; i++)
        printf("%d - %d \t%d \n", result[i].src, result[i].dest, result[i].weight);

    free(subsets);
}
//Enter the number of vertices in the graph: 4
//Enter the number of edges in the graph: 5
//Choose representation (1 for Matrix / 2 for List): 1
//Enter the edges and weights (format: source destination weight):
//0 1 2
//0 2 3
//1 2 1
//1 3 4
//2 3 5
