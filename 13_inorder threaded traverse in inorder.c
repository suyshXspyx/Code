#include <stdio.h>
#include <stdlib.h>

// Structure for a threaded binary tree node
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
    int isThreaded; // Indicates whether the right pointer is a thread or not
} TreeNode;

// Function to create a new threaded binary tree node
TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->isThreaded = 0;
    return newNode;
}

// Function to perform Morris Inorder Traversal on the threaded binary tree
void morrisInorderTraversal(TreeNode* root) {
    TreeNode* current = root;

    while (current != NULL) {
        if (current->left == NULL) {
            // If left child is NULL, print the current node and move to right
            printf("%d ", current->data);

            current = (current->isThreaded) ? NULL : current->right; // Move to the threaded right child
        } else {
            // Find the inorder predecessor
            TreeNode* predecessor = current->left;
            while (predecessor->right != NULL && predecessor->right != current)
                predecessor = predecessor->right;

            // Make the current node as the right child of its inorder predecessor
            if (predecessor->right == NULL) {
                predecessor->right = current;
                current = current->left;
            } else {
                // Revert the changes made in the 'if' part to restore the original tree
                predecessor->right = NULL;
                printf("%d ", current->data);
                current = (current->isThreaded) ? NULL : current->right; // Move to the threaded right child
            }
        }
    }
}

// Function to convert a binary tree to a threaded binary tree using Morris Traversal
void convertToThreaded(TreeNode* root) {
    if (root == NULL)
        return;

    TreeNode* current = root;
    TreeNode* predecessor = NULL;

    while (current != NULL) {
        if (current->left == NULL) {
            // If left child is NULL, make the current node as the threaded right child of its inorder predecessor
            if (predecessor != NULL) {
                predecessor->right = current;
                predecessor->isThreaded = 1; // Set the threaded flag
            }

            predecessor = current; // Move to the threaded right child
            current = current->right;
        } else {
            // Find the inorder predecessor
            TreeNode* temp = current->left;
            while (temp->right != NULL && temp->right != current)
                temp = temp->right;

            // If the right child of the inorder predecessor is NULL, make the current node as the right child
            // Otherwise, revert the changes made in the 'if' part to restore the original tree
            if (temp->right == NULL) {
                temp->right = current;
                current = current->left;
            } else {
                temp->right = NULL;
                predecessor = current;
                printf("%d ", current->data); // Print the current node during the conversion
                current = current->right;
            }
        }
    }
}

int main() {
    // Create a binary tree
    TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);

    // Convert the binary tree to a threaded binary tree
    convertToThreaded(root);

    // Perform Morris Inorder Traversal on the threaded binary tree
    printf("\nInorder Traversal: ");
    morrisInorderTraversal(root);
    printf("\n");

    return 0;
}
