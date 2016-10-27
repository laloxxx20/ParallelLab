#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cuda.h>
#include <iostream>

using namespace std;


void initArray(float* vec, int n) {
    int i;
    for(i=0; i<n; i++)
        vec[i] = rand() % 9 + 1;
}

void initMat(float* mat, int n) {
    int i, j;
    for(i=0; i<n; i++)
        for(j=0; j<n; j++)
            mat[i*n+j] = rand() % 9 + 1;
}

void printVec(float* vector, int size)
{
    for(int i=0; i<n; i++)
        cout << vector[i] << " ";
    cout<<endl;
}

void printMat(float *a, int n) {
    int i, j;
    for(int i=0; i<n; i++){
        for (int j=0; j<n; j++)
            cout<< a[i*n+j] << " ";
    cout<<endl;
    }    
}

__global__
void mulKernel(float *vec, float *mat, float *C, int n)
{
    int tid = threadIdx.x + blockDim.x * blockIdx.x ;
    float sum=0;

    if(tid < n){
        for(int i=0; i<n; i++)
            sum += vec[i]*mat[(i*n) + tid];
        C[tid]=sum;
    }
}

void mulVecMat(float* vec, float* mat, int n){
    float* c;
    float* dev_a, * dev_b, * dev_c;

    vec = (float*)malloc(sizeof(float)*n);
    mat = (float*)malloc(sizeof(float)*n*n);
    c = (float*)malloc(sizeof(float)*n);

    printVec(a, n);
    printMat(b, n);
    printVec(c, n);

    cudaMalloc((void**)&dev_a, sizeof(float)*n);
    cudaMalloc((void**)&dev_b, sizeof(float)*n*m);
    cudaMalloc((void**)&dev_c, sizeof(float)*m);

    cudaMemcpy(dev_a, a, sizeof(float)*n, cudaMemcpyHostToDevice);
    cudaMemcpy(dev_b, b, sizeof(float)*n*n, cudaMemcpyHostToDevice);

    mulKernel<<<ceil(n/2560), 256>>>(dev_a, dev_b, dev_c, n);

    cudaMemcpy(c, dev_c, sizeof(float)*n, cudaMemcpyDeviceToHost);

    cudaFree(dev_a);
    cudaFree(dev_b);
    cudaFree(dev_c);
    
    printMat(c, n);
}
