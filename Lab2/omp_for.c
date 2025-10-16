#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define CHUNKSIZE 10
#define N 100

int main (int argc, char *argv[]) {
    float a[N], b[N], c[N];

    // Initialise some random(ish) data
    for (int i = 0; i < N; i++) {
        a[i] = b[i] = i * 1.0;
    }

    // Create a workgroup
#pragma omp parallel shared(a,b,c)
    {
        int tid = omp_get_thread_num();
        // Run on "master" thread (arbitrary tid)
        if (tid == 0) {
            int nthreads = omp_get_num_threads();
            printf("Number of threads = %d\n", nthreads);
        }
        printf("Thread %d starting...\n",tid);

#pragma omp for schedule(dynamic, CHUNKSIZE)
        for (int i = 0; i < N; i++) {
            c[i] = a[i] + b[i];
            printf("Thread %d: c[%d] = %f\n",tid,i,c[i]);
        }
    }  /* end of parallel section */
}
