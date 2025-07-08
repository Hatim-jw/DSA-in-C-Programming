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

void bfs(int graph[5][5], int startNode){
    queue *front = NULL, *back = NULL;
    int visited[5] = {0};       //Makes all elements = 0

    enqueue(&front, &back, startNode);
    visited[startNode] = 1;     //Visited first node

    printf("BFS Traversal: ");
    while(!isEmpty(&front)){
        int node = dequeue(&front, &back);
        printf("%d ", node);

        for(int i=0; i<5; i++){
            if(graph[node][i]==1 && !visited[i]){
                enqueue(&front, &back, i);
                visited[i] = 1;
            }
        }
    }
    printf("\n");
}

int main(){
    int graph[5][5] = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 1, 0},
        {1, 1, 0, 0, 1},
        {0, 1, 0, 0, 1},
        {0, 0, 1, 1, 0}
    };

    bfs(graph, 0);

    return 0;
}