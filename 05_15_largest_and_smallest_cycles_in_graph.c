#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

int graph[MAX][MAX];
int visited[MAX];
int stack[MAX];
int top = -1;
int minCycle = MAX, maxCycle = -1;
int V, E;
int isDirected; // 1 for directed, 0 for undirected

// DFS with cycle detection
void DFS(int u, int parent) {
    visited[u] = 1;
    stack[++top] = u;

    for (int v = 0; v < V; v++) {
        if (graph[u][v]) {
            if (!visited[v]) {
                DFS(v, u);
            } else {
                // Check if v is in the stack (cycle found)
                for (int i = 0; i <= top; i++) {
                    if (stack[i] == v) {
                        int cycleLength = top - i + 1;
                        if (cycleLength > 1) {
                            if (cycleLength < minCycle) minCycle = cycleLength;
                            if (cycleLength > maxCycle) maxCycle = cycleLength;
                        }
                        break;
                    }
                }
            }
        }
    }

    top--;
    visited[u] = 2;
}

int main() {
    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter number of edges: ");
    scanf("%d", &E);

    printf("Is the graph directed? (1=Yes, 0=No): ");
    scanf("%d", &isDirected);

    // Initialize graph
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            graph[i][j] = 0;
        }
        visited[i] = 0;
    }

    printf("Enter edges (u v) (0-indexed):\n");
    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
        if (!isDirected) graph[v][u] = 1; // for undirected
    }

    // Run DFS from every unvisited node
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            DFS(i, -1);
        }
    }

    if (maxCycle == -1) {
        printf("No cycles found in the graph.\n");
    } else {
        printf("Smallest Cycle Length = %d\n", minCycle);
        printf("Largest Cycle Length = %d\n", maxCycle);
    }

    return 0;
}
