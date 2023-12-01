#include <stdio.h>
#include <stdlib.h>

// Maximum number of vertices in the graph
#define MAX_VERTICES 100

// Function to initialize an adjacency matrix
void initializeGraph(int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES], int vertices) {
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            adjacencyMatrix[i][j] = 0;
        }
    }
}

// Function to add an edge to the graph
void addEdge(int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES], int source, int destination) {
    // Assuming 0-based indexing
    adjacencyMatrix[source][destination] = 1;
    adjacencyMatrix[destination][source] = 1; // For undirected graph
}

// Function to perform Breadth-First Search (BFS) traversal
void bfs(int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES], int vertices, int startVertex) {
    int visited[MAX_VERTICES] = {0}; // Array to keep track of visited vertices
    int queue[MAX_VERTICES]; // Queue for BFS traversal
    int front = -1, rear = -1;

    // Enqueue the starting vertex
    queue[++rear] = startVertex;
    visited[startVertex] = 1;

    while (front != rear) {
        // Dequeue a vertex and print it
        int currentVertex = queue[++front];
        printf("%d ", currentVertex);

        // Enqueue adjacent vertices
        for (int i = 0; i < vertices; i++) {
            if (adjacencyMatrix[currentVertex][i] == 1 && !visited[i]) {
                queue[++rear] = i;
                visited[i] = 1;
            }
        }
    }
}

// Function to perform Depth-First Search (DFS) traversal
void dfs(int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES], int vertices, int currentVertex, int visited[MAX_VERTICES]) {
    printf("%d ", currentVertex);
    visited[currentVertex] = 1;

    // Visit adjacent vertices
    for (int i = 0; i < vertices; i++) {
        if (adjacencyMatrix[currentVertex][i] == 1 && !visited[i]) {
            dfs(adjacencyMatrix, vertices, i, visited);
        }
    }
}

int main() {
    int vertices, edges, sourceVertex;

    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &vertices);

    int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES];
    initializeGraph(adjacencyMatrix, vertices);

    printf("Enter the number of edges in the graph: ");
    scanf("%d", &edges);

    printf("Enter the edges (format: source destination):\n");
    for (int i = 0; i < edges; i++) {
        int source, destination;
        scanf("%d %d", &source, &destination);
        addEdge(adjacencyMatrix, source, destination);
    }

    printf("Enter the starting vertex for traversal: ");
    scanf("%d", &sourceVertex);

    printf("BFS Traversal: ");
    bfs(adjacencyMatrix, vertices, sourceVertex);
    printf("\n");

    // Reset visited array for DFS
    int visited[MAX_VERTICES] = {0};

    printf("DFS Traversal: ");
    dfs(adjacencyMatrix, vertices, sourceVertex, visited);
    printf("\n");

    return 0;
}
//inputs :
//Number of Vertices: 5
//Number of Edges: 6
//Edges:
//0 1
//0 2
//1 3
//2 4
//3 4
//4 0
//Starting Vertex for Traversal: 0
