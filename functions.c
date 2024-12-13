#include "bc.h"

Node* createNode(int digit) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    newNode->digit = digit;
    newNode->next = NULL;
    newNode->prev = NULL;

    return newNode;
}

void appendDigit(Node** head, int digit) {
    Node* newNode = createNode(digit);

    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }

        temp->next = newNode;
        newNode->prev = temp;
    }
}

void printList(Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    Node* temp = head;
    while (temp != NULL) {
        printf("%d", temp->digit);
        temp = temp->next;
    }
    printf("\n");
}

void freeList(Node* head) {
    Node* temp;

    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void push(Stack** top, char element) {
    Stack* newNode = (Stack*)malloc(sizeof(Stack));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    newNode->data = element;
    newNode->next = *top;
    *top = newNode;
}

char pop(Stack** top) {
    if (*top == NULL) {
        fprintf(stderr, "Stack Underflow. Attempt to pop from an empty stack.\n");
        exit(EXIT_FAILURE);
    }

    Stack* temp = *top;
    char poppedValue = temp->data;
    *top = temp->next;
    free(temp);

    return poppedValue;
}

char peek(Stack* top) {
    if (top == NULL) {
        fprintf(stderr, "Stack is empty. Cannot peek.\n");
        exit(EXIT_FAILURE);
    }
    return top->data;
}

int isEmpty(Stack* top) {
    return top == NULL;
}

void freeStack(Stack* top) {
    Stack* temp;
    while (top != NULL) {
        temp = top;
        top = top->next;
        free(temp);
    }
}

int precedence(char operator) {
    switch (operator) {
        case '+':
        case '-':
            return 1; 
        case '*':
        case '/':
            return 2; 
        default:
            return 0; 
    }
}

int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

void infixToPostfix(const char* infix, char* postfix) {
    Stack* operatorStack = NULL;
    int i = 0, j = 0;

    while (infix[i] != '\0') {
        if (isdigit(infix[i])) {
            postfix[j++] = infix[i];
        } else if (infix[i] == '(') {
            push(&operatorStack, infix[i]);
        } else if (infix[i] == ')') {
            while (!isEmpty(operatorStack) && peek(operatorStack) != '(') {
                postfix[j++] = pop(&operatorStack);
            }
            if (!isEmpty(operatorStack) && peek(operatorStack) == '(') {
                pop(&operatorStack);
            } else {
                fprintf(stderr, "Invalid expression: Mismatched parentheses.\n");
                exit(EXIT_FAILURE);
            }
        } else if (isOperator(infix[i])) {
            while (!isEmpty(operatorStack) && precedence(peek(operatorStack)) >= precedence(infix[i])) {
                postfix[j++] = pop(&operatorStack);
            }
            push(&operatorStack, infix[i]);
        } else if (!isspace(infix[i])) {
            fprintf(stderr, "Error: Invalid character '%c' in the infix expression.\n", infix[i]);
            exit(EXIT_FAILURE);
        }
        i++;
    }

    while (!isEmpty(operatorStack)) {
        postfix[j++] = pop(&operatorStack);
    }

    postfix[j] = '\0';
    freeStack(operatorStack);
}

Node* evaluatePostfix(const char* postfix) {
    Stack* operandStack = NULL;
    Node* resultList = NULL;
    int i = 0;

    while (postfix[i] != '\0') {
        if (isdigit(postfix[i])) {
            push(&operandStack, postfix[i]);
        } else if (isOperator(postfix[i])) {
            if (isEmpty(operandStack)) {
                fprintf(stderr, "Error: Invalid postfix expression.\n");
                exit(EXIT_FAILURE);
            }
            
            char op2Char = pop(&operandStack);
            if (isEmpty(operandStack)) {
                fprintf(stderr, "Error: Invalid postfix expression.\n");
                exit(EXIT_FAILURE);
            }
            char op1Char = pop(&operandStack);

            int num1 = op1Char - '0';
            int num2 = op2Char - '0';
            int result = 0;

            switch (postfix[i]) {
                case '+':
                    result = num1 + num2;
                    break;
                case '-':
                    result = num1 - num2;
                    break;
                case '*':
                    result = num1 * num2;
                    break;
                case '/':
                    if (num2 == 0) {
                        fprintf(stderr, "Error: Division by zero.\n");
                        exit(EXIT_FAILURE);
                    }
                    result = num1 / num2;
                    break;
            }

            push(&operandStack, result + '0');
        }
        i++;
    }

    if (isEmpty(operandStack)) {
        fprintf(stderr, "Error: Invalid postfix expression.\n");
        exit(EXIT_FAILURE);
    }

    char finalResult = pop(&operandStack);
    if (!isEmpty(operandStack)) {
        fprintf(stderr, "Error: Invalid postfix expression.\n");
        exit(EXIT_FAILURE);
    }

    appendDigit(&resultList, finalResult - '0');
    return resultList;
}

Node* addLargeNumbers(Node* num1, Node* num2) {
    Node* result = NULL;
    Node* temp1 = num1;
    Node* temp2 = num2;
    int carry = 0;

    while (temp1 != NULL || temp2 != NULL || carry) {
        int sum = carry;

        if (temp1 != NULL) {
            sum += temp1->digit;
            temp1 = temp1->next;
        }
        if (temp2 != NULL) {
            sum += temp2->digit;
            temp2 = temp2->next;
        }

        carry = sum / 10;
        appendDigit(&result, sum % 10);
    }

    return result;
}

Node* subtractLargeNumbers(Node* num1, Node* num2, int* isNegative) {
    Node* result = NULL;
    Node* temp1 = num1;
    Node* temp2 = num2;
    int borrow = 0;

    Node* larger = NULL;
    Node* smaller = NULL;
    
    while (temp1 != NULL && temp2 != NULL) {
        if (temp1->digit > temp2->digit) {
            larger = num1;
            smaller = num2;
            *isNegative = 0; 
            break;
        } else if (temp1->digit < temp2->digit) {
            larger = num2;
            smaller = num1;
            *isNegative = 1; 
            break;
        }
        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    if (larger == NULL) {
        if (num1 != NULL) {
            larger = num1;
            smaller = num2;
            *isNegative = 0;
        } else {
            larger = num2;
            smaller = num1;
            *isNegative = 1;
        }
    }

    while (larger != NULL || smaller != NULL) {
        int digit1 = (larger != NULL) ? larger->digit : 0;
        int digit2 = (smaller != NULL) ? smaller->digit : 0;

        int diff = digit1 - digit2;

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        appendDigit(&result, diff);

        if (larger != NULL) larger = larger->next;
        if (smaller != NULL) smaller = smaller->next;
    }

    return result;
}

Node* multiplyLargeNumbers(Node* num1, Node* num2, int* isNegative) {
    if (num1 == NULL || num2 == NULL) {
        fprintf(stderr, "Error: One of the numbers is NULL.");
        exit(EXIT_FAILURE);
    }

    int sign1 = *isNegative;
    int sign2 = 0; 

    *isNegative = (sign1 + sign2) % 2;

    Node* result = NULL;

    Node* temp1 = num1;
    int shift = 0;

    while (temp1 != NULL) {
        Node* temp2 = num2;
        Node* currentShiftedResult = NULL;
        int carry = 0;

        for (int i = 0; i < shift; i++) {
            appendDigit(&currentShiftedResult, 0);
        }

        while (temp2 != NULL) {
            int product = temp1->digit * temp2->digit + carry;
            appendDigit(&currentShiftedResult, product % 10);
            carry = product / 10;
            temp2 = temp2->next;
        }

        if (carry > 0) {
            appendDigit(&currentShiftedResult, carry);
        }

        result = addLargeNumbers(result, currentShiftedResult);
        freeList(currentShiftedResult);

        temp1 = temp1->next;
        shift++;
    }

    while (result != NULL && result->digit == 0 && result->next != NULL) {
        Node* temp = result;
        result = result->next;
        result->prev = NULL;
        free(temp);
    }

    return result;
}

Node* divideLargeNumbers(Node* dividend, Node* divisor, int* isNegative, Node** remainder) {
    Node* quotient = NULL;

    if (divisor == NULL || (divisor->digit == 0 && divisor->next == NULL)) {
        fprintf(stderr, "Error: Division by zero is undefined.\n");
        exit(EXIT_FAILURE);
    }

    if (dividend == NULL || (dividend->digit == 0 && dividend->next == NULL)) {
        Node* result = createNode(0);
        if (remainder) *remainder = createNode(0);
        return result;
    }

    int sign1 = *isNegative; 
    *isNegative = 0;  
    *remainder = NULL;
    Node* currentDividend = NULL;

    while (dividend != NULL) {
        appendDigit(&currentDividend, dividend->digit);

        while (currentDividend != NULL && currentDividend->digit == 0 && currentDividend->next != NULL) {
            Node* temp = currentDividend;
            currentDividend = currentDividend->next;
            currentDividend->prev = NULL;
            free(temp);
        }

        int quotientDigit = 0;
        while (compareLargeNumbers(currentDividend, divisor) >= 0) {
            currentDividend = subtractLargeNumbers(currentDividend, divisor, &(int){0});
            quotientDigit++;
        }

        Node* newQuotientDigit = createNode(quotientDigit);
        if (quotient == NULL) {
            quotient = newQuotientDigit;
        } else {
            newQuotientDigit->next = quotient;
            quotient->prev = newQuotientDigit;
            quotient = newQuotientDigit;
        }

        dividend = dividend->next;
    }

    *remainder = currentDividend;

    while (quotient != NULL && quotient->digit == 0 && quotient->next != NULL) {
        Node* temp = quotient;
        quotient = quotient->next;
        quotient->prev = NULL;
        free(temp);
    }

    *isNegative = sign1; 

    return quotient;
}


int compareLargeNumbers(Node* num1, Node* num2) {
    int len1 = getLength(num1);
    int len2 = getLength(num2);

    if (len1 > len2) return 1;
    if (len1 < len2) return -1;

    Node* temp1 = num1;
    Node* temp2 = num2;
    while (temp1 != NULL && temp2 != NULL) {
        if (temp1->digit > temp2->digit) return 1;
        if (temp1->digit < temp2->digit) return -1;

        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    return 0;
}

int getLength(Node* head) {
    int length = 0;
    while (head != NULL) {
        length++;
        head = head->next;
    }
    return length;
}
