#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct Node
{
    int v;
    struct Node *next;
} Node;

Node *graph[MAX];
int time = 0;

void addEdge(int u, int v, int directed)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->v = v;
    node->next = graph[u];
    graph[u] = node;
    if (!directed)
    {
        node = (Node *)malloc(sizeof(Node));
        node->v = u;
        node->next = graph[v];
        graph[v] = node;
    }
}

int discSCC[MAX], lowSCC[MAX], stackMember[MAX], stackSCC[MAX];
int topSCC = -1;
int timeSCC = 0;

void SCCUtil(int u)
{
    discSCC[u] = lowSCC[u] = ++timeSCC;
    stackSCC[++topSCC] = u;
    stackMember[u] = 1;

    for (Node *temp = graph[u]; temp; temp = temp->next)
    {
        int v = temp->v;
        if (!discSCC[v])
        {
            SCCUtil(v);
            if (lowSCC[v] < lowSCC[u])
                lowSCC[u] = lowSCC[v];
        }
        else if (stackMember[v] && discSCC[v] < lowSCC[u])
        {
            lowSCC[u] = discSCC[v];
        }
    }

    if (lowSCC[u] == discSCC[u])
    {
        printf("SCC: ");
        int w;
        do
        {
            w = stackSCC[topSCC--];
            stackMember[w] = 0;
            printf("%d ", w);
        } while (w != u);
        printf("\n");
    }
}

void findSCCs(int V)
{
    memset(discSCC, 0, sizeof(discSCC));
    memset(lowSCC, 0, sizeof(lowSCC));
    memset(stackMember, 0, sizeof(stackMember));
    topSCC = -1;
    timeSCC = 0;

    for (int i = 0; i < V; i++)
        if (!discSCC[i])
            SCCUtil(i);
}

int discBCC[MAX], lowBCC[MAX], parentBCC[MAX], timeBCC = 0;
int ap[MAX];

typedef struct Edge
{
    int u, v;
} Edge;

Edge stackEdges[MAX * MAX];
int topEdges = -1;

void pushEdge(int u, int v)
{
    stackEdges[++topEdges].u = u;
    stackEdges[topEdges].v = v;
}

void popBCC(int u, int v)
{
    printf("Biconnected Component: ");
    Edge e;
    do
    {
        e = stackEdges[topEdges--];
        printf("(%d-%d) ", e.u, e.v);
    } while (!(e.u == u && e.v == v));
    printf("\n");
}

void BCCUtil(int u)
{
    discBCC[u] = lowBCC[u] = ++timeBCC;
    int children = 0;
    for (Node *temp = graph[u]; temp; temp = temp->next)
    {
        int v = temp->v;
        if (!discBCC[v])
        {
            children++;
            parentBCC[v] = u;
            pushEdge(u, v);
            BCCUtil(v);

            if (lowBCC[v] >= discBCC[u])
            {
                ap[u] = 1;
                popBCC(u, v);
            }

            if (lowBCC[v] < lowBCC[u])
                lowBCC[u] = lowBCC[v];
        }
        else if (v != parentBCC[u] && discBCC[v] < lowBCC[u])
        {
            lowBCC[u] = discBCC[v];
            pushEdge(u, v);
        }
    }
}

void findBCCsAPBridges(int V)
{
    memset(discBCC, 0, sizeof(discBCC));
    memset(lowBCC, 0, sizeof(lowBCC));
    memset(parentBCC, -1, sizeof(parentBCC));
    memset(ap, 0, sizeof(ap));
    topEdges = -1;
    timeBCC = 0;

    for (int i = 0; i < V; i++)
        if (!discBCC[i])
            BCCUtil(i);

    printf("Articulation Points: ");
    for (int i = 0; i < V; i++)
        if (ap[i])
            printf("%d ", i);
    printf("\n");
}

int main()
{
    int V = 5;

    for (int i = 0; i < MAX; i++)
        graph[i] = NULL;

    addEdge(1, 0, 1);
    addEdge(0, 2, 1);
    addEdge(2, 1, 1);
    addEdge(0, 3, 1);
    addEdge(3, 4, 1);

    printf("Strongly Connected Components:\n");
    findSCCs(5);

    for (int i = 0; i < MAX; i++)
    {
        while (graph[i])
        {
            Node *temp = graph[i];
            graph[i] = graph[i]->next;
            free(temp);
        }
    }

    addEdge(0, 1, 0);
    addEdge(1, 2, 0);
    addEdge(2, 0, 0);
    addEdge(1, 3, 0);
    addEdge(3, 4, 0);

    printf("\nBiconnected Components, Articulation Points:\n");
    findBCCsAPBridges(5);

    return 0;
}
