#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Define the structure for a tree node
typedef struct Node {
    char character;
    struct Node *left;
    struct Node *right;
} Node;

// Function to create a new tree node
Node* createNode(char character) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->character = character;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to decode the encoded bitstream
void huffmanDecode(Node* root, const char* encodedData) {
    Node* currentNode = root;
    
    for (int i = 0; i < strlen(encodedData); i++) {
        // Traverse the tree based on the bit
        if (encodedData[i] == '0') {
            currentNode = currentNode->left;
        } else if (encodedData[i] == '1') {
            currentNode = currentNode->right;
        }

        // If leaf node is reached, output the character
        if (currentNode->left == NULL && currentNode->right == NULL) {
            printf("%c", currentNode->character);
            currentNode = root;  // Reset to root to decode next character
        }
    }
}

int main() {
    // Manually create a Huffman tree for this example
    // Example Huffman Tree:
    //          (root)
    //         /    \
    //        A      B
    //       / \
    //      C   D

    Node* root = createNode('\0'); // Root node

    // Left and right branches
    root->left = createNode('\0'); // Internal node
    root->right = createNode('B'); // Leaf node with character 'B'

    // Left subtree of root
    root->left->left = createNode('A'); // Leaf node with character 'A'
    root->left->right = createNode('\0'); // Internal node
    root->left->right->left = createNode('C'); // Leaf node with character 'C'
    root->left->right->right = createNode('D'); // Leaf node with character 'D'

    // Example encoded data (Huffman codes)
    // Suppose we have the following Huffman codes:
    // A: 00
    // B: 1
    // C: 010
    // D: 011
    const char* encodedData = "010011001"; // Corresponds to C, D, A, B

    // Decode the encoded data
    printf("Decoded Data: ");
    huffmanDecode(root, encodedData);

    // Free allocated memory (important in real-world applications)
    free(root->left->left);  // Node A
    free(root->left->right->left);  // Node C
    free(root->left->right->right); // Node D
    free(root->left->right);   // Internal node
    free(root->left);          // Internal node
    free(root->right);         // Node B
    free(root);                // Root

    return 0;
}
