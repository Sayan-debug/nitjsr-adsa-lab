#include <stdio.h>
#include <stdlib.h>

int n;              // number of items
int W;              // capacity of knapsack
int *val, *wt;      // arrays for values and weights
int maxValue = 0;   // best solution found
int *bestSet;       // stores best subset of items
int *currSet;       // stores current subset of items

// Backtracking function
void knapsackBT(int i, int currWeight, int currValue) {
    if (currWeight > W) {
        return; // invalid path, backtrack
    }

    if (i == n) {  // reached all items
        if (currValue > maxValue) {
            maxValue = currValue;
            for (int k = 0; k < n; k++) {
                bestSet[k] = currSet[k];
            }
        }
        return;
    }

    // Choice 1: Exclude item i
    currSet[i] = 0;
    knapsackBT(i + 1, currWeight, currValue);

    // Choice 2: Include item i
    currSet[i] = 1;
    knapsackBT(i + 1, currWeight + wt[i], currValue + val[i]);
}

int main() {
    printf("Enter number of items: ");
    scanf("%d", &n);

    val = (int*)malloc(n * sizeof(int));
    wt = (int*)malloc(n * sizeof(int));
    bestSet = (int*)malloc(n * sizeof(int));
    currSet = (int*)malloc(n * sizeof(int));

    printf("Enter values of items:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &val[i]);

    printf("Enter weights of items:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &wt[i]);

    printf("Enter knapsack capacity: ");
    scanf("%d", &W);

    knapsackBT(0, 0, 0);

    printf("\nMaximum value in knapsack = %d\n", maxValue);
    printf("Selected items:\n");
    for (int i = 0; i < n; i++) {
        if (bestSet[i] == 1)
            printf("Item%d (value=%d, weight=%d)\n", i+1, val[i], wt[i]);
    }

    // Free memory
    free(val);
    free(wt);
    free(bestSet);
    free(currSet);

    return 0;
}