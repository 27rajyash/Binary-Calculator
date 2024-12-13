#include "bc.h"
#include "functions.c"

void getInput(Node** num);
void displayMenu();
void printResult(Node* result, int isNegative);
void clearInputBuffer();

int main() {
    int choice;
    Node *num1 = NULL, *num2 = NULL, *result = NULL, *remainder = NULL;

    while (1) {
        displayMenu();
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            printf("Invalid input. Please enter a number.\n");
            continue;
        }
        clearInputBuffer();  

        freeList(num1);
        freeList(num2);
        freeList(result);
        freeList(remainder);
        
        num1 = NULL;
        num2 = NULL;
        result = NULL;
        remainder = NULL;

        switch (choice) {
            case 1:  // Addition
                printf("Enter the first number:\n");
                getInput(&num1);
                printf("Enter the second number:\n");
                getInput(&num2);

                result = addLargeNumbers(num1, num2);
                printf("Result of addition: ");
                printResult(result, 0); 
                break;

            case 2:  // Subtraction
                printf("Enter the first number:\n");
                getInput(&num1);
                printf("Enter the second number:\n");
                getInput(&num2);

                int isNegative = 0;  
                result = subtractLargeNumbers(num1, num2, &isNegative);
                printf("Result of subtraction: ");
                printResult(result, isNegative);  
                break;

            case 3:  // Multiplication
                printf("Enter the first number:\n");
                getInput(&num1);
                printf("Enter the second number:\n");
                getInput(&num2);

                isNegative = 0;
                result = multiplyLargeNumbers(num1, num2, &isNegative);
                printf("Result of multiplication: ");
                printResult(result, isNegative);
                break;

            case 4:  // Division
                printf("Enter the dividend (first number):\n");
                getInput(&num1);
                printf("Enter the divisor (second number):\n");
                getInput(&num2);

                isNegative = 0;
                result = divideLargeNumbers(num1, num2, &isNegative, &remainder);
                
                printf("Result of division: ");
                printResult(result, isNegative);
                
                if (remainder && !(remainder->digit == 0 && remainder->next == NULL)) {
                    printf("Remainder: ");
                    printResult(remainder, 0);
                }
                break;

            case 0:
                freeList(num1);
                freeList(num2);
                freeList(result);
                freeList(remainder);
                
                printf("Exiting the program.\n");
                return 0;

            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}

void displayMenu() {
    printf("\n--- Binary Calculator Menu ---\n");
    printf("1. Add two large numbers\n");
    printf("2. Subtract two large numbers\n");
    printf("3. Multiply two large numbers\n");
    printf("4. Divide two large numbers\n");
    printf("0. Exit\n");
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void getInput(Node** num) {
    char input[1000]; 
    
    *num = NULL;
    
    printf("Enter a large number: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Input error.\n");
        return;
    }

    input[strcspn(input, "\n")] = 0;

    for (int i = 0; input[i] != '\0'; i++) {
        if (!isdigit(input[i])) {
            printf("Error: Input must be a positive integer.\n");
            return;
        }
        appendDigit(num, input[i] - '0');
    }

    while (*num != NULL && (*num)->digit == 0 && (*num)->next != NULL) {
        Node* temp = *num;
        *num = (*num)->next;
        (*num)->prev = NULL;
        free(temp);
    }

    if (*num == NULL) {
        *num = createNode(0);
    }
}

void printResult(Node* result, int isNegative) {
    if (result == NULL) {
        printf("No result available.\n");
        return;
    }

    if (isNegative) {
        printf("-");
    }

    Node* firstNonZero = result;
    while (firstNonZero != NULL && firstNonZero->digit == 0 && firstNonZero->next != NULL) {
        firstNonZero = firstNonZero->next;
    }

    // Print the result
    Node* temp = firstNonZero;
    while (temp != NULL) {
        printf("%d", temp->digit);
        temp = temp->next;
    }
    printf("\n");
}