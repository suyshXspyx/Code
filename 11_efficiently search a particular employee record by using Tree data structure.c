#include <stdio.h>
#include <stdlib.h>

// Define the structure for an employee record
typedef struct Employee {
    int empId;
    // Add other employee details as needed
} Employee;

// Define the structure for a binary search tree node
typedef struct Node {
    Employee data;
    struct Node* left;
    struct Node* right;
} Node;

// Function to create a new node with given employee data
Node* createNode(Employee emp) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = emp;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a new employee record into the BST
Node* insert(Node* root, Employee emp) {
    if (root == NULL) {
        return createNode(emp);
    }

    if (emp.empId < root->data.empId) {
        root->left = insert(root->left, emp);
    } else if (emp.empId > root->data.empId) {
        root->right = insert(root->right, emp);
    }

    return root;
}

// Function to perform in-order traversal of the BST (ascending order)
void inOrderTraversal(Node* root) {
    if (root != NULL) {
        inOrderTraversal(root->left);
        printf("Employee ID: %d\n", root->data.empId);
        // Print other employee details as needed
        inOrderTraversal(root->right);
    }
}

// Function to search for an employee record by empId
Node* search(Node* root, int empId) {
    if (root == NULL || root->data.empId == empId) {
        return root;
    }

    if (empId < root->data.empId) {
        return search(root->left, empId);
    } else {
        return search(root->right, empId);
    }
}

// Function to free the memory allocated for the BST
void freeBST(Node* root) {
    if (root != NULL) {
        freeBST(root->left);
        freeBST(root->right);
        free(root);
    }
}

int main() {
    Node* root = NULL;

    // Example: Inserting employee records
    root = insert(root, (Employee){101});
    root = insert(root, (Employee){72});
    root = insert(root, (Employee){150});
    root = insert(root, (Employee){50});

    // Example: Searching for an employee record
    int searchId = 72;
    Node* result = search(root, searchId);
    if (result != NULL) {
        printf("Employee ID %d found!\n", searchId);
    } else {
        printf("Employee ID %d not found.\n", searchId);
    }

    // Displaying the employee records in ascending order
    printf("\nEmployee Records in Ascending Order:\n");
    inOrderTraversal(root);

    // Freeing the memory allocated for the BST
    freeBST(root);

    return 0;
}
