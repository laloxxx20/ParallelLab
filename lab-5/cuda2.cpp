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

void initMat(float* mat, int n, int m) {
    int i, j;
    for(i=0; i<n; i++)
        for(j=0; j<m; j++)
            mat[i*m+j] = rand() % 9 + 1;
}

void printVec(float* vector, int size)
{
    for(int i=0; i<n; i++)
        cout << vector[i] << " ";
    cout<<endl;
}

void printMat(float *a, int n, int m) {
    int i, j;
    for(int i=0; i<n; i++){
        for (int j=0; j<m; j++)
            cout<< a[i*m+j] << " ";
    cout<<endl;
    }    
}

__global__
void mulKernel(float *vec, float *mat, float *C, int n, int m)
{
    int tid = threadIdx.x + blockDim.x * blockIdx.x ;
    float sum=0;

    if(tid < m){
        for(int i=0; i<n; i++)
            sum += vec[i]*mat[(i*m)+tid];
        C[tid]=sum;
    }
}

void mulVecMat(float* vec, float* mat, int n){

}
