#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "helper.h"
//#include "blis.h"

#define DEFAULT_VECTOR_LENGTH 100000000 // million
// computing Y = aX + Y
int main(int argc, char *argv[])
{
    struct timeval calc;
    double calctime;
    int n, m,k;
    float a = 1.1;
    double b = 0.7;
    float *X, *Y, *A;
    // double *x,*y;

    // double a = 0.8; // scalar value
    double gflops;

    // if (argc > 1)
    //   n = atoi(argv[1]);
    // else
    n = DEFAULT_VECTOR_LENGTH;
    m = DEFAULT_VECTOR_LENGTH;
    k=DEFAULT_VECTOR_LENGTH;

    // Changes as per the problem

    if (argv[1][0] == 's')
    {

        if (strcmp(argv[1],"sgemm")==0 ||strcmp(argv[1],"sgemm2")==0||strcmp(argv[1],"sgemm3")==0||strcmp(argv[1],"sgemm4")==0||strcmp(argv[1],"sgemm5")==0||strcmp(argv[1],"sgemm6")==0||strcmp(argv[1],"sgemm7")==0||strcmp(argv[1],"sgemm8")==0)
        {
            m=500;
            k=500;
            n=500;
            X=(float*)malloc(m*k*sizeof(float));
            Y=(float*)malloc(k*n*sizeof(float));
            A=(float*)malloc(m*n*sizeof(float));
            RandomVector(m*k, X);
            RandomVector(k*n, Y);

        }
        else if (strcmp(argv[1], "sgemv") == 0)
        {
            m = 1e5;

            n = 1e3;
            X = (float *)malloc(n * sizeof(float));
            Y = (float *)malloc(m * sizeof(float));
            RandomVector(n, X);
            RandomVector(m, Y);
        }
        else if (strcmp(argv[1], "sgemv2") == 0)
        { // Row major Transpose
            m = 20050;
            n = 1e3;
            X = (float *)malloc(m * sizeof(float));
            Y = (float *)malloc(n * sizeof(float));
            // printf("hello1");
            RandomVector(m, X);
            RandomVector(n, Y);
        }
        else if (strcmp(argv[1], "sgemv3") == 0)
        {
            m = 200000;

            n = 1e3;
            X = (float *)malloc(n * sizeof(float));
            Y = (float *)malloc(m * sizeof(float));
            RandomVector(n, X);
            RandomVector(m, Y);
        }
        else if (strcmp(argv[1], "sgemv4") == 0)
        {
            m = 1e5;

            n = 1e3;
            X = (float *)malloc(m * sizeof(float));
            Y = (float *)malloc(n * sizeof(float));
            RandomVector(m, X);
            RandomVector(n, Y);
        }
        else
        {
            X = (float *)malloc(n * sizeof(float));
            Y = (float *)malloc(n * sizeof(float));
            RandomVector(n, X);
            RandomVector(m, Y);
        }
    }
    else
    {
        X = (double *)X;
        Y = (double *)Y;
        X = (double *)malloc(n * sizeof(double));
        Y = (double *)malloc(n * sizeof(double));
        RandomVector2(n, X);
        RandomVector2(n, Y);
    }
    if(strcmp(argv[1],"sgemm")==0 ||strcmp(argv[1],"sgemm2")==0||strcmp(argv[1],"sgemm3")==0||strcmp(argv[1],"sgemm4")==0||strcmp(argv[1],"sgemm5")==0||strcmp(argv[1],"sgemm6")==0||strcmp(argv[1],"sgemm7")==0||strcmp(argv[1],"sgemm8")==0)
    {
        RandomVector(m*n,A);
    }
    else if (strcmp(argv[1], "sgemv") == 0)
    {
        // n = 1e6;
        // m = 1e2;
        A = (float *)malloc(n * m * sizeof(float));
        RandomVector(n * m, A);
    }
    else if (strcmp(argv[1], "sgemv2") == 0)
    {

        A = (float *)malloc(m * n * sizeof(float));
        // printf("hello2");
        RandomVector(m * n, A);
    }
    else if (strcmp(argv[1], "sgemv3") == 0)
    {

        A = (float *)malloc(m * n * sizeof(float));
        // printf("hello2");
        RandomVector(m * n, A);
    }
    else if (strcmp(argv[1], "sgemv4") == 0)
    {

        A = (float *)malloc(m * n * sizeof(float));
        // printf("hello2");
        RandomVector(m * n, A);
    }

    srand((unsigned)time(NULL));

    tick(&calc);
    if (strcmp(argv[1], "sscal") == 0)
    {
        gflops = 1.0 * n * 1e-09;
        cblas_sscal(n, a, X, 1);
    }
    else if (strcmp(argv[1], "dscal") == 0)
    {
        gflops = 1.0 * n * 1e-09;
        cblas_dscal(n, b, X, 1);
    }
    // else if (argv[1]=="dscal")

    else if (strcmp(argv[1], "saxpy") == 0)
    {
        gflops = 2.0 * n * 1e-09;
        cblas_saxpy(n, a, X, 1, Y, 1);
    }
    else if (strcmp(argv[1], "daxpy") == 0)
    {
        gflops = 2.0 * n * 1e-09;
        cblas_daxpy(n, b, X, 1, Y, 1);
    }
    else if (strcmp(argv[1], "sgemv") == 0)
    {
        gflops = (2.0 * m * n + 2.0 * m) * 1e-09;
        /*float *ans=(float*)malloc(n*sizeof(float));
        for (int i=0;i<n;i++)
        {
            ans[i]=cblas_sdot(n,A+i*n*sizeof(float),1,X,1);
        }*/
        float c = 0.7;
        /*printf("%d\n",n);
        for(int i=0;i<n*m;i++)
        {
            printf("%f ",A[i]);
        }
        printf("\n");
        for(int i=0;i<m;i++)
        {
            printf("%f ",Y[i]);
        }
        printf("\n");
        for (int i = 0; i < n; i++)
        {
            printf("%f ", X[i]);
        }
        printf("\n");*/
        cblas_sgemv(CblasRowMajor, CblasNoTrans, m, n, a, A, n, X, 1, c, Y, 1);
        /*for(int i=0;i<n*m;i++)
        {
            printf("%f ",A[i]);
        }
        printf("\n");
        for(int i=0;i<m;i++)
        {
            printf("%f ",Y[i]);
        }
        printf("\n");
        for (int i = 0; i < n; i++)
        {
            printf("%f ", X[i]);
        }
        printf("\n");*/
    }
    else if (strcmp(argv[1], "sgemv2") == 0)
    {
        gflops = (2.0 * m * n + 2.0 * n) * 1e-09;

        float c = 0.7;
        // printf("hello");
        cblas_sgemv(CblasRowMajor, CblasTrans, m, n, a, A, n, X, 1, c, Y, 1);
    }
    else if (strcmp(argv[1], "sgemv3") == 0)
    {
        gflops = (2.0 * m * n + 2.0 * m) * 1e-09;

        float c = 0.7;
        // printf("hello");
        cblas_sgemv(CblasColMajor, CblasNoTrans, n, m, a, A, m, X, 1, c, Y, 1);
    }
    else if (strcmp(argv[1], "sgemv4") == 0)
    {
        gflops = (2.0 * m * n + 2.0 * n) * 1e-09;

        float c = 0.7;
        //printf("hello");
        cblas_sgemv(CblasRowMajor, CblasTrans, m, n, a, A, n, X, 1, c, Y, 1);
    }
    else if(strcmp(argv[1],"sgemm")==0)
    {
        gflops = (2.0 * m * n*k + 2.0 * n*m) * 1e-09;
        float c=0.7;
        cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, m, n, k, a, A, k, X, n, c, Y, n);
   
    }
    else if(strcmp(argv[1],"sgemm2")==0)
    {
        gflops = (2.0 * m * n*k + 2.0 * n*m) * 1e-09;
        float c=0.7;
        cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasTrans, m, n, k, a, A, k, X, n, c, Y, n);
   
    }
    else if(strcmp(argv[1],"sgemm3")==0)
    {
        gflops = (2.0 * m * n*k + 2.0 * n*m) * 1e-09;
        float c=0.7;
        cblas_sgemm(CblasRowMajor, CblasTrans, CblasNoTrans, m, n, k, a, A, k, X, n, c, Y, n);
   
    }
    else if(strcmp(argv[1],"sgemm4")==0)
    {
        gflops = (2.0 * m * n*k + 2.0 * n*m) * 1e-09;
        float c=0.7;
        cblas_sgemm(CblasRowMajor, CblasTrans, CblasTrans, m, n, k, a, A, k, X, n, c, Y, n);
   
    }
    else if(strcmp(argv[1],"sgemm5")==0)
    {
        gflops = (2.0 * m * n*k + 2.0 * n*m) * 1e-09;
        float c=0.7;
        cblas_sgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, m, n, k, a, A, k, X, n, c, Y, n);
   
    }
    else if(strcmp(argv[1],"sgemm6")==0)
    {
        gflops = (2.0 * m * n*k + 2.0 * n*m) * 1e-09;
        float c=0.7;
        cblas_sgemm(CblasColMajor, CblasNoTrans, CblasTrans, m, n, k, a, A, k, X, n, c, Y, n);
    }
    else if(strcmp(argv[1],"sgemm7")==0)
    {
        gflops = (2.0 * m * n*k + 2.0 * n*m) * 1e-09;
        float c=0.7;
        cblas_sgemm(CblasColMajor, CblasTrans, CblasNoTrans, m, n, k, a, A, k, X, n, c, Y, n);
    }
    else if(strcmp(argv[1],"sgemm8")==0)
    {
        gflops = (2.0 * m * n*k + 2.0 * n*m) * 1e-09;
        float c=0.7;
        cblas_sgemm(CblasColMajor, CblasTrans, CblasTrans, m, n, k, a, A, k, X, n, c, Y, n);
    }

    /*else if (strcmp(argv[1],"dgemv")==0)
    {
        gflops = 2.0 * n * 1e-09;
        cblas_dgemv(CblasRowMajor, CblasNoTrans, n, n, b, A, n, X, 1, a, Y, 1);
    }
    else if (strcmp(argv[1],"sgemm")==0)
    {
        gflops = 2.0 * n * n * 1e-09;
        cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, n, n, n, a, A, n, X, 1, b, Y, 1);
    }
    else if (strcmp(argv[1],"dgemm")==0)
    {
        gflops = 2.0 * n * n * 1e-09;
        cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, n, n, n, b, A, n, X, 1, a, Y, 1);
    }
    else if (strcmp(argv[1],"sgemm")==0)
    {
        gflops = 2.0 * n * n * 1e-09;
        cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, n, n, n, a, A, n, X, 1, b, Y, 1);
    }
    */

    calctime = tock(&calc);

    // Changes as per the problem
    float mem_bw;
    if (strcmp(argv[1], "saxpy") == 0)
    {
        mem_bw = (8.0 * n * 1e-09) / calctime;
    }
    if (strcmp(argv[1], "daxpy") == 0)
    {
        mem_bw = (16.0 * n * 1e-09) / calctime;
    }
    else if (strcmp(argv[1], "sscal") == 0)
    {
        mem_bw = (4.0 * n * 1e-09) / calctime;
    }
    else if (strcmp(argv[1], "dscal") == 0)
    {
        mem_bw = (8.0 * n * 1e-09) / calctime;
    }
    else if (strcmp(argv[1], "sgemv") == 0)
    {
        mem_bw = (4.0 * (m * n + m + n) * 1e-09) / calctime;
    }
    else if (strcmp(argv[1], "sgemv2") == 0)
    {
        mem_bw = (4.0 * (m * n + m + n) * 1e-09) / calctime;
    }
    else if (strcmp(argv[1], "sgemv3") == 0)
    {
        mem_bw = (4.0 * (m * n + m + n) * 1e-09) / calctime;
    }
    else if (strcmp(argv[1], "sgemv4") == 0)
    {
        mem_bw = (4.0 * (m * n + m + n) * 1e-09) / calctime;
    }
    else if (strcmp(argv[1], "sgemm") == 0)
    {
        mem_bw = (4.0 * (m * n + m*k + n*k) * 1e-09) / calctime;
    }
    else if (strcmp(argv[1], "sgemm2") == 0)
    {
        mem_bw = (4.0 * (m * n + m*k + n*k) * 1e-09) / calctime;
    }
    else if (strcmp(argv[1], "sgemm3") == 0)
    {
        mem_bw = (4.0 * (m * n + m*k + n*k) * 1e-09) / calctime;
    }
    else if (strcmp(argv[1], "sgemm4") == 0)
    {
        mem_bw = (4.0 * (m * n + m*k + n*k) * 1e-09) / calctime;
    }
    else if (strcmp(argv[1], "sgemm5") == 0)
    {
        mem_bw = (4.0 * (m * n + m*k + n*k) * 1e-09) / calctime;
    }
    else if (strcmp(argv[1], "sgemm6") == 0)
    {
        mem_bw = (4.0 * (m * n + m*k + n*k) * 1e-09) / calctime;
    }
    else if (strcmp(argv[1], "sgemm7") == 0)
    {
        mem_bw = (4.0 * (m * n + m*k + n*k) * 1e-09) / calctime;
    }
    else if (strcmp(argv[1], "sgemm8") == 0)
    {
        mem_bw = (4.0 * (m * n + m*k + n*k) * 1e-09) / calctime;
    }

    printf("Time (in milli-secs) %f\n", calctime * 1000);
    printf("Memory Bandwidth (in GBytes/s): %f\n", mem_bw);
    printf("Compute Throughput (in GFlops/s): %f\n", gflops / calctime);

    free(X);
    free(Y);
    free(A);
}
