#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct Node{
    int row, col, val;
    struct Node* next;
} Node;

Node *createNode(int row, int col, int val){
    Node *newNode = (Node*) malloc(sizeof(Node));
    newNode->row = row;
    newNode->col = col;
    newNode->val = val;
    newNode->next = NULL;
    return newNode;
}

Node *insertNode(Node *head, int row, int col, int val) {
    Node *newNode = createNode(row, col, val);
    Node *temp = head;

    while (temp->next != NULL && 
           (temp->next->row < row || 
            (temp->next->row == row && temp->next->col < col))) {
        temp = temp->next;
    }

    newNode->next = temp->next;
    temp->next = newNode;

    return head;
}


Node *inputSparse(Node *head){
    int rows,cols,n;
    printf("Enter the size of the sparse matrix: ");
    scanf("%d %d", &rows, &cols);
    printf("Enter the no. of non-zero elements: ");
    scanf("%d", &n);
    head = createNode(rows, cols, n);

    printf("Enter the non-zero elements in the format(Row Col Value):\n");
    for(int i=0; i<head->val; i++){
        int row, col, value;
        scanf("%d %d %d", &row, &col, &value);
        head = insertNode(head, row, col, value);
    }
    return head;
}

void displaySparse(Node *head){
    Node *temp = head->next;
    while(temp!=NULL){
        printf("Row: %d, Column: %d, Value: %d\n", temp->row, temp->col, temp->val);
        temp = temp->next;
    }
}

Node *addSparse(Node *head1, Node *head2){
    if(head1->row!=head2->row || head1->col!=head2->col){
        printf("Error in sparse addition due to different sizes.\n");
        return NULL;
    }

    Node *result = createNode(head1->row, head1->col, 0);
    Node *temp1 = head1->next;
    Node *temp2 = head2->next;

    while (temp1 != NULL && temp2 != NULL) {
        if (temp1->row == temp2->row && temp1->col == temp2->col) {
            result = insertNode(result, temp1->row, temp1->col, temp1->val + temp2->val);
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        else if (temp1->row < temp2->row || (temp1->row == temp2->row && temp1->col < temp2->col)) {
            result = insertNode(result, temp1->row, temp1->col, temp1->val);
            temp1 = temp1->next;
        }
        else {
            result = insertNode(result, temp2->row, temp2->col, temp2->val);
            temp2 = temp2->next;
        }
    }

    while(temp1!=NULL){
        result = insertNode(result, temp1->row, temp1->col, temp1->val);
        temp1 = temp1->next;
    }

    while(temp2!=NULL){
        result = insertNode(result, temp2->row, temp2->col, temp2->val);
        temp2 = temp2->next;
    }

    return result;
}

void freeNode(Node *head) {
    Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}


int main(){
    Node *sp1 = NULL, *sp2 = NULL;
    printf("Sparse Matrix Addition:\n\nSP MATRIX-1:\n");
    sp1 = inputSparse(sp1);
    printf("SP MATRIX-2:\n");
    sp2 = inputSparse(sp2);

    clock_t t;
    double tt;
    t = clock();

    Node *result = addSparse(sp1, sp2);

    t = clock() - t;
    tt = ((double)t)/CLOCKS_PER_SEC;
    displaySparse(result);
    printf("Sparse matrix addition took %f secs\n\n", tt);

    freeNode(sp1); freeNode(sp2); freeNode(result);

    int n, m;
    printf("Normal Matrix Addition:\n\nEnter the size of matrices: ");
    scanf("%d %d", &n, &m);
    int mat1[n][m], mat2[n][m];

    printf("MATRIX-1:\nEnter the matrix:\n");
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            scanf("%d", &mat1[i][j]);
        }
    }

    printf("MATRIX-2:\nEnter the matrix:\n");
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            scanf("%d", &mat2[i][j]);
        }
    }

    int RMatrix[n][m];
    t = clock();
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            RMatrix[i][j] = mat1[i][j] + mat2[i][j];
        }
    }
    t = clock() - t;
    tt = ((double)t)/CLOCKS_PER_SEC;

    printf("Normal addition:\n");
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            printf("%d ", RMatrix[i][j]);
        }
        printf("\n");
    }
    printf("Normal matrix addition took %f secs\n", tt);

    return 0;
}