#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10

int n;
int dist[MAX][MAX];
int visited[MAX];
int min_cost = 1e9;

void tsp(int pos, int count, int cost)
{
    if (count == n && dist[pos][0])
    {
        if (cost + dist[pos][0] < min_cost)
            min_cost = cost + dist[pos][0];
        return;
    }

    for (int i = 0; i < n; i++)
    {
        if (!visited[i] && dist[pos][i])
        {
            visited[i] = 1;
            tsp(i, count + 1, cost + dist[pos][i]);
            visited[i] = 0;
        }
    }
}

int main()
{
    n = 10;
    srand(0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dist[i][j] = (i == j) ? 0 : (rand() % 100 + 1);

    clock_t start = clock();
    visited[0] = 1;
    tsp(0, 1, 0);
    clock_t end = clock();

    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("TSP minimum cost: %d\n", min_cost);
    printf("Execution time for %d nodes: %f seconds\n", n, time_taken);

    return 0;
}
