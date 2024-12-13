# Large Number Calculator

## Overview

This is a command-line binary calculator designed to perform arithmetic operations on extremely large numbers that exceed the standard integer limits of most programming languages. The calculator supports addition, subtraction, multiplication, and division of arbitrarily large positive integers.

## Features

- **Unlimited Number Size**: Can handle numbers of virtually unlimited length
- **Supported Operations**:
  - Addition
  - Subtraction
  - Multiplication
  - Division (with remainder calculation)
- **Implemented Using Linked List**: Stores and manipulates numbers as linked lists of digits
- **Error Handling**: Robust input validation and error checking

## How It Works

The calculator uses a custom linked list data structure to represent large numbers, where each node represents a single digit. This approach allows for mathematical operations on numbers much larger than the built-in integer types can handle.

### Key Data Structures

- `Node`: Represents a single digit in a large number
  - Contains the digit value
  - Supports doubly-linked list navigation
- `Stack`: Used for expression parsing and evaluation

### Arithmetic Operations

- **Addition**: Adds digits from least significant to most significant, managing carry-over
- **Subtraction**: Compares and subtracts digits, handling borrowing
- **Multiplication**: Performs digit-by-digit multiplication with shift and add
- **Division**: Implements long division algorithm with remainder calculation

## Build Instructions

### Prerequisites

- C compiler (gcc recommended)
- Make (optional)

### Compilation

```bash
gcc -o large_number_calculator main.c
```

## Usage

Run the program and choose from the following menu options:

1. Add two large numbers
2. Subtract two large numbers
3. Multiply two large numbers
4. Divide two large numbers
0. Exit the program

### Example Interaction

```
--- Binary Calculator Menu ---
1. Add two large numbers
2. Subtract two large numbers
3. Multiply two large numbers
4. Divide two large numbers
0. Exit

Enter your choice: 1
Enter the first number: 123456789012345678901234567890
Enter the second number: 987654321098765432109876543210
Result of addition: 1111111110111111111011111111100
```

## Limitations

- Supports only positive integers
- No decimal point or floating-point operations
- Simple command-line interface

## Future Improvements

- Add support for negative numbers
- Implement floating-point operations
- Create a more sophisticated user interface
- Add more advanced mathematical functions
