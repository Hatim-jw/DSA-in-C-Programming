#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int data;
    struct node *next;
    struct node *prev;
}node;

void enqueueR(node **front, node **back, int val){
    node *newNode = (node*) malloc(sizeof(node));
    newNode->data = val;
    newNode->next = NULL;
    newNode->prev = NULL;

    if(*front==NULL && *back==NULL){
        *front = *back = newNode;
        newNode->next = newNode;
        newNode->prev = newNode;
    }
    else{
        (*back)->next = newNode;
        newNode->prev = *back;
        newNode->next = *front;
        (*front)->prev = newNode;
        *back = newNode;
    }

}

void enqueueF(node **front, node **back, int val){
    node *newNode = (node*) malloc(sizeof(node));
    newNode->data = val;
    newNode->next = NULL;
    newNode->prev = NULL;

    if(*front==NULL && *back==NULL){
        *front = *back = newNode;
        newNode->next = newNode;
        newNode->prev = newNode;
    }
    else{
        newNode->next = *front;
        (*front)->prev = newNode;
        newNode->prev = *back;
        (*back)->next = newNode;
        *front = newNode;
    }

}

int dequeueF(node **front, node **back){
    if(*front == NULL){
        printf("Queue underflow.\n");
        exit(-1);
    }
    else{
        int val = (*front)->data;
        node *temp = *front;

        if(*front == *back){
            *front = *back = NULL;
        }
        else{
            *front = (*front)->next;
            (*front)->prev = *back;
            (*back)->next = *front;
        }

        free(temp);
        return val;
    }
}
int dequeueR(node **front, node **back){
    if(*back == NULL){
        printf("Queue underflow.\n");
        exit(-1);
    }
    else{
        int val = (*back)->data;
        node *temp = *back;

        if(*front == *back){
            *front = *back = NULL;
        }
        else{
            *back = (*back)->prev;
            (*back)->next = *front;
            (*front)->prev = *back;
        }

        free(temp);
        return val;
    }
}

int *SlidingWindow(int arr[], int size, int win_size){
    node *dequeFront = NULL, *dequeBack = NULL;

    for(int i=0; i<size; i++){
        while(dequeFront!=NULL && dequeFront->data <= i-win_size){
            dequeueF(&dequeFront, &dequeBack);
        }

        while(dequeFront!=NULL && arr[dequeBack->data] < arr[i]){
            dequeueR(&dequeFront, &dequeBack);
        }

        enqueueR(&dequeFront, &dequeBack, i);

        if(i >= win_size-1){
            printf("%d, ", arr[dequeFront->data]);
        }
    }
}

int main(){
    int n;
    printf("Enter no. of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter the elements of array: ");
    for(int i=0; i<n; i++){
        scanf("%d", &arr[i]);
    }

    int k;
    printf("Enter the window size: ");
    scanf("%d", &k);

    printf("Maximum in each sliding window of size %d: {", k);
    SlidingWindow(arr, n, k);
    printf("\b\b");
    printf("}\n");

    return 0;
}