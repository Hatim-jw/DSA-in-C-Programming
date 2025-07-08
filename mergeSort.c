#include<stdio.h>
#include<math.h>

void merge(int arr[], int l, int mid, int h){
    int l_arr[mid-l+2], r_arr[h-mid+1];
    l_arr[mid-l+1] = r_arr[h-mid] = (int)INFINITY;
    
    for(int i=0; i<=mid-l; i++){
        l_arr[i] = arr[l+i];
    }
    for(int i=0; i<h-mid; i++){
        r_arr[i] = arr[mid+1+i];
    }
    
    int i = 0, j = 0;
    for(int k=l; k<=h; k++){
        if(l_arr[i] <= r_arr[j]){
            arr[k] = l_arr[i];
            i++;
        }
        else{
            arr[k] = r_arr[j];
            j++;
        }
    }
}

void mergeSort(int arr[], int l, int h){
    if(l < h){
        int mid = (l+h)/2;

        mergeSort(arr, l, mid);
        mergeSort(arr, mid+1, h);
        merge(arr, l, mid, h);
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

    mergeSort(a, 0, n-1);

    printf("\nSorted array: ");
    for(int i=0; i<n; i++){
        printf("%d ", a[i]);
    }
    printf("\n");

    return 0;
}