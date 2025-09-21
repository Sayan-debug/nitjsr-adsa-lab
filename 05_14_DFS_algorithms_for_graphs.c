#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int graph[MAX][MAX];  // adjacency matrix
int visited[MAX], discovery[MAX], finish[MAX];
int timeCounter = 0;

// DFS function
void DFS(int u, int V) {
    visited[u] = 1;
    discovery[u] = ++timeCounter;

    for (int v = 0; v < V; v++) {
        if (graph[u][v]) {
            if (visited[v] == 0) {
                printf("Tree Edge: %d -> %d\n", u, v);
                DFS(v, V);
            } 
            else if (visited[v] == 1) {
                printf("Back Edge: %d -> %d\n", u, v);
            } 
            else if (visited[v] == 2) {
                if (discovery[u] < discovery[v]) {
                    printf("Forward Edge: %d -> %d\n", u, v);
                } else {
                    printf("Cross Edge: %d -> %d\n", u, v);
                }
            }
        }
    }

    visited[u] = 2;
    finish[u] = ++timeCounter;
}

// Driver code
int main() {
    int V, E;

    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter number of edges: ");
    scanf("%d", &E);

    // Initialize graph
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            graph[i][j] = 0;
        }
        visited[i] = 0;
    }

    printf("Enter edges (u v) (0-indexed, directed graph):\n");
    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;  // directed graph
    }

    printf("\nDFS Edge Classification:\n");
    for (int i = 0; i < V; i++) {
        if (visited[i] == 0) {
            DFS(i, V);
        }
    }

    return 0;
}
