#include <stdio.h>

void coinChange(int coins[], int n, int amount)
{
    printf("Coins used to make %d:\n", amount);
    for (int i = 0; i < n; i++)
    {
        while (amount >= coins[i])
        {
            amount -= coins[i];
            printf("%d ", coins[i]);
        }
    }
    printf("\n");
}

int main()
{
    int n, amount;

    printf("Enter number of coin denominations: ");
    scanf("%d", &n);

    int coins[n];
    printf("Enter coin denominations in descending order:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &coins[i]);
    }

    printf("Enter amount: ");
    scanf("%d", &amount);

    coinChange(coins, n, amount);

    return 0;
}
