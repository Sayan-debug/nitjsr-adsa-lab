#include <stdio.h>

#define MAXN 20

int n, e, m;
int adj[MAXN][MAXN];

int is_clique(int subset[], int size)
{
    for (int i = 0; i < size; i++)
        for (int j = i + 1; j < size; j++)
            if (!adj[subset[i]][subset[j]])
                return 0;
    return 1;
}

int find_clique(int start, int depth, int subset[])
{
    if (depth == m)
    {
        if (is_clique(subset, m))
            return 1;
        return 0;
    }
    for (int i = start; i < n; i++)
    {
        subset[depth] = i;
        if (find_clique(i + 1, depth + 1, subset))
            return 1;
    }
    return 0;
}

int main()
{
    printf("Enter number of vertices (n), edges (e), clique size (m): ");
    scanf("%d %d %d", &n, &e, &m);

    if (m > n)
    {
        printf("Clique size m cannot be greater than number of vertices n.\n");
        return 0;
    }
    if (n > MAXN)
    {
        printf("Maximum number of vertices supported is %d.\n", MAXN);
        return 0;
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            adj[i][j] = 0;

    printf("Enter edges (u v) with vertices numbered from 0 to %d:\n", n - 1);
    for (int i = 0; i < e; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        if (u < 0 || u >= n || v < 0 || v >= n)
        {
            printf("Invalid edge (%d, %d), vertices out of range.\n", u, v);
            i--;
            continue;
        }
        adj[u][v] = adj[v][u] = 1;
    }

    int subset[MAXN];
    if (find_clique(0, 0, subset))
        printf("Graph contains a clique of size %d\n", m);
    else
        printf("No clique of size %d found\n", m);

    return 0;
}