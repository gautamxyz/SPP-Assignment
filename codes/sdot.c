float  cblas_sdot(const int N, const float  *X, const int incX, const float  *Y, const int incY)
{
    float  dot =0.0;
    ////#pragma ivdep
    ////#pragma omp simd
    ////#pragma omp parallel for
    ////#pragma vector nodynamic_align
    ////#pragma omp for
    ////#pragma omp parallel
    ////#pragma omp for simd
    //#pragma omp parallel
    {
       // #pragma omp for simd 
        for (int i = 0; i < N; ++i)
            dot += X[i] * Y[i*incY];
    }
    return dot;
}