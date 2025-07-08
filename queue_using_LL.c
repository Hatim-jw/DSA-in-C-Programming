#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int value;
    struct node *next;
}queue;

void enqueue(queue **front, queue **back, int value){
    queue *newNode = (queue*) malloc(sizeof(queue));
    newNode->value = value;
    newNode->next = NULL;

    if(*front==NULL && *back==NULL){
        *front = *back = newNode;
    }
    else{
        (*back)->next = newNode;
        *back = newNode;
    }
}

int dequeue(queue **front, queue **back){
    if(*front == NULL){
        printf("Queue underflow.\n");
        exit(-1);
    }
    else{
        int val = (*front)->value;
        queue *temp = *front;
        *front = (*front)->next;

        if(*front == NULL){
            *back = NULL;
        }
        free(temp);
        return val;
    }
}

int isEmpty(queue **front){
    return(*front == NULL);
}

int main(){
    queue *front = NULL, *back = NULL;

    int x = isEmpty(&front);
    printf("%d\n", x);

    enqueue(&front, &back, 12);
    enqueue(&front, &back, 13);
    enqueue(&front, &back, 14);

    printf("Dequeued value: %d\n", dequeue(&front, &back));
    printf("Dequeued value: %d\n", dequeue(&front, &back));
    printf("Dequeued value: %d\n", dequeue(&front, &back));
    printf("Dequeued value: %d\n", dequeue(&front, &back));

    return 0;
}