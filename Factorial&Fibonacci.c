#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Stack implementation
typedef struct {
    int top;
    int items[MAX_SIZE];
} Stack;

// Function prototypes
void initialize(Stack *stack);
void push(Stack *stack, int item);
int pop(Stack *stack);
int isEmpty(Stack *stack);
int factorial(int n);
void generateFibonacci(int n);

int main() {
    int choice, n;

    do {
        printf("Choose an operation:\n");
        printf("1. Calculate factorial\n");
        printf("2. Generate Fibonacci series\n");
        printf("3. Exit\n");

        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter a number to calculate factorial: ");
                scanf("%d", &n);
                printf("Factorial of %d is: %d\n", n, factorial(n));
                break;
            case 2:
                printf("Enter the number of terms in Fibonacci series: ");
                scanf("%d", &n);
                printf("Fibonacci series:\n");
                generateFibonacci(n);
                break;
            case 3:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 3);

    return 0;
}

void initialize(Stack *stack) {
    stack->top = -1;
}

void push(Stack *stack, int item) {
    if (stack->top == MAX_SIZE - 1) {
        printf("Stack overflow\n");
        exit(EXIT_FAILURE);
    }
    stack->items[++stack->top] = item;
}

int pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    return stack->items[stack->top--];
}

int isEmpty(Stack *stack) {
    return stack->top == -1;
}

int factorial(int n) {
    Stack stack;
    initialize(&stack);
    int result = 1;

    while (n > 0) {
        push(&stack, n);
        n--;
    }

    while (!isEmpty(&stack)) {
        result *= pop(&stack);
    }

    return result;
}

void generateFibonacci(int n) {
    Stack stack;
    initialize(&stack);

    int first = 0, second = 1, next, i;

    printf("%d %d ", first, second);

    for (i = 3; i <= n; i++) {
        next = first + second;
        printf("%d ", next);
        push(&stack, first);
        first = second;
        second = next;
    }

    while (!isEmpty(&stack)) {
        printf("%d ", pop(&stack));
    }

    printf("\n");
}
