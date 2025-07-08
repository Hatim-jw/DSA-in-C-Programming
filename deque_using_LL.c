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

int isEmpty(node **front){
    return(*front == NULL);
}

int main(){
    node *front = NULL, *back = NULL;

    int x = isEmpty(&front);
    printf("%d\n", x);

    enqueueF(&front, &back, 13);
    enqueueR(&front, &back, 14);
    enqueueF(&front, &back, 12);

    printf("Dequeued value: %d\n", dequeueF(&front, &back));
    printf("Dequeued value: %d\n", dequeueR(&front, &back));
    printf("Dequeued value: %d\n", dequeueR(&front, &back));
    printf("Dequeued value: %d\n", dequeueF(&front, &back));

    return 0;
}