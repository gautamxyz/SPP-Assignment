//void MySaxpy(int n, float a, float *X, float *Y)
void cblas_sscal(const int N, const float alpha, float *X, const int incX)
{
////#pragma ivdep
////#pragma omp simd
////#pragma omp parallel for
////#pragma vector nodynamic_align
////#pragma omp for
//#pragma omp parallel
//#pragma omp for simd
    for (int i = 0; i < N; ++i)
    {
        X[i*incX] = alpha * X[i*incX];

    }
}

void cblas_dscal(const int N, const double alpha, double *X, const int incX)
{
////#pragma ivdep
////#pragma omp simd
////#pragma omp parallel for
////#pragma vector nodynamic_align
////#pragma omp for
//#pragma omp parallel
{
//#pragma omp for simd
    for (int i = 0; i < N; ++i)
    {
        X[i*incX] = alpha * X[i*incX];

    }
}
}

