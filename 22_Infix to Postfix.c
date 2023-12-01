#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct Stack {
    int top;
    unsigned capacity;
    int* array;
};

struct Stack* createStack(unsigned capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

void push(struct Stack* stack, int item) {
    stack->array[++stack->top] = item;
}

int pop(struct Stack* stack) {
    if (!isEmpty(stack))
        return stack->array[stack->top--];
    return -1; // Stack underflow
}

int peek(struct Stack* stack) {
    if (!isEmpty(stack))
        return stack->array[stack->top];
    return -1; // Stack is empty
}

int isOperand(char ch) {
    return isalnum(ch);
}

int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
    }
    return -1;
}

char* infixToPostfix(char* infix) {
    struct Stack* stack = createStack(strlen(infix));
    char* postfix = (char*)malloc((strlen(infix) + 1) * sizeof(char));
    int i, j;
    i = j = 0;

    while (infix[i]) {
        if (isOperand(infix[i])) {
            postfix[j++] = infix[i++];
        } else if (infix[i] == '(') {
            push(stack, infix[i++]);
        } else if (infix[i] == ')') {
            while (!isEmpty(stack) && peek(stack) != '(') {
                postfix[j++] = pop(stack);
            }
            if (!isEmpty(stack) && peek(stack) != '(') {
                printf("Invalid infix expression\n");
                free(postfix);
                return NULL;
            } else {
                pop(stack);
            }
            i++;
        } else {
            while (!isEmpty(stack) && precedence(infix[i]) <= precedence(peek(stack))) {
                postfix[j++] = pop(stack);
            }
            push(stack, infix[i++]);
        }
    }

    while (!isEmpty(stack)) {
        postfix[j++] = pop(stack);
    }

    postfix[j] = '\0';
    return postfix;
}

int evaluatePostfix(char* postfix) {
    struct Stack* stack = createStack(strlen(postfix));
    int i = 0;

    while (postfix[i]) {
        if (isOperand(postfix[i])) {
            push(stack, postfix[i] - '0');
        } else {
            int operand2 = pop(stack);
            int operand1 = pop(stack);

            switch (postfix[i]) {
                case '+':
                    push(stack, operand1 + operand2);
                    break;
                case '-':
                    push(stack, operand1 - operand2);
                    break;
                case '*':
                    push(stack, operand1 * operand2);
                    break;
                case '/':
                    push(stack, operand1 / operand2);
                    break;
                case '^':
                    {
                        int result = 1;
                        for (int j = 0; j < operand2; ++j) {
                            result *= operand1;
                        }
                        push(stack, result);
                        break;
                    }
            }
        }
        i++;
    }

    return pop(stack);
}

int main() {
    char infix[100];

    printf("Enter infix expression: ");
    scanf("%s", infix);

    char* postfix = infixToPostfix(infix);

    if (postfix != NULL) {
        printf("Postfix expression: %s\n", postfix);

        int result = evaluatePostfix(postfix);
        printf("Result after evaluation: %d\n", result);

        free(postfix);
    }

    return 0;
}
