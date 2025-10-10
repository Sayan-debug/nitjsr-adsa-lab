#include <stdio.h>
#define V 4

int graph[V][V] = {
    {0, 1, 1, 1},
    {1, 0, 1, 0},
    {1, 1, 0, 1},
    {1, 0, 1, 0}};

int colors[V];

int isSafe(int v, int c)
{
    for (int i = 0; i < V; i++)
        if (graph[v][i] && colors[i] == c)
            return 0;
    return 1;
}

int graphColoring(int v, int m)
{
    if (v == V)
        return 1;

    for (int c = 1; c <= m; c++)
    {
        if (isSafe(v, c))
        {
            colors[v] = c;
            if (graphColoring(v + 1, m))
                return 1;
            colors[v] = 0;
        }
    }
    return 0;
}

int main()
{
    int m = 3;

    for (int i = 0; i < V; i++)
        colors[i] = 0;

    if (graphColoring(0, m))
    {
        printf("Solution Exists: Following are the assigned colors:\n");
        for (int i = 0; i < V; i++)
            printf("Vertex %d ---> Color %d\n", i, colors[i]);
    }
    else
    {
        printf("No solution exists with %d colors.\n", m);
    }
    return 0;
}
