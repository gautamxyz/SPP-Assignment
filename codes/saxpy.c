//void MySaxpy(int n, float a, float *X, float *Y)
void cblas_saxpy(const int N, const float alpha, const float *X,
                 const int incX, float *Y, const int incY)

{
////#pragma ivdep
////#pragma omp simd
////#pragma omp parallel for
////#pragma vector nodynamic_align
// //#pragma omp parallel
////#pragma omp for simd
//#pragma omp parallel
{
  // #pragma omp for simd
   ////#pragma omp parallel for

    for (int i = 0; i < N; ++i)
        Y[i*incY] = alpha * X[i*incX] + Y[i*incY];
}
        
}

void cblas_daxpy(const int N, const double alpha, const double *X,
                 const int incX, double *Y, const int incY)

{
////#pragma ivdep
////#pragma omp simd
////#pragma omp parallel for
////#pragma vector nodynamic_align
// //#pragma omp parallel
////#pragma omp for simd
//#pragma omp parallel
{

   ////#pragma omp parallel for
   //#pragma omp for simd
    for (int i = 0; i < N; ++i)
        Y[i*incY] = alpha * X[i*incX] + Y[i*incY];
}
        
}

