#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int key;
    struct Node *left, *right;
}node;

node* createNode(int key){
    node* newNode = (node*) malloc(sizeof(node));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    return newNode;
}

node* insertNode(node* root, int key){
    if(root == NULL){
        node* newNode = createNode(key);
        return newNode;
    }
    else if(key < root->key){
        root->left = insertNode(root->left, key);
    }
    else if(key > root->key){
        root->right = insertNode(root->right, key);
    }
    else{
        //Duplicate
    }

    return root;
}

void inorder(node* root){
    if(root == NULL){
        return;
    }

    inorder(root->left);
    printf("%d ", root->key);
    inorder(root->right);
}

void calculateSum(node** root, int* sum){
    if(*root == NULL){
        return;
    }

    calculateSum(&((*root)->left), sum);
    
    *sum += (*root)->key;
    (*root)->key = *sum;

    calculateSum(&((*root)->right), sum);
}

int main(){
    node* tree = NULL;
    int n, s = 0;

    printf("Enter no. of nodes in input tree: ");
    scanf("%d", &n);

    printf("\nEnter the preorder traversal of the input tree: ");
    for(int i=0; i<n; i++){
        int value;
        scanf("%d", &value);
        tree = insertNode(tree, value);
    }

    printf("\nInorder traversal of input tree: ");
    inorder(tree);
    printf("\n\n");

    calculateSum(&tree, &s);

    printf("Inorder traversal of output tree: ");
    inorder(tree);
    printf("\n");

    return 0;
}