# C-projects

A collection of C programming projects including algorithms, a text editor, a compiler utility, and a custom memory allocator.

## Projects

### 📁 algorithms/
Mathematical algorithms and computational solutions:
- **dhondt.c** - Implementation of the D'Hondt method for proportional representation seat allocation
- **ebs.c** - Exponentiation by squaring algorithm for efficient power calculation
- **gcd.c** - Greatest Common Divisor calculator using Euclidean algorithm


### 📁 compilator-to-rpn/
Expression compiler and evaluator:
- **compilator.c** - Evaluate Reverse Polish Notation (RPN) and calculate them


### 📁 my-vim/
Simple text editor implementation:
- **myvim.c** - A basic text editor for Windows console with file loading, saving, cursor movement, and text editing capabilities


### 📁 custom_malloc/
Custom implementation of memory allocation functions:
- **custom_malloc.c** - Minimal implementation of `malloc`, `free`, and `realloc` using `sbrk()` system call and metadata headers
- Demonstrates manual memory management, block reuse, and resizing
- Includes built-in usage examples and block visualization output


## Building

Each project can be compiled using GCC:
```bash
gcc -o program filename.c

