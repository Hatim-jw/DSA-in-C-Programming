#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int key, height;
    struct node *left, *right;
}Node;

Node* insert(Node* root, int key){
    if(root == NULL){
        Node* newNode = (Node*) malloc(sizeof(Node));
        newNode->key = key;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->height = 0;
        return newNode;
    }
    else if(key < root->key){
        root->left = insert(root->left, key);
    }
    else if(key > root->key){
        root->right =  insert(root->right, key);
    }
    else{
        //Duplicate
    }
    return root;
}

int height(Node* root){
    if(root == NULL){
        return -1;
    }

    int l_height = height(root->left);
    int r_height = height(root->right);

    if(l_height >= r_height){
        root->height =  l_height + 1;
    }
    else{
        root->height = r_height + 1;
    }

    return root->height;
}

void print_hrange(Node* root, int k, int l){
    if(root == NULL){
        return;
    }
    else if(root->height >= k && root->height <= l){
        printf("(%d:%d), ", root->key, root->height);
    }

    print_hrange(root->left, k, l);
    print_hrange(root->right, k, l);
}

int main(){
    Node* bst = NULL;

    int n;
    printf("Enter no. of keys: ");
    scanf("%d", &n);

    printf("Enter the keys to be inserted:\n");
    for(int i=0; i<n; i++){
        int num;
        scanf("%d", &num);
        bst = insert(bst, num);
    }

    printf("\nHeights of nodes calculated.\n");
    printf("Maximum height: %d\n\n", height(bst));

    int k, l;
    printf("K = ");
    scanf("%d", &k);
    printf("L = ");
    scanf("%d", &l);

    printf("Nodes with heights in the range [%d,%d]:\n", k, l);
    print_hrange(bst, k, l);
    printf("\b\b.\n");

    return 0;
}