#include <stdio.h>
#include <stdlib.h>

#define INF 99999

// Function to implement Floyd–Warshall Algorithm
void floydWarshall(int **graph, int V) {
    int dist[V][V];

    // Step 1: Initialize distance matrix with input graph
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            dist[i][j] = graph[i][j];
        }
    }

    // Step 2: Dynamic Programming -> update distances
    for (int k = 0; k < V; k++) {  // intermediate vertices
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Step 3: Print result
    printf("\nAll-Pairs Shortest Path Matrix:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                printf("%7s", "INF");
            else
                printf("%7d", dist[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int V;
    printf("Enter number of vertices: ");
    scanf("%d", &V);

    // Allocate memory for adjacency matrix
    int **graph = (int **)malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++) {
        graph[i] = (int *)malloc(V * sizeof(int));
    }

    printf("Enter adjacency matrix (use %d for INF):\n", INF);
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    floydWarshall(graph, V);

    // Free memory
    for (int i = 0; i < V; i++) {
        free(graph[i]);
    }
    free(graph);

    return 0;
}
