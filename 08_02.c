#include <stdio.h>
#define MAXN 20

int n = 5, e = 6;
int adj[MAXN][MAXN];
int path[MAXN];
int visited[MAXN];

int can_add(int v, int pos)
{
    if (!adj[path[pos - 1]][v])
        return 0;
    if (visited[v])
        return 0;
    return 1;
}

int hamiltonian(int pos)
{
    if (pos == n)
        return adj[path[pos - 1]][path[0]];

    for (int v = 1; v < n; v++)
    {
        if (can_add(v, pos))
        {
            path[pos] = v;
            visited[v] = 1;
            if (hamiltonian(pos + 1))
                return 1;
            visited[v] = 0;
        }
    }
    return 0;
}

int main()
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            adj[i][j] = 0;

    int edges[][2] = {
        {0, 1},
        {1, 2},
        {2, 3},
        {3, 4},
        {4, 0},
        {1, 3}};

    for (int i = 0; i < e; i++)
    {
        int u = edges[i][0], v = edges[i][1];
        adj[u][v] = adj[v][u] = 1;
    }

    for (int i = 0; i < n; i++)
        visited[i] = 0;
    path[0] = 0;
    visited[0] = 1;

    if (hamiltonian(1))
    {
        printf("Hamiltonian cycle exists:\n");
        for (int i = 0; i < n; i++)
            printf("%d ", path[i]);
        printf("%d\n", path[0]);
    }
    else
    {
        printf("No Hamiltonian cycle found\n");
    }

    return 0;
}