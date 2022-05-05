#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>

#define _XOPEN_SOURCE
enum ImageType
{
    HD,
    UHD
};
void RandomMatrixImage(int h, int w, int k, float *A);
double tock(struct timeval *t);
void RandomVector(int n, float *A);
void tick(struct timeval *t);


void RandomMatrixImage(int h, int w, int k, float *A)
{
    int next_row = w + k - 1;
    for (int j = 0; j < h; j++)
    {
        for (int i = 0; i < w; ++i)
        {
            A[j*(next_row) +i] = (float) rand()/RAND_MAX;
            
        }
        for (int i = w; i < w + k - 1; i++)
        {
            A[j * (next_row) + i] = 0;
        }
    }
    for (int j = h; j < h + k - 1; j++)
    {
        for (int i = 0; i < w + k - 1; ++i)
        {
            A[j * next_row + i] = 0;
        }
    }
}
double tock(struct timeval *t)
{
    struct timeval now;
    gettimeofday(&now, NULL);
    return (double)(now.tv_sec - t->tv_sec) +
           ((double)(now.tv_usec - t->tv_usec) / 1000000.0);
}
void RandomVector(int n, float *A)
{
    for (int i = 0; i < n; i++)
    {
        A[i] = (float) rand()/RAND_MAX;
        
    }
}
void tick(struct timeval *t)
{
    gettimeofday(t, NULL);
}





int main(int argc, char *argv[])
{
    printf("Enter the image type (HD or UHD): \n");
    printf("h FOR HD\n");
    printf("u FOR UHD\n");
    struct timeval t0;
    char A;
    scanf("%c", &A);
    
    int k, w, h;
    
    
    for (int i = 0; i < 7; i++)
    {
        if(A!='h' && A!='u')
        {
            printf("Invalid input\n");
            return 0;
        }
        else if ( 'h'==A)
        {
            w = 1920;
            h = 1080;
            k = i+3;
            
        }
        else if ('u'==A)
        {
            w = 3840;
            h = 2160;
            k = i+3;
            
        }
        
        int actual_h = h + k - 1;
        int actual_w = w + k - 1;
        
        
        float *S = (float *)malloc(k * k * sizeof(float));
        float *Y = (float *)malloc(w * h * sizeof(float));
        float *X = (float *)malloc(actual_w * actual_h * sizeof(float));
        
        RandomVector(k * k, S);
        RandomMatrixImage(h, w, k, X);
        
        
        
        tick(&t0);
        
        for (int i = 0; i < h; i++)
        {
            for (int j = 0; j < w; j++)
            {
                Y[j+i*w] = 0.0;
                // #pragma omp simd
                for (int m = 0; m < k; m++)
                {
                    for (int n = 0; n < k; n++)
                    {
                       Y[i*w+j ] += X[j+n+(i + m) * (actual_w) ] * S[n+m * k ];
                    }
                }
                // Y[i * w + j] = temp;
            }
        }
        
        double calctime = tock(&t0);
        
        double mem_bw = ((8*h*w*k*k) / 1000000000.0) / calctime;
        double gflops = (2*h*w*k*k) / 1000000000.0;
        printf("%d %f\n", k,gflops/calctime);
        free(S);

        free(X);
        free(Y);
    }
    return 0;
}