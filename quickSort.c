#include<stdio.h>

void swap(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

int partition(int arr[], int l, int h){
    int x = arr[l];
    int i = l-1;
    int j = h+1;

    while(1){
        do{
            j--;
        }while(arr[j] > x);
        do{
            i++;
        }while(arr[i] < x);
        
        if(i < j){
            swap(&arr[i], &arr[j]);
        }
        else{
            return j;
        }
    }
}

void quickSort(int arr[], int l, int h){
    if(l < h){
        int q = partition(arr, l, h);

        quickSort(arr, l, q);
        quickSort(arr, q+1, h);
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

    quickSort(a, 0, n-1);

    printf("\nSorted array: ");
    for(int i=0; i<n; i++){
        printf("%d ", a[i]);
    }
    printf("\n");

    return 0;
}