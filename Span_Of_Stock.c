#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int element;
    struct node *next;
}stack;

stack *push(stack *top, int element){
    stack *newNode = (stack*) malloc(sizeof(stack));
    newNode->element = element;

    if(top == NULL){
        newNode->next = NULL;
        top = newNode;
        return top;
    }

    newNode->next = top;
    top = newNode;
    return top;
}

stack *pop(stack *top){
    stack *p = top;
    top = top->next;
    p->next = NULL;
    free(p);
    return top;
}

void calculateSpan(int price[], int size){
    stack *s = NULL;
    int span[size];
    span[0] = 1;
    s = push(s, 0);

    for(int i=1; i<size; i++){
        while(s!=NULL && price[s->element]<=price[i]){
            s = pop(s);
        }

        if(s == NULL)   span[i] = i+1;
        else    span[i] = i - s->element;

        s = push(s, i);
    }

    printf("Stock spans: ");
    for(int i=0; i<size; i++){
        printf("%d ", span[i]);
    }
    printf("\n");
}

int main(){
    int n;
    printf("Enter no. of prices: ");
    scanf("%d", &n);

    int prices[n];
    printf("Enter prices: ");
    for(int i=0; i<n; i++){
        scanf("%d", &prices[i]);
    }

    calculateSpan(prices, n);

    return 0;
}