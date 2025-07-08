#include<stdio.h>

int min_loc(int arr[], int k, int size){
    int pos = k;
    for(int i=k+1; i<size; i++){
        if(arr[pos] > arr[i]){
            pos = i;
        }
    }
    return pos;
}

void swap(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

void sel_sort(int arr[], int size){
    for(int i=0; i<size-1; i++){
        int m = min_loc(arr, i, size);
        if(m != i){
            swap(&arr[m], &arr[i]);
        }
    }
}

int main(){
    int n;
    printf("\nEnter size of array: ");
    scanf("%d", &n);

    int a[n];
    printf("Enter the elements of array: ");
    for(int i=0; i<n; i++){
        scanf("%d", &a[i]);
    }

    sel_sort(a, n);

    printf("\nSorted array: ");
    for(int i=0; i<n; i++){
        printf("%d ", a[i]);
    }
    printf("\n");

    return 0;
}