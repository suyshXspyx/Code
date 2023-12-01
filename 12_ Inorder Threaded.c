#include <stdio.h>
#include <stdlib.h>

// Node structure for the threaded binary tree
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    int isThreaded; // Flag to indicate whether right pointer is threaded
} Node;

// Function to create a new threaded binary tree node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    newNode->isThreaded = 0; // Initially, right pointer is not threaded
    return newNode;
}

// Function to perform in-order threading of the binary tree
void threadedInOrder(Node* root, Node** prev) {
    if (root == NULL) {
        return;
    }

    // Recursively thread the left subtree
    threadedInOrder(root->left, prev);

    // Thread the current node
    if (*prev != NULL) {
        (*prev)->right = root; // Thread the previous node to the current node
        (*prev)->isThreaded = 1; // Set the threaded flag
    }

    // Update the previous pointer to the current node
    *prev = root;

    // Recursively thread the right subtree
    threadedInOrder(root->right, prev);
}

// Function to traverse the threaded binary tree in preorder
void preOrderTraversal(Node* root) {
    while (root != NULL) {
        printf("%d ", root->data);

        // If the right pointer is not threaded, move to the right child
        if (!root->isThreaded) {
            root = root->right;
        }
        // If the right pointer is threaded, move to the in-order successor
        else {
            root = root->right;
            while (root != NULL && root->left != NULL) {
                root = root->left;
            }
        }
    }
}

int main() {
    // Example: Creating a threaded binary tree
    Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);

    // Perform in-order threading
    Node* prev = NULL;
    threadedInOrder(root, &prev);

    // Example: Traverse the threaded binary tree in preorder
    printf("Preorder Traversal of the Threaded Binary Tree: ");
    preOrderTraversal(root);
    printf("\n");

    // Free memory
    free(root->left->right);
    free(root->left->left);
    free(root->left);
    free(root->right);
    free(root);

    return 0;
}
