#include<stdio.h>
#include<time.h>

void insertion_sort(int arr[], int size){
    for(int i=1; i<size; i++){
        int key = arr[i];
        int j = i-1;

        while((key < arr[j]) && (j>=0)){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
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

    insertion_sort(a, n);

    printf("\nSorted array: ");
    for(int i=0; i<n; i++){
        printf("%d ", a[i]);
    }
    printf("\n");

    return 0;
}