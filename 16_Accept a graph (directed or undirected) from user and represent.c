#include <stdio.h>
#include <stdlib.h>

// Node structure for the adjacency list
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// Structure to represent the adjacency list
typedef struct {
    Node** array;
    int vertices;
} AdjList;

// Function to create a new adjacency list node
Node* createNode(int vertex) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

// Function to create a new adjacency list
AdjList* createAdjList(int vertices) {
    AdjList* adjList = (AdjList*)malloc(sizeof(AdjList));
    adjList->array = (Node**)malloc(vertices * sizeof(Node*));
    adjList->vertices = vertices;

    for (int i = 0; i < vertices; ++i)
        adjList->array[i] = NULL;

    return adjList;
}

// Function to add an edge to the adjacency list
void addEdge(AdjList* adjList, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = adjList->array[src];
    adjList->array[src] = newNode;

    // Uncomment the next line for undirected graph
    // newNode = createNode(src);
    // newNode->next = adjList->array[dest];
    // adjList->array[dest] = newNode;
}

// Function to perform Breadth-First Search (BFS) traversal
void bfs(AdjList* adjList, int startVertex) {
    int* visited = (int*)malloc(adjList->vertices * sizeof(int));
    for (int i = 0; i < adjList->vertices; ++i)
        visited[i] = 0;

    int* queue = (int*)malloc(adjList->vertices * sizeof(int));
    int front = -1, rear = -1;

    // Enqueue the starting vertex
    queue[++rear] = startVertex;
    visited[startVertex] = 1;

    while (front != rear) {
        // Dequeue a vertex and print it
        int currentVertex = queue[++front];
        printf("%d ", currentVertex);

        // Enqueue adjacent vertices
        Node* temp = adjList->array[currentVertex];
        while (temp != NULL) {
            if (!visited[temp->vertex]) {
                queue[++rear] = temp->vertex;
                visited[temp->vertex] = 1;
            }
            temp = temp->next;
        }
    }

    free(visited);
    free(queue);
}

// Function to perform Depth-First Search (DFS) traversal
void dfsUtil(AdjList* adjList, int currentVertex, int* visited) {
    printf("%d ", currentVertex);
    visited[currentVertex] = 1;

    // Visit adjacent vertices
    Node* temp = adjList->array[currentVertex];
    while (temp != NULL) {
        if (!visited[temp->vertex])
            dfsUtil(adjList, temp->vertex, visited);
        temp = temp->next;
    }
}

void dfs(AdjList* adjList, int startVertex) {
    int* visited = (int*)malloc(adjList->vertices * sizeof(int));
    for (int i = 0; i < adjList->vertices; ++i)
        visited[i] = 0;

    dfsUtil(adjList, startVertex, visited);

    free(visited);
}

int main() {
    int vertices, edges, src, dest;

    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &vertices);

    AdjList* adjList = createAdjList(vertices);

    printf("Enter the number of edges in the graph: ");
    scanf("%d", &edges);

    printf("Enter the edges (format: source destination):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &src, &dest);
        addEdge(adjList, src, dest);
    }

    printf("Enter the starting vertex for traversal: ");
    scanf("%d", &src);

    printf("BFS Traversal: ");
    bfs(adjList, src);
    printf("\n");

    printf("DFS Traversal: ");
    dfs(adjList, src);
    printf("\n");

    // Free allocated memory
    for (int i = 0; i < vertices; ++i) {
        Node* current = adjList->array[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(adjList->array);
    free(adjList);

    return 0;
}
 //Enter the number of vertices in the graph: 5
//Enter the number of edges in the graph: 6
//Enter the edges (format: source destination):
//0 1
//0 2
//1 3
//2 4
//3 4
//4 0
//Enter the starting vertex for traversal: 0
