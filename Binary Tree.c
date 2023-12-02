#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
struct Node {
int data;
struct Node* left;
struct Node* right;
};
struct Node* createNode(int data) {
struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
if (newNode) {
newNode->data = data;
newNode->left = NULL;
newNode->right = NULL;
}
return newNode;
}
struct Node* insertNode(struct Node* root, int data)
{ if (root == NULL)
return createNode(data);
if (data < root->data)
root->left = insertNode(root->left, data);
else if (data > root->data)
root->right = insertNode(root->right, data);
return root;
}
int computeHeight(struct Node* root) {
if (root == NULL)
return -1;
int leftHeight = computeHeight(root->left);
int rightHeight = computeHeight(root->right);
return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1; }
void levelOrderTraversal(struct Node* root) {
if (root == NULL)
return;
struct Node* queue[100];
int front = -1, rear = -1;
queue[++rear] = root;
while (front < rear) {
struct Node* temp = queue[++front];
printf("%d ", temp->data);
if (temp->left)
queue[++rear] = temp->left;
if (temp->right)
queue[++rear] = temp->right;
}
}
int isMirror(struct Node* a, struct Node* b) {
if (a == NULL && b == NULL)
return 1;
if (a == NULL || b == NULL)
return 0;
return (a->data == b->data) && isMirror(a->left, b->right) && isMirror(a->right, b->left);
}
void printLeafNodes(struct Node* root) {
if (root == NULL)
return;
if (root->left == NULL && root->right == NULL)
printf("%d ", root->data);
printLeafNodes(root->left);
printLeafNodes(root->right);
}
struct Node* constructMirror(struct Node* root) {
if (root == NULL)
return NULL;
struct Node* newNode = createNode(root->data);
newNode->left = constructMirror(root->right);
newNode->right = constructMirror(root->left);
return newNode;
}
int isBSTUtil(struct Node* node, int min, int max) {
if (node == NULL)
return 1;
if (node->data < min || node->data > max)
return 0;
return isBSTUtil(node->left, min, node->data - 1) && isBSTUtil(node->right, node->data + 1, max); }
int isBST(struct Node* root) {
return isBSTUtil(root, INT_MIN, INT_MAX);
}
void cleanUp(struct Node* root) {
if (root) {
cleanUp(root->left);
cleanUp(root->right);
free(root);
}
}
int main() {
struct Node* root = NULL;
int choice, data;
do {
printf("\nMenu:\n1.Insert \n2.Compute the Height \n3.Level Order Traversal \n4.Detect Mirror
Image \n5.Print a Leaf Nodes\n6.Construct Mirror Image \n7.Check if it's a BST \n8.Exit\n");
printf("Enter your choice: ");
scanf("%d", &choice);
switch (choice) {
case 1:
printf("Enter data to insert: ");
scanf("%d", &data);
root = insertNode(root, data);
break;
case 2:
printf("Height of the binary tree: %d\n", computeHeight(root));
break;
case 3:
printf("Level Order Traversal: ");
levelOrderTraversal(root);
printf("\n");
break;
case 4:
if (isMirror(root, root))
printf("The tree has a mirror image.\n"); else
printf("The tree does not have a mirror image.\n"); break;
case 5:
printf("Leaf nodes: ");
printLeafNodes(root);
printf("\n");
break;
case 6:
root = constructMirror(root);
printf("Mirror image constructed.\n"); break;
case 7:
if (isBST(root))
printf("The tree is a BST.\n");
else
printf("The tree is not a BST.\n");
break;
case 8:
printf("Exiting...\n");
break;
default:
printf("Invalid choice. Please try again.\n");
}
} while (choice != 8);
cleanUp(root);
return 0;
}
