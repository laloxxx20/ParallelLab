#include "stdafx.h"
#include <stdio.h>
#include <cuda.h>

_global_ 
void thirdDimentionalKernel(float* d_in, float* d_out, int n, int m, int p) 
{
       int row = blockIdx.y*blockDim.y + threadIdx.y;
       int col = blockIdx.x*blockDim.x + threadIdx.x;
       int plane = blockIdx.z*blockDim.z + threadIdx.z;
       
       if ((plane < p)  && (col < n) && (row < m)) 
               d_Pout[plane * m * n + row * n + Col] = 2 * d_in[plane * m * n +row * n + Col];
}

void thirdDimentionalOperation(float* in ,float* out, int n, int m, int p)
{
       int size = p * m * n * sizeof(float);
       float* d_in, * d_out;

       cudaMalloc((void **) &d_in, size);
       cudaMalloc((void **) &d_out, size);
       
       cudaMemcpy(d_in, in, size, cudaMemcpyHostToDevice);
       
       thirdDimentionalKernel<<<(ceil(n/16), ceil(m/16), ceil(p/16)),(16, 16, 16)>>>(d_in, d_out, n, m, p);
               
       cudaMemcpy(out, d_out, size, cudaMemcpyDeviceToHost);
       
       cudaFree(d_in); 
       cudaFree(d_out);
}

void initMat(float* mat, int n) {
    int i, j;
    for(i=0; i<n; i++)
        for(j=0; j<n; j++)
            mat[i*n+j] = rand() % 9 + 1;
}

void printMat(float *a, int n) {
    int i, j;
    for(int i=0; i<n; i++){
        for (int j=0; j<n; j++)
            cout<< a[i*n+j] << " ";
    cout<<endl;
    }    
}

int main(int argc, char const *argv[])
{
      int n = 100;
      float* in;
      float* out;

      initMat(in, n);
      initMat(out, n);

      thirdDimentionalOperation();
      printMat(out, n);
      return 0;
}