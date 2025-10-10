#include <stdio.h>
#define MAX 100

int graph[MAX][MAX], visited[MAX], stack[MAX], top = -1;
int V;

void dfs(int u)
{
    visited[u] = 1;
    for (int v = 0; v < V; v++)
    {
        if (graph[u][v] && !visited[v])
        {
            dfs(v);
        }
    }
    stack[++top] = u;
}

void topologicalSort()
{
    for (int i = 0; i < V; i++)
        visited[i] = 0;
    top = -1;

    for (int i = 0; i < V; i++)
    {
        if (!visited[i])
            dfs(i);
    }

    printf("Topological order:\n");
    for (int i = top; i >= 0; i--)
        printf("%d ", stack[i]);
    printf("\n");
}

int main()
{
    V = 6;

    graph[5][2] = 1;
    graph[5][0] = 1;
    graph[4][0] = 1;
    graph[4][1] = 1;
    graph[2][3] = 1;
    graph[3][1] = 1;

    topologicalSort();
    return 0;
}
