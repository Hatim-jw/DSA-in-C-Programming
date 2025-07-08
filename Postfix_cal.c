#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct lifo{
    int st[100];
    int top;
} stack;

void create(stack *s){
    s->top = -1;
}

void push(stack *s, int element){
    if(s->top==(99)){
        printf("Stack overflow\n");
        exit(-1);
    }
    s->st[++s->top] = element;
}

int pop(stack *s){
    if(s->top==-1){
        printf("Stack underflow\n");
        exit(-1);
    }
    return s->st[s->top--];
}

void Calculate_postfix(char str[]){
    stack *s = (stack*) malloc(sizeof(stack));
    create(s);

    for(int i=0; i<strlen(str); i++){
        char curr = str[i];

        if(curr > '0' && curr <= '9'){
            int num = curr - '0';
            push(s, num);
        }
        else{
            int arg2 = pop(s);
            int arg1 = pop(s);
            
            if(curr == '+'){
                push(s, arg1+arg2);
            }
            else if(curr == '-'){
                push(s, arg1-arg2);
            }
            else if(curr == '*'){
                push(s, arg1*arg2);
            }
            else{
                push(s, arg1/arg2);
            }
        }
    }

    int eval = pop(s);
    printf("Answer = %d", eval);
}

int main(){
    char s[100];
    printf("Enter expression to be calculated: ");
    fgets(s, sizeof(s), stdin);
    s[strcspn(s, "\n")] = '\0';

    Calculate_postfix(s);

    return 0;
}