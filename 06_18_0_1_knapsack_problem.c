#include <stdio.h>
#include <stdlib.h>

// Function to get maximum of two numbers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Solves 0/1 Knapsack problem using DP
int knapsack(int W, int wt[], int val[], int n) {
    int dp[n + 1][W + 1];

    // Build DP table
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (wt[i - 1] <= w)
                dp[i][w] = max(val[i - 1] + dp[i - 1][w - wt[i - 1]], dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    // Print DP Table
    printf("\nDP Table:\n");
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            printf("%4d", dp[i][w]);
        }
        printf("\n");
    }

    // Trace back to show selected items
    printf("\nSelected items: ");
    int res = dp[n][W];
    int w = W;
    for (int i = n; i > 0 && res > 0; i--) {
        if (res != dp[i - 1][w]) {  // item was included
            printf("Item%d ", i);
            res -= val[i - 1];
            w -= wt[i - 1];
        }
    }
    printf("\n");

    return dp[n][W];
}

int main() {
    int n, W;

    printf("Enter number of items: ");
    scanf("%d", &n);

    int val[n], wt[n];

    printf("Enter values of items:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &val[i]);

    printf("Enter weights of items:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &wt[i]);

    printf("Enter knapsack capacity: ");
    scanf("%d", &W);

    int maxValue = knapsack(W, wt, val, n);

    printf("\nMaximum value in knapsack = %d\n", maxValue);

    return 0;
}