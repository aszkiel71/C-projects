#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_STACK_SIZE 10

typedef struct {
  double* items;
  int top;
  int capacity;
} Stack;

Stack* createStack() {
  Stack* s = (Stack*)malloc(sizeof(Stack));
  if (s == NULL) {
    fprintf(stderr, "Error: Stack allocation failed!\n");
    exit(EXIT_FAILURE);
  }
  s->items = (double*)malloc(sizeof(double) * INITIAL_STACK_SIZE);
  if (s->items == NULL) {
    fprintf(stderr, "Error: Stack item allocation failed!\n");
    free(s);
    exit(EXIT_FAILURE);
  }
  s->top = -1;
  s->capacity = INITIAL_STACK_SIZE;
  return s;
}

int isEmpty(Stack* s) { return s->top == -1; }

void resizeStack(Stack* s) {
  s->capacity *= 2;
  double* new_items = (double*)realloc(s->items, sizeof(double) * s->capacity);
  if (new_items == NULL) {
    fprintf(stderr, "Error: Stack re-allocation failed!\n");
    exit(EXIT_FAILURE);
  }
  s->items = new_items;
}

void push(Stack* s, double value) {
  if (s->top == s->capacity - 1) {
    resizeStack(s);
  }
  s->items[++(s->top)] = value;
}

double pop(Stack* s) {
  if (isEmpty(s)) {
    fprintf(stderr, "Error: Stack is empty! Cannot pop element.\n");
    exit(EXIT_FAILURE);
  }
  return s->items[(s->top)--];
}

void freeStack(Stack* s) {
  if (s == NULL) return;
  free(s->items);
  free(s);
}

int isNumber(const char* token) {
  if (token == NULL || *token == '\0') return 0;
  char* endptr;
  strtod(token, &endptr);
  return *endptr == '\0';
}

double evaluateRPN(const char* expression) {
  Stack* stack = createStack();
  char* expr_copy = strdup(expression);
  if (expr_copy == NULL) {
    fprintf(stderr, "Error: Expression copy allocation failed!\n");
    exit(EXIT_FAILURE);
  }

  char* token = strtok(expr_copy, " ");

  while (token != NULL) {
    if (isNumber(token)) {
      push(stack, atof(token));
    } else {
      if (isEmpty(stack)) {
        fprintf(
            stderr,
            "Error: Insufficient arguments for operator '%s'! (Operand 2)\n",
            token);
        free(expr_copy);
        freeStack(stack);
        exit(EXIT_FAILURE);
      }
      double operand2 = pop(stack);

      if (isEmpty(stack)) {
        fprintf(
            stderr,
            "Error: Insufficient arguments for operator '%s'! (Operand 1)\n",
            token);
        free(expr_copy);
        freeStack(stack);
        exit(EXIT_FAILURE);
      }
      double operand1 = pop(stack);

      double result;
      if (strcmp(token, "+") == 0) {
        result = operand1 + operand2;
      } else if (strcmp(token, "-") == 0) {
        result = operand1 - operand2;
      } else if (strcmp(token, "*") == 0) {
        result = operand1 * operand2;
      } else if (strcmp(token, "/") == 0) {
        if (operand2 == 0) {
          fprintf(stderr, "Error: Division by zero!\n");
          free(expr_copy);
          freeStack(stack);
          exit(EXIT_FAILURE);
        }
        result = operand1 / operand2;
      } else {
        fprintf(stderr, "Error: Unknown operator '%s'!\n", token);
        free(expr_copy);
        freeStack(stack);
        exit(EXIT_FAILURE);
      }
      push(stack, result);
    }
    token = strtok(NULL, " ");
  }

  if (isEmpty(stack)) {
    fprintf(stderr,
            "Error: No result on stack. Possibly empty expression or malformed "
            "expression.\n");
    free(expr_copy);
    freeStack(stack);
    exit(EXIT_FAILURE);
  }
  double final_result = pop(stack);

  if (!isEmpty(stack)) {
    fprintf(stderr,
            "Error: Too many elements on stack after expression processing. "
            "Possibly too many numbers or too few operators.\n");
    free(expr_copy);
    freeStack(stack);
    exit(EXIT_FAILURE);
  }

  free(expr_copy);
  freeStack(stack);
  return final_result;
}

int main() {
  char expression[256];

  printf("Welcome to the simple RPN compiler!\n");
  printf("Supported operators: +, -, *, /\n");
  printf("Numbers can be integers or decimals (e.g., 3.14).\n");
  printf("Separate numbers and operators with spaces.\n");
  printf("Example: 10 20 + 5 *\n");
  printf("Enter RPN expression: ");

  if (fgets(expression, sizeof(expression), stdin) == NULL) {
    fprintf(stderr, "Error reading expression.\n");
    return EXIT_FAILURE;
  }

  expression[strcspn(expression, "\n")] = '\0';

  if (strlen(expression) == 0) {
    printf("Empty expression. Exiting.\n");
    return EXIT_SUCCESS;
  }

  double result = evaluateRPN(expression);
  printf("Result: %.2f\n", result);

  return EXIT_SUCCESS;
}
