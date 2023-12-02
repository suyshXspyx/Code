    #include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 5

// Stack implementation
typedef struct {
    int top;
    int items[MAX_SIZE];
} Stack;

// Function prototypes
void initialize(Stack *stack);
void push(Stack *stack, int item);
int pop(Stack *stack);
int isFull(Stack *stack);
int isEmpty(Stack *stack);
void displayStack(Stack *stack);

int main() {
    Stack stack;
    initialize(&stack);

    int choice, item;

    do {
        printf("\nMenu:\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Stack Full?\n");
        printf("4. Stack Empty?\n");
        printf("5. Display Stack\n");
        printf("0. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (isFull(&stack)) {
                    printf("Stack is full. Cannot push.\n");
                } else {
                    printf("Enter the item to push: ");
                    scanf("%d", &item);
                    push(&stack, item);
                    printf("Pushed %d to the stack.\n", item);
                }
                break;
            case 2:
                if (isEmpty(&stack)) {
                    printf("Stack is empty. Cannot pop.\n");
                } else {
                    item = pop(&stack);
                    printf("Popped %d from the stack.\n", item);
                }
                break;
            case 3:
                if (isFull(&stack)) {
                    printf("Stack is full.\n");
                } else {
                    printf("Stack is not full.\n");
                }
                break;
            case 4:
                if (isEmpty(&stack)) {
                    printf("Stack is empty.\n");
                } else {
                    printf("Stack is not empty.\n");
                }
                break;
            case 5:
                displayStack(&stack);
                break;
            case 0:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (choice != 0);

    return 0;
}

void initialize(Stack *stack) {
    stack->top = -1;
}

void push(Stack *stack, int item) {
    stack->items[++stack->top] = item;
}

int pop(Stack *stack) {
    return stack->items[stack->top--];
}

int isFull(Stack *stack) {
    return stack->top == MAX_SIZE - 1;
}

int isEmpty(Stack *stack) {
    return stack->top == -1;
}

void displayStack(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty.\n");
    } else {
        printf("Stack elements: ");
        for (int i = 0; i <= stack->top; i++) {
            printf("%d ", stack->items[i]);
        }
        printf("\n");
}}
