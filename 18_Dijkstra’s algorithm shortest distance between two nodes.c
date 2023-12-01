#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100

// Function to find the vertex with the minimum distance value
int minDistance(int dist[], int sptSet[], int vertices) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < vertices; v++) {
        if (sptSet[v] == 0 && dist[v] < min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

// Function to print the shortest path from source to destination
void printPath(int parent[], int j) {
    if (parent[j] == -1)
        return;

    printPath(parent, parent[j]);
    printf(" -> %d", j);
}

// Function to print the distance and path from source to all vertices
void printSolution(int dist[], int parent[], int vertices, int src, int dest) {
    printf("Vertex\tDistance\tPath\n");
    for (int i = 0; i < vertices; i++) {
        if (i == dest) {
            printf("%d -> %d \t%d\t\t%d", src, i, dist[i], src);
            printPath(parent, i);
            printf("\n");
        } else {
            printf("%d -> %d \t%d\t\t%d", src, i, dist[i], src);
            printPath(parent, i);
            printf(" -> %d\n", i);
        }
    }
}

// Function to implement Dijkstra's algorithm
void dijkstra(int graph[MAX_VERTICES][MAX_VERTICES], int src, int dest, int vertices) {
    int dist[MAX_VERTICES];  // Distance array to store the shortest distance from src to i
    int sptSet[MAX_VERTICES]; // Set to keep track of vertices included in shortest path tree
    int parent[MAX_VERTICES]; // Array to store the shortest path tree

    // Initialize all distances as INFINITE and sptSet[] as 0
    for (int i = 0; i < vertices; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = 0;
        parent[i] = -1;
    }

    // Distance from source to itself is always 0
    dist[src] = 0;

    // Find the shortest path for all vertices
    for (int count = 0; count < vertices - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not yet processed
        int u = minDistance(dist, sptSet, vertices);

        // Mark the picked vertex as processed
        sptSet[u] = 1;

        // Update dist value of the adjacent vertices of the picked vertex
        for (int v = 0; v < vertices; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    // Print the solution
    printSolution(dist, parent, vertices, src, dest);
}

int main() {
    int vertices, src, dest;

    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &vertices);

    int graph[MAX_VERTICES][MAX_VERTICES];

    printf("Enter the adjacency matrix for the graph:\n");
    for (int i = 0; i < vertices; i++)
        for (int j = 0; j < vertices; j++)
            scanf("%d", &graph[i][j]);

    printf("Enter the source node: ");
    scanf("%d", &src);

    printf("Enter the destination node: ");
    scanf("%d", &dest);

    // Run Dijkstra's algorithm
    dijkstra(graph, src, dest, vertices);

    return 0;
}
//Enter the number of vertices in the graph: 5
//Enter the adjacency matrix for the graph:
//0 2 0 6 0
//2 0 3 8 5
//0 3 0 0 7
//6 8 0 0 9
//0 5 7 9 0
//Enter the source node: 0
//Enter the destination node: 4
