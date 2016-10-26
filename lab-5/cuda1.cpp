#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cuda.h>
#include <iostream>

using namespace std;


_ _global_ _
void vecAddKernel(float* A, float* B, float* C, int n)
{
    int i = threadIdx.x + blockDim.x * blockIdx.x;
    if(i<n) C[i] = A[i] + B[i];
}

void print_vec(float* vector, int size)
{
    for(int i=0; i<n; i++)
        cout << vector[i] << " ";
    cout<<endl;
}

void vecAdd(float* A, float* B, float* C, int n)
{
    int size = n * sizeof(float);
    A = (double*)malloc(size);
    B = (double*)malloc(size);
    C = (double*)malloc(size);
    for( int i = 0; i < n; i++ ) {
        A[i] = sin(i)*sin(i);
        B[i] = cos(i)*cos(i);
    }

    float *d_A, *d_B, *d_C;

    cudaMalloc((void **) &d_A, size);
    cudaMemcpy(d_A, A, size, cudaMemcpyHostToDevice);

    cudaMalloc((void **) &d_B, size);
    ccudaMemcpy(d_B, B, size, cudaMemcpyHostToDevice);

    cudaMalloc((void **) &d_C, size);
    vecAddKernel<<<ceil(n/2560), 256>>> vecAddKernel<<<ceil(n/2560), 256>>>(d_A, d_B, d_C, n); (d_A, d_B, d_C, n);
    cudaMemcpy(C, d_C, size, cudaMemcpyDeviceToHost);
    // Free device memory for A, B, C
    cudaFree(d_Ad); cudaFree(d_B); cudaFree (d_C);
    print_vec(C, size);
}

void  main()
{
    // Size of vectors
    int n = 100000;
 
    // Host input vectors
    double *h_a;
    double *h_b;
    //Host output vector
    double *h_c;

    vecAdd(h_a, h_b, h_c);
}