#include <stdio.h>
#include <string.h>

typedef struct
{
    int id;
    int deadline;
    int profit;
} Job;

void jobSequencing(Job jobs[], int n)
{
    int result[n];
    int slot[n];
    memset(result, -1, sizeof(result));
    memset(slot, 0, sizeof(slot));

    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (jobs[j].profit > jobs[i].profit)
            {
                Job temp = jobs[i];
                jobs[i] = jobs[j];
                jobs[j] = temp;
            }

    for (int i = 0; i < n; i++)
    {
        for (int j = (jobs[i].deadline < n ? jobs[i].deadline - 1 : n - 1); j >= 0; j--)
        {
            if (slot[j] == 0)
            {
                slot[j] = 1;
                result[j] = i;
                break;
            }
        }
    }

    printf("Scheduled jobs:\n");
    for (int i = 0; i < n; i++)
    {
        if (result[i] != -1)
            printf("Job%d ", jobs[result[i]].id);
    }
    printf("\n");
}

int main()
{
    Job jobs[] = {{1, 4, 20}, {2, 1, 10}, {3, 1, 40}, {4, 1, 30}};
    int n = sizeof(jobs) / sizeof(jobs[0]);

    jobSequencing(jobs, n);
    return 0;
}
