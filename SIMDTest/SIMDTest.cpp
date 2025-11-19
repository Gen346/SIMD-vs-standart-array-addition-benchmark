#include <iostream>
#include <chrono>
#include <xmmintrin.h> // SSE intrinsics
#include <vector>
#include <iomanip>

int main()
{
    const int N = 1000000;
    std::vector<float> a(N, 1.0f);
    std::vector<float> b(N, 2.0f);
    std::vector<float> result_seq(N, 0.0f);
    std::vector<float> result_simd(N, 0.0f);

    auto start_seq = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < N; ++i)
    {
        result_seq[i] = a[i] + b[i];
    }

    auto end_seq = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration_seq = end_seq - start_seq;

    auto start_SIMD = std::chrono::high_resolution_clock::now();
    //_mm128 - 128-bit SSE (Streaming SIMD Extension) register
    for (int i = 0; i < N - 4; i += 4) // Adding 4 floats per operation; 
    {
        __m128 vecA = _mm_loadu_ps(&a[i]); //load 4 floats
        __m128 vecB = _mm_loadu_ps(&b[i]); //load 4 float
        __m128 vecR = _mm_add_ps(vecA, vecB); //SIMD add


    }

    auto end_SIMD = std::chrono::high_resolution_clock::now();
    return 0;
}
