//Includes
#include "trabalho_aux.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Function to create an empty stack
Stack* createStack(void) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (stack == NULL) {
        printf("Error: Failed to allocate memory for the stack.\n");
        exit(EXIT_FAILURE);
    }
    stack->top = NULL;
    return stack;
}

// Function to check if the stack is empty
int isEmpty(Stack* stack) {
    return stack->top == NULL;
}

// Function to push a value onto the stack
void push(Stack* stack, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Error: Failed to allocate memory for the stack node.\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
}

// Function to pop a value from the stack
int pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Error: Attempt to pop from an empty stack.\n");
        exit(EXIT_FAILURE);
    }
    int data = stack->top->data;
    Node* temp = stack->top;
    stack->top = stack->top->next;
    free(temp);
    return data;
}

// Function to evaluate a postfix expression
int calculatePostfix(const char* expression) {
    Stack* stack = createStack();
    int i = 0;
    while (expression[i] != '\0') {
        if (isdigit(expression[i])) {
            int value = 0;
            while (isdigit(expression[i])) {
                value = value * 10 + (expression[i] - '0');
                i++;
            }
            push(stack, value);
        } else if (expression[i] == ' ') {
            // Ignore whitespace
            i++;
        } else {
            // Operator encountered
            int operand2 = pop(stack);
            int operand1 = pop(stack);
            switch (expression[i]) {
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
                default:
                    printf("Invalid operator: %c\n", expression[i]);
                    exit(EXIT_FAILURE);
            }
            i++;
        }
    }
    int result = pop(stack);
    if (!isEmpty(stack)) {
        printf("Error: The stack is not empty after evaluating the expression.\n");
        exit(EXIT_FAILURE);
    }
    free(stack);
    return result;
}
