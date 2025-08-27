#include <stdio.h>
#include<stdlib.h>
int main() {
    int rows, cols;
    printf("Enter number of rows: ");
    scanf("%d", &rows);
    printf("Enter number of columns: ");
    scanf("%d", &cols);

    int **arr = (int**)malloc(rows * sizeof(int*));
    for(int i=0;i<rows;i++){
        arr[i] = (int*)malloc(cols * sizeof(int));
    }
    
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            arr[i][j] = 0;
        }
    }

    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            printf("Enter the value of matrix[%d][%d] : ",i+1,j+1);
            scanf("%d",&arr[i][j]);
        }
    }

    // Print array
    printf("\nFinal 2D Array:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d\t", arr[i][j]);
        }
        printf("\n");
    }

    for(int i=0;i<rows;i++){
        free(arr[i]);
    }
    free(arr);

    return 0;
}