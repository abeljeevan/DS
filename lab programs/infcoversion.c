#include <stdio.h>
#include <ctype.h>  
#include <stdlib.h> 
#include <string.h> 

#define MAX 100
typedef struct {
    int top;
    char items[MAX];
} Stack;

void push(Stack *s, char value) {
    if (s->top == (MAX - 1)) {
        printf("Stack Overflow\n");
        exit(1);
    }
    s->items[++(s->top)] = value;
}

char pop(Stack *s) {
    if (s->top == -1) {
        printf("Stack Underflow\n");
        exit(1);
    }
    return s->items[(s->top)--];
}

char peek(Stack *s) {
    if (s->top == -1) {
        return '\0';
    }
    return s->items[s->top];
}
int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}
int precedence(char ch) {
    switch (ch) {
        case '^': return 3;
        case '*':
        case '/': return 2;
        case '+':
        case '-': return 1;
        default: return 0;
    }
}
int isLeftParenthesis(char ch) {
    return (ch == '(');
}
int isRightParenthesis(char ch) {
    return (ch == ')');
}

void infixToPostfix(char infix[], char postfix[]) {
    Stack s;
    s.top = -1;
    int i = 0, j = 0;
    char symbol;

    while ((symbol = infix[i++]) != '\0') {
        if (isdigit(symbol) || isalpha(symbol)) {
            postfix[j++] = symbol;
        } else if (isLeftParenthesis(symbol)) {
            // If the symbol is a '(', push it onto the stack
            push(&s, symbol);
        } else if (isRightParenthesis(symbol)) {
            // If the symbol is a ')', pop and output from the stack until '(' is encountered
            while (!isLeftParenthesis(peek(&s))) {
                postfix[j++] = pop(&s);
            }
            pop(&s);  // Discard the '('
        } else if (isOperator(symbol)) {
            // If the symbol is an operator
            while (s.top != -1 && precedence(peek(&s)) >= precedence(symbol)) {
                postfix[j++] = pop(&s);
            }
            push(&s, symbol);
        }
    }

    // Pop all remaining operators from the stack
    while (s.top != -1) {
        postfix[j++] = pop(&s);
    }

    postfix[j] = '\0';
}

int main() {
    char infix[MAX], postfix[MAX];

    printf("Enter an infix expression: ");
    fgets(infix, MAX, stdin);  // Read the infix expression from user

    infixToPostfix(infix, postfix);  // Convert to postfix

    printf("Postfix Expression: %s\n", postfix);

    return 0;
}

