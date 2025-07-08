#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int data;
    struct node *next;
}stack;

stack *createStack(int val){
    stack *newNode = (stack*) malloc(sizeof(stack));
    newNode->data = val;
    newNode->next = NULL;
    return newNode;
}

void push(stack **top, int val){
    stack *newNode = createStack(val);
    newNode->next = *top;
    *top = newNode;
}

int pop(stack** top){
    if(*top == NULL){
        printf("Stack underflow.\n");
        exit(-1);
    }

    int t = (*top)->data;
    stack *p = *top;
    *top = (*top)->next;
    free(p);
    return t;
}

int isEmpty(stack **top){
    return(*top == NULL);
}

void printReverse(int arr[], int low, int high){
    stack *s = createStack(high);
    push(&s, low);
    push(&s, high);

    while(!isEmpty(&s)){
        int h = pop(&s);
        int l = pop(&s);

        if(l == h){
            printf("%d ", arr[l]);
        }
        else{
            int m = l+(h-l)/2;
            push(&s, l); push(&s, m);
            push(&s, m+1); push(&s, h);
        }
    }
}

int main(){
    int arr[] = {1, 2, 3, 4, 5};

    printReverse(arr, 0, 4);

    return 0;
}