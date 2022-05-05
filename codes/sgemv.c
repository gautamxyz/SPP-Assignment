#include "helper.h"
void cblas_sgemv(const enum CBLAS_ORDER order, const enum CBLAS_TRANSPOSE TransA,
                 const int M, const int N, const float alpha, const float *A,
                 const int lda, const float *X, const int incX,
                 const float beta, float *Y, const int incY)
{
    ////#pragma ivdep
    ////#pragma omp simd
    ////#pragma omp parallel for
    ////#pragma vector nodynamic_align
    // //#pragma omp parallel
    ////#pragma omp for simd
    ////#pragma omp parallel
    {
        ////#pragma omp for simd
        ////#pragma omp parallel for
        ////#pragma vector nodynamic_align
        // //#pragma omp parallel
        ////#pragma omp for simd
        ////#pragma omp parallel for
        ////#pragma vector nodynamic_align
        // //#pragma omp parallel
        ////#pragma omp for simd
        // parallelize by row
        if (order == CblasRowMajor)
        {
            if (TransA == CblasNoTrans)
            {
                // vectorize by row using pragma

//#pragma omp parallel
//#pragma omp for simd
                for (int i = 0; i < M; ++i)
                {
                    ////#pragma omp parallel
                    // for (int j = 0; j < N; ++j)
                    //  sum += A[i*lda + j] * X[j*incX];
                    Y[i * incY] = beta * Y[i * incY] + alpha * cblas_sdot(N, A + i * lda, 1, X, incX);
                }
            }
            else if (TransA == CblasTrans)
            {
                // vectorize by row using pragma

                // for(int i=0;i<N;i++)

                cblas_sscal(N, beta, Y, incY);
//#pragma omp parallel
                {
//#pragma omp for simd
                    for (int i = 0; i < M; ++i)
                    {
                        float sum = 0;
                        cblas_saxpy(N, alpha * X[i], A + i * lda, 1, Y, incY);
                        ////#pragma omp parallel
                        //for (int j = 0; j < N; ++j)
                          //  sum += A[j * lda + i] * X[j * incX];
                        //Y[i * incY] = beta * Y[i * incY] + alpha * sum;
                    }
                }
            }
        }
        else
        {
            if (TransA == CblasNoTrans)
            {
// vectorize by column using pragma
// for(int i=0;i<M;i++)
                cblas_sscal(N, beta, Y, incY);
//#pragma omp parallel
                {
//#pragma omp for simd
                    for (int i = 0; i < M; ++i)
                    {
                        //float sum = 0;
                        cblas_saxpy(N, alpha * X[i], A + i * lda, 1, Y, incY);
                        ////#pragma omp parallel
                        //for (int j = 0; j < N; ++j)
                          //  sum += A[j * lda + i] * X[j * incX];
                        //Y[i * incY] = beta * Y[i * incY] + alpha * sum;
                    }
                }
            }

            else if (TransA == CblasTrans)
            {
                // vectorize by column using pragma
                // for(int i=0;i<N;i++)
                //cblas_sscal(N, beta, Y, incY);
                //#pragma omp parallel
                {
#pragma omp for simd
                    for (int i = 0; i < N; ++i)
                    {
                        float sum = cblas_sdot(M, A + i*lda,1, X, incX);
                        //cblas_saxpy(M, alpha * X[i], A + i, lda, Y, incY);
                        ////#pragma omp parallel
                        //for (int j = 0; j < M; ++j)
                          //  sum += A[j * lda + i] * X[j * incX];
                        Y[i * incY] = beta * Y[i * incY] + alpha * sum;
                    }
                }

            }
        }
    }
}