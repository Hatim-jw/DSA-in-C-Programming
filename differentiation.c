#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int coeff,exp;
    struct node *next;
}node;

node *insertNode(node* head, int coeff, int exp){
    node *newNode = (node*) malloc(sizeof(node));
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = NULL;

    if(head == NULL){
        head = newNode;
        return head;
    }

    if(head->exp<newNode->exp){
        newNode->next = head;
        head = newNode;
        return head;
    }

    if(head->exp == newNode->exp){
        head->coeff+=newNode->coeff;
        return head;
    }

    node *temp = head;
    while(temp->next!=NULL && temp->next->exp>newNode->exp){
        temp = temp->next;
    }

    if(temp->next!=NULL && temp->next->exp==newNode->exp){
        temp->next->coeff+=newNode->coeff;
        return head;
    }

    newNode->next = temp->next;
    temp->next = newNode;
    return head;
}

node *insertIncrOrder(node *head, int coeff, int exp){
    node *newNode = (node*) malloc(sizeof(node));
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = NULL;

    if(head == NULL){
        head = newNode;
        return head;
    }

    if(head->exp>newNode->exp){
        newNode->next = head;
        head = newNode;
        return head;
    }

    if(head->exp == newNode->exp){
        head->coeff+=newNode->coeff;
        return head;
    }

    node *temp = head;
    while(temp->next!=NULL && temp->next->exp<newNode->exp){
        temp = temp->next;
    }

    if(temp->next!=NULL && temp->next->exp==newNode->exp){
        temp->next->coeff+=newNode->coeff;
        return head;
    }

    newNode->next = temp->next;
    temp->next = newNode;
    return head;
}

node *derivative(node *head){
    node *result = NULL;
    node *temp = head;

    while(temp!=NULL){
        result = insertIncrOrder(result, (temp->exp*temp->coeff), (temp->exp)-1);
        temp = temp->next;
    }

    return result;
}

void displayPoly(node *head){
    node *temp = head;

    if((temp->coeff)<0){
        printf("-");
    }

    while(temp!=NULL){
        if(temp->coeff!=0){
            if(temp->exp>1){
                if(temp->coeff>0){
                    printf("%dx^%d", temp->coeff, temp->exp);
                }
                else{
                    printf("%dx^%d", -temp->coeff, temp->exp);
                }
            }
            else if(temp->exp==1){
                if(temp->coeff>0){
                    printf("%dx", temp->coeff);
                }
                else{
                    printf("%dx", -temp->coeff);
                }
            }
            else{
                if(temp->coeff>0){
                    printf("%d", temp->coeff);
                }
                else{
                    printf("%d", -temp->coeff);
                }
            }
        }

        if(temp->next!=NULL && temp->next->coeff>0){
            printf(" + ");
        }
        else if(temp->next!=NULL && temp->next->coeff<0){
            printf(" - ");
        }

        temp = temp->next;
    }
}

int main(){
    node *poly = NULL;
    int n;
    printf("Enter no. of terms: ");
    scanf("%d", &n);

    printf("Enter terms of polynomial:\n");
    for(int i=0; i<n; i++){
        int coeff, exp;
        scanf("%d %d", &coeff, &exp);
        poly = insertNode(poly, coeff, exp);
    }

    printf("Given polynomial is: ");
    displayPoly(poly);
    printf("\n");

    node *Derivative = derivative(poly);

    printf("After differentiation, function is: ");
    displayPoly(Derivative);
    printf("\n");

    return 0;
}