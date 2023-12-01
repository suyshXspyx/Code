/*2.	Write a Program to create a Binary Tree and perform following nonrecursive operations on it.
 a. inorder Traversal; b. Count no. of nodes on longest path; c. display tree levelwise; d. Display height of a tree.*/


 #include <stdio.h>
#include <stdlib.h>

// Define a structure for tree nodes
struct TreeNode {
    int value;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Function to create a new node
struct TreeNode* createNode(int value) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->value = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to perform inorder traversal non-recursively
void inorderTraversal(struct TreeNode* root) {
    if (root == NULL) return;

    struct TreeNode* stack[100]; // Assuming a maximum of 100 nodes
    int top = -1;
    struct TreeNode* current = root;

    while (current != NULL || top != -1) {
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }

        current = stack[top--];
        printf("%d ", current->value);

        current = current->right;
    }
}

// Function to count nodes on the longest path
int countNodesOnLongestPath(struct TreeNode* root) {
    if (root == NULL) return 0;

    struct TreeNode* queue[100];
    int front = 0, rear = -1;
    int nodesAtCurrentLevel = 1;
    int nodesAtNextLevel = 0;
    int level = 0;

    queue[++rear] = root;

    while (front <= rear) {
        struct TreeNode* current = queue[front++];
        nodesAtCurrentLevel--;

        if (current->left) {
            queue[++rear] = current->left;
            nodesAtNextLevel++;
        }
        if (current->right) {
            queue[++rear] = current->right;
            nodesAtNextLevel++;
        }

        if (nodesAtCurrentLevel == 0) {
            level++;
            nodesAtCurrentLevel = nodesAtNextLevel;
            nodesAtNextLevel = 0;
        }
    }

    return level;
}

// Function to display tree level-wise
void displayLevelWise(struct TreeNode* root) {
    if (root == NULL) return;

    struct TreeNode* queue[100];
    int front = 0, rear = -1;

    queue[++rear] = root;

    while (front <= rear) {
        struct TreeNode* current = queue[front++];

        printf("%d ", current->value);

        if (current->left)
            queue[++rear] = current->left;
        if (current->right)
            queue[++rear] = current->right;
    }

    printf("\n");
}

// Function to display height of the tree
int heightOfTree(struct TreeNode* root) {
    if (root == NULL) return 0;

    struct TreeNode* queue[100];
    int front = 0, rear = -1;
    int level = 0;

    queue[++rear] = root;

    while (front <= rear) {
        int nodesAtCurrentLevel = rear - front + 1;

        while (nodesAtCurrentLevel > 0) {
            struct TreeNode* current = queue[front++];
            
            if (current->left)
                queue[++rear] = current->left;
            if (current->right)
                queue[++rear] = current->right;

            nodesAtCurrentLevel--;
        }

        level++;
    }

    return level;
}

// Main function
int main() {
    // Create a sample binary tree
    struct TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    // Perform operations
    printf("Inorder Traversal: ");
    inorderTraversal(root);
    printf("\n");

    printf("Count of Nodes on Longest Path: %d\n", countNodesOnLongestPath(root));

    printf("Display Tree Level-wise: ");
    displayLevelWise(root);

    printf("Height of the Tree: %d\n", heightOfTree(root));

    return 0;
}
