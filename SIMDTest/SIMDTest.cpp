#include <iostream>
#include <xmmintrin.h> // SSE intrinsics

int main()
{
    // Arrays must be aligned or size multiple of 4 for simplicity
    alignas(16) float a[4] = { 1.0f, 2.0f, 3.0f, 4.0f };
    alignas(16) float b[4] = { 5.0f, 6.0f, 7.0f, 8.0f };
    alignas(16) float result[4];

    // Load 4 floats from each array into an SSE register
    __m128 vecA = _mm_load_ps(a);  // Load a[0..3] into vecA
    __m128 vecB = _mm_load_ps(b);  // Load b[0..3] into vecB

    // Perform SIMD addition
    __m128 vecResult = _mm_add_ps(vecA, vecB);

    // Store the result back to memory
    _mm_store_ps(result, vecResult);

    // Print result
    std::cout << "Result: ";
    for (int i = 0; i < 4; ++i)
        std::cout << result[i] << " ";
    std::cout << std::endl;

    return 0;
}
