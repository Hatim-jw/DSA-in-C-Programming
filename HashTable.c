#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int value;
    struct Node* next;
}Node;

typedef struct HashTable{
    Node* table[10];
}HashTable;

Node* createNode(int value){
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

int HashFunc(int value){
    return value % 10;
}

void initTable(HashTable* ht){
    for(int i=0; i<10; i++){
        ht->table[i] = NULL;
    }
}

void insert(HashTable* ht, int value){
    int index = HashFunc(value);
    Node* newNode = createNode(value);

    if(ht->table[index] == NULL){
        ht->table[index] = newNode;
        return;
    }

    Node* curr = ht->table[index];
    while(curr->next != NULL){
        curr = curr->next;
    }
    curr->next = newNode;
}

void search(HashTable* ht, int key){
    int index = HashFunc(key);

    Node* curr = ht->table[index];
    while(curr != NULL){
        if(curr->value == key){
            printf("Searching for %d....\n%d found in the table\n", key, key);
            return;
        }
        curr = curr->next;
    }
    
    printf("Searching for %d....\n%d was not found\n", key, key);
}

void delete(HashTable* ht, int key){
    int index = HashFunc(key);

    Node* curr = ht->table[index];
    Node* prev = NULL;
    while(curr != NULL){
        if(curr->value == key){
            if(prev == NULL){
                ht->table[index] = curr->next;
            }
            else{
                prev->next = curr->next;
            }
            free(curr);
            printf("%d deleted.\n");
            return;
        }
        prev = curr;
        curr = curr->next;
    }

    printf("%d cannot be deleted because it does not exist in table.\n", key);
}

void display(HashTable* ht){
    for(int i=0; i<10; i++){
        Node* curr = ht->table[i];
        printf("Index %d: ", i+1);
        while(curr != NULL){
            printf("%d -> ", curr->value);
            curr = curr->next;
        }
        printf("NULL\n");
    }
}

int main(){
    HashTable hash;
    initTable(&hash);

    insert(&hash, 16);
    insert(&hash, 25);
    insert(&hash, 38);
    insert(&hash, 45);
    insert(&hash, 12);

    display(&hash);
    printf("\n");

    search(&hash, 35);
    search(&hash, 10);
    printf("\n");

    delete(&hash, 35);
    delete(&hash, 12);
    printf("\n");

    display(&hash);

    return 0;
}