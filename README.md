# Matrix Multiplication with POSIX Threads

This repository contains an implementation of matrix multiplication using POSIX threads (Pthreads). The project is designed to introduce concepts related to multithreading and the Pthreads library. Two variations of the matrix multiplication algorithm are implemented:

1. **Version 1:** Each element of the output matrix is computed in a separate thread.
2. **Version 2:** Each row of the output matrix is computed in a separate thread.

## Codebase

The codebase consists of the following files:

- `project.c`: This file generates two matrices and calls the functions that multiply both matrices. It is used for testing functionality and speedup.

- `matmult.c`: This file contains the implementation of the matrix multiplication algorithm. It contains the implemention for the `matmult_v1` and `matmult_v2` functions.

- `Makefile`: This Makefile  includes the necessary flags to link with the Pthreads library.

## Getting Started

To compile the project, simply run the provided Makefile:

`make`

This will compile the project and generate an executable named `lab6`.

## Running the Program

To run the program and see it in action, execute the following command:

`./lab6`

You can also add your own tests for functionality and performance within the `project.c` file.



