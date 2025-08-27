#include<stdio.h>
#include<stdlib.h>

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}
void merge(int arr[],int low,int mid,int high){
    int n1 = mid-low+1;
    int n2 = high-mid;
    int a1[n1];
    int a2[n2];

    for(int i=0;i<n1;i++){
        a1[i] = arr[low+i];
    }
    for(int i=0;i<n2;i++){
        a2[i] = arr[mid+1+i];
    }

    int i=0,j=0,k=low;

    while(i<n1&&j<n2){
        if(a1[i]<=a2[j]){
            arr[k] = a1[i];
            k++;
            i++;
        }
        else{
            arr[k] = a2[j];
            k++;
            j++;
        }
    }
    while(i<n1){
        arr[k] = a1[i];
        k++;
        i++;
    }
    while(j<n2){
        arr[k] = a2[j];
        k++;
        j++;
    }
}

void mergesort(int arr[],int start,int end){

    if(start>=end){
        return;
    }
    int low = start;
    int high = end;
    int mid = (high+low)/2;
    mergesort(arr, low, mid);
    mergesort(arr, mid+1,high);
    merge(arr,low,mid,high);
}

void bubblesort(int arr[],int n){
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(arr[j]>arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
    
        int min_idx = i;
        
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
              
                min_idx = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;
    }
}
void insertionSort(int arr[], int N) {

    for (int i = 1; i < N; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }

        arr[j + 1] = key;
    }
}
void shellSort(int array[], int n) {
  for (int interval = n / 2; interval > 0; interval /= 2) {
    for (int i = interval; i < n; i += 1) {
      int temp = array[i];
      int j;
      for (j = i; j >= interval && array[j - interval] > temp; j -= interval) {
        array[j] = array[j - interval];
      }
      array[j] = temp;
    }
  }
}

void heapify(int arr[], int n, int i)
{
    int temp, maximum, left_index, right_index;

    maximum = i;
    right_index = 2 * i + 2;

    left_index = 2 * i + 1;
    if (left_index < n && arr[left_index] > arr[maximum])
        maximum = left_index;

    if (right_index < n && arr[right_index] > arr[maximum])
        maximum = right_index;

    // checking if we needed swaping the elements or not
    if (maximum != i) {
        temp = arr[i];
        arr[i] = arr[maximum];
        arr[maximum] = temp;
        heapify(arr, n, maximum);
    }
}

// HeapSorting function
void heapsort(int arr[], int n)
{
    int i, temp;
    for (i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    // the current array is changed to max heap

    for (i = n - 1; i > 0; i--) {
        temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}
int partition(int arr[], int low, int high) {
    
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);  
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
int main(){
    //meregesort
    int n;
    printf("Enter the size: ");
    scanf("%d",&n);
    int arr[1000];
    printf("Enter the array elements : \n");
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    int choice;
    printf("\n--List of sorting algorithm--\n");
    printf("\n1.Bubble sort\n2.Merge sort\n3.Insertion sort\n4.Quick sort\n5.Selection sort\n6.Heap sort\n7.Shell sort\n");
    printf("Enter the choice : ");
    scanf("%d",&choice);
    switch (choice)
    {
    case 1:
        /* code */bubblesort(arr,n);
        break;
    case 2:
        /* code */mergesort(arr,0,n-1);
        break;
    case 3:
        /* code */insertionSort(arr,n);
        break;
    case 4:
        /* code */quickSort(arr,0,n-1);
        break;
    case 5:
        /* code */selectionSort(arr,n);
        break;
    case 6:
        /* code */heapsort(arr,n);
        break;
    case 7:
        shellSort(arr,n);
        break;
    default:
        break;
    }
    printf("Array elements after sorting : \n");
    for(int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
    //free(arr);
}