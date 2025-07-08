#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node{
    char element;
    struct node* next;
}stack;

void create(stack *top){
    top = NULL;
}

stack *push(stack *top, char element){
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

int precedence(char c){
    if(c=='+' || c=='-')    return 1;
    else if(c=='*' || c=='/')   return 2;
    else if(c=='^')     return 3;
    else    return 0;
}

void Infix_To_Postfix(char *infix){
    stack *s;
    create(s);
    char postfix[100];
    int j=0;

    for(int i=0; infix[i]!='\0'; i++){
        char curr = infix[i];

        if((curr>='a' && curr<='z') || (curr>='A' && curr<='Z') || (curr>'0' && curr<='9')){
            postfix[j++] = curr;
        }
        else if(curr == '('){
            s = push(s, curr);
        }
        else if(curr == ')'){
            while(s->element!='('){
                postfix[j++] = s->element;
                s = pop(s);
            }
            s = pop(s);
        }
        else{
            while(s!=NULL && precedence(curr)<=precedence(s->element)){
                postfix[j++] = s->element;
                s = pop(s);
            }
            s = push(s, curr);
        }
    }

    while(s!=NULL){
        postfix[j++] = s->element;
        s = pop(s);
    }
    postfix[j] = '\0';

    printf("Postfix expression: ");
    for(int i=0; postfix[i]!='\0'; i++){
        printf("%c", postfix[i]);
    }
    printf("\n");
}

int main(){
    char infix[100];
    printf("Enter infix expression: ");
    fgets(infix, 100, stdin);
    infix[strcspn(infix, "\n")] = '\0';

    Infix_To_Postfix(infix);

    return 0;
}