#include<stdio.h>

void swap(int *x, int *y){
    *x = *x ^ *y;
    *y = *x ^ *y;
    *x = *x ^ *y;
}

void bubble_sort(int arr[], int size){
    for(int i=size-1; i>0; i--){
        int flag = 0;
        for(int j=0; j<i; j++){
            if(arr[j] > arr[j+1]){
                swap(&arr[j], &arr[j+1]);
                flag = j;
            }
        }
        if(flag == 0){
            break;
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

    bubble_sort(a, n);

    printf("\nSorted array: ");
    for(int i=0; i<n; i++){
        printf("%d ", a[i]);
    }
    printf("\n");

    return 0;
}