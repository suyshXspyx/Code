#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct Stack {
    int top;
    unsigned capacity;
    char* array;
};

struct Stack* createStack(unsigned capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (char*)malloc(stack->capacity * sizeof(char));
    return stack;
}

int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

void push(struct Stack* stack, char item) {
    stack->array[++stack->top] = item;
}

char pop(struct Stack* stack) {
    if (!isEmpty(stack))
        return stack->array[stack->top--];
    return -1; // Stack underflow
}

char peek(struct Stack* stack) {
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

char* infixToPrefix(char* infix) {
    // Reverse the infix expression
    int len = strlen(infix);
    for (int i = 0; i < len / 2; i++) {
        char temp = infix[i];
        infix[i] = infix[len - i - 1];
        infix[len - i - 1] = temp;
    }

    struct Stack* stack = createStack(strlen(infix));
    char* prefix = (char*)malloc((strlen(infix) + 1) * sizeof(char));
    int i, j;
    i = j = 0;

    while (infix[i]) {
        if (isOperand(infix[i])) {
            prefix[j++] = infix[i++];
        } else if (infix[i] == ')') {
            push(stack, infix[i++]);
        } else if (infix[i] == '(') {
            while (!isEmpty(stack) && peek(stack) != ')') {
                prefix[j++] = pop(stack);
            }
            if (!isEmpty(stack) && peek(stack) != ')') {
                printf("Invalid infix expression\n");
                free(prefix);
                return NULL;
            } else {
                pop(stack);
            }
            i++;
        } else {
            while (!isEmpty(stack) && precedence(infix[i]) <= precedence(peek(stack))) {
                prefix[j++] = pop(stack);
            }
            push(stack, infix[i++]);
        }
    }

    while (!isEmpty(stack)) {
        prefix[j++] = pop(stack);
    }

    prefix[j] = '\0';

    // Reverse the prefix expression to get the final result
    for (int i = 0; i < j / 2; i++) {
        char temp = prefix[i];
        prefix[i] = prefix[j - i - 1];
        prefix[j - i - 1] = temp;
    }

    return prefix;
}

int evaluatePrefix(char* prefix) {
    struct Stack* stack = createStack(strlen(prefix));
    int i = 0;

    while (prefix[i]) {
        if (isOperand(prefix[i])) {
            push(stack, prefix[i] - '0');
        } else {
            int operand2 = pop(stack);
            int operand1 = pop(stack);

            switch (prefix[i]) {
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

    char* prefix = infixToPrefix(infix);

    if (prefix != NULL) {
        printf("Prefix expression: %s\n", prefix);

        int result = evaluatePrefix(prefix);
        printf("Result after evaluation: %d\n", result);

        free(prefix);
    }

    return 0;
}
