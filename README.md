SIMD Operations Example
Overview

This project demonstrates SIMD (Single Instruction, Multiple Data) operations in C++ using SSE intrinsics.
The goal is to add two float arrays in parallel using SIMD instructions and compare the performance with a standard sequential addition.

Features / What is used

SIMD Intrinsics:

_mm_loadu_ps — load 4 floats from memory into a 128-bit SSE register (unaligned).

_mm_storeu_ps — store 4 floats from SSE register back to memory.

_mm_add_ps — add 4 floats in parallel.

_mm_add_ss — add only the lowest float (scalar) for comparison purposes.

Sequential addition: normal for loop to add floats one by one.

Timing: using std::chrono::high_resolution_clock to measure execution time.

Arrays: large float arrays (example: 1 million elements) to visualize performance difference.

Results
Method	Time (seconds)	Notes
Sequential	e.g., 0.012	Standard single-element addition loop
SIMD (SSE)	e.g., 0.004	4 floats added simultaneously per instruction

How to compile:
g++ -O2 -msse -std=c++17 simd_add.cpp -o simd_add
