#include "helper.h"
#include <stdio.h>
void cblas_sgemm(const enum CBLAS_ORDER Order, const enum CBLAS_TRANSPOSE TransA,
                 const enum CBLAS_TRANSPOSE TransB, const int M, const int N,
                 const int K, const float alpha, const float *A,
                 const int lda, const float *B, const int ldb,
                 const float beta, float *C, const int ldc)
{
    if (Order == CblasRowMajor)
    {
        if (TransA == CblasNoTrans)
        {
            if (TransB == CblasNoTrans)
            {
                for (int i = 0; i < M; i++)
                {
                    cblas_sgemv(CblasRowMajor, CblasTrans, N, K, alpha, B, ldb, A + i * lda, 1, beta, C + i * ldc, 1);
                }
                printf("done\n");
            }
            else
            {
                for (int i = 0; i < M; i++)
                {
                    cblas_sgemv(CblasRowMajor, CblasNoTrans, K, N, alpha, B, N, A + i * lda, 1, beta, C + i * ldc, 1);
                }
            }
        }
        else
        {
            if (TransB == CblasNoTrans)
            {
                for (int i = 0; i < M; i++)
                {
                    cblas_sgemv(CblasRowMajor, CblasTrans, N, K, alpha, B, ldb, A + i*lda,1, beta, C + i * ldc, 1);
                }
            }
            else
            {
                for (int i = 0; i < M; i++)
                {
                    cblas_sgemv(CblasRowMajor, CblasNoTrans, K, N, alpha, B, N, A + i*lda,1, beta, C + i * ldc, 1);
                }
            }
        }
    }
    else
    {
        if (TransA == CblasNoTrans)
        {
            if (TransB == CblasNoTrans)
            {
                for (int i = 0; i < M; i++)
                {
                    cblas_sgemv(CblasRowMajor, CblasNoTrans, K, N, alpha, B, N, A + i* lda,1, beta, C + i * ldc, 1);
                }
            }
            else
            {
                for (int i = 0; i < M; i++)
                {
                    cblas_sgemv(CblasRowMajor, CblasTrans, N, K, alpha, B, ldb, A + i* lda,1, beta, C + i * ldc, 1);
                }
            }
        }
        else
        {
            if (TransB == CblasNoTrans)
            {
                for (int i = 0; i < M; i++)
                {
                    cblas_sgemv(CblasRowMajor, CblasNoTrans, K, N, alpha, B, N, A + i * lda, 1, beta, C + i * ldc, 1);
                }
            }
            else
            {
                for (int i = 0; i < M; i++)
                {
                    cblas_sgemv(CblasRowMajor, CblasTrans, N, K, alpha, B, ldb, A + i * lda, 1, beta, C + i * ldc, 1);
                }
            }
        }
    }
}