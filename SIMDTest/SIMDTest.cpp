#include <iostream>
#include <chrono>
#include <xmmintrin.h> // SSE intrinsics
#include <vector>
#include <iomanip>

int main()
{
    const long N = 100000000; // 10^8
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
    for (int i = 0; i < N; i += 4) // Adding 4 floats per operation; 
    {
        __m128 vecA = _mm_loadu_ps(&a[i]); //load 4 floats
        __m128 vecB = _mm_loadu_ps(&b[i]); //load 4 float
        __m128 vecR = _mm_add_ps(vecA, vecB); //SIMD add
        _mm_storeu_ps(&result_simd[i], vecR); // store unaligned result into vector "result SIMD"
    }

    auto end_SIMD = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_simd = end_SIMD - start_SIMD;

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "+----------------+-----------------+\n";
    std::cout << "| Method         | Time (seconds)  |\n";
    std::cout << "+----------------+-----------------+\n";
    std::cout << "| Sequential     | " << std::setw(15) << duration_seq.count() << " |\n";
    std::cout << "| SIMD (SSE)     | " << std::setw(15) << duration_simd.count() << " |\n";
    std::cout << "+----------------+-----------------+\n";

    // Optional check (verify arrays are equal)
    for (int i = 0; i < N; ++i)
    {
        if (result_seq[i] != result_simd[i])
        {
            std::cout << "Error at index " << i << "\n";
            break;
        }
    }
}
