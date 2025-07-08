#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct lifo{
    char st[100];
    int top;
} stack;

void create(stack *s){
    s->top = -1;
}

void push(stack *s, char element){
    if(s->top==(99)){
        printf("Stack overflow\n");
        exit(-1);
    }
    s->st[++s->top] = element;
}

char pop(stack *s){
    if(s->top==-1){
        printf("Stack underflow\n");
        exit(-1);
    }
    return s->st[s->top--];
}

void parenMatching(char str[]){
    stack *s = (stack*) malloc(sizeof(stack));
    create(s);

    for(int i=0; i<strlen(str); i++){
        char curr = str[i];

        if(curr == '(' || curr == '{' || curr == '['){
            push(s, curr);
        }
        else if(curr == ')' || curr == '}' || curr == ']'){
            if((s->st[s->top] == '(' && curr != ')') || (s->st[s->top] == '{' && curr !='}') || (s->st[s->top] == '[' && curr != ']')){
                printf("The parentheses are not balanced.\n");
                return;
            }
            pop(s);
        }
    }

    if(s->top == -1){
        printf("The parentheses are balanced.\n");
    }
    else{
        printf("The parentheses are not balanced.\n");
    }
}

int main(){
    char s[100];
    scanf("%s", &s);

    parenMatching(s);

    return 0;
}