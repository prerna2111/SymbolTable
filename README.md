This program implements a symbol table using a hash table for efficient storage and retrieval of symbols along with their corresponding values. It reads a series of commands from a file and performs actions such as creating new scopes, ending scopes, assigning values to symbols, and printing the values of symbols.

## Description

A symbol table is a data structure used by compilers to keep track of various entities such as variable names, function names, etc., along with their attributes or values. This program demonstrates the implementation of a symbol table using a hash table data structure.

## Features

- **Hash Table**: Utilizes a hash table for storing symbols and their corresponding values.
- **Scoping**: Supports nested scopes, allowing for the definition of symbols within different scopes.
- **File Input**: Reads commands from a file to perform symbol table operations.
- **Command Interpretation**: Supports commands such as creating new scopes (`begin`), ending scopes (`end`), assigning values to symbols (`assign`), and printing the values of symbols (`print`).
