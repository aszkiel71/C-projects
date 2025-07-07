# C-projects

A collection of C programming projects including algorithms, a text editor, and a compiler utility.

## Projects

### 📁 algorithms/
Mathematical algorithms and computational solutions:
- **dhondt.c** - Implementation of the D'Hondt method for proportional representation seat allocation
- **ebs.c** - Exponentiation by squaring algorithm for efficient power calculation
- **gcd.c** - Greatest Common Divisor calculator using Euclidean algorithm
- **program.exe** - Compiled executable

### 📁 compilator-to-rpn/
Expression compiler and evaluator:
- **compilator.c** - Converts mathematical expressions to Reverse Polish Notation (RPN) and evaluates them
- **program.exe** - Compiled executable

### 📁 my-vim/
Simple text editor implementation:
- **myvim.c** - A basic text editor for Windows console with file loading, saving, cursor movement, and text editing capabilities
- **program.exe** - Compiled executable

## Building

Each project can be compiled using GCC:
```bash
gcc -o program filename.c
```

Or use the VS Code build task (Ctrl+Shift+P → "Tasks: Run Build Task") to compile the active file.

## Usage

Run the compiled executables to use each program:
- Navigate to the respective directory
- Run `./program.exe` (or `program.exe` on Windows)

## Requirements

- GCC compiler (MinGW-w64 on Windows)
- Windows console (for my-vim project)
- Standard C libraries
