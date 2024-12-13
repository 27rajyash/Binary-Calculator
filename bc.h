#ifndef BC_H
#define BC_H

#include <stdio.h>    
#include <stdlib.h>   
#include <string.h>   
#include <ctype.h>    
#include <stdbool.h>  

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Node {
    int digit;              
    struct Node* next;      
    struct Node* prev;      
} Node;

typedef struct Stack {
    char data;             
    struct Stack* next;     
} Stack;

// Function prototypes with explicit parameter names for clarity
Node* createNode(int digit);            
void appendDigit(Node** head, int digit); 
void printList(Node* head);             
void freeList(Node* head);              

void push(Stack** top, char element);  
char pop(Stack** top);                 
int isEmpty(Stack* top);               
char peek(Stack* top);                 
void freeStack(Stack* top);            

Node* addLargeNumbers(Node* num1, Node* num2);     
Node* subtractLargeNumbers(Node* num1, Node* num2, int* isNegative);
Node* multiplyLargeNumbers(Node* num1, Node* num2, int* isNegative);
Node* divideLargeNumbers(Node* dividend, Node* divisor, int* isNegative, Node** remainder);  

int compareLargeNumbers(Node* num1, Node* num2);
int getLength(Node* num);

void infixToPostfix(const char* infix, char* postfix);   
Node* evaluatePostfix(const char* postfix);

#ifdef __cplusplus
}
#endif

#endif // BC_H