#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define N 100000000

void add(float* out, float* a, float* b) {
    int tid = omp_get_thread_num();
    printf("Thread %d doing add\n",tid);

#pragma omp task
{
    int tid = omp_get_thread_num();
    printf("Thread %d doing add half\n",tid);
    for (int i = 0; i < N/2; i++) {
        out[i] = a[i] + b[i];
    }
}

#pragma omp task
{
    int tid = omp_get_thread_num();
    printf("Thread %d doing add half\n",tid);
    for (int i = N/2; i < N; i++) {
        out[i] = a[i] + b[i];
    }
}

#pragma omp taskwait
} // add

void mul(float* out, float* a, float* b) {
    int tid = omp_get_thread_num();
    printf("Thread %d doing mul\n",tid);
    for (int i = 0; i < N; i++) {
        out[i] = a[i] * b[i];
    }
}

int main (int argc, char *argv[]) {
    float *a, *b, *c, *d;
    a = malloc(sizeof(float) * N);
    b = malloc(sizeof(float) * N);
    c = malloc(sizeof(float) * N);
    d = malloc(sizeof(float) * N);

    // Initialise some random(ish) data
    for (int i = 0; i < N; i++) {
        a[i] = i * 1.5;
        b[i] = i + 22.35;
        c[i] = d[i] = 0.0;
    }

#pragma omp parallel shared(a,b,c,d)
    {
        // One thread only executes this. Other threads can execute the created tasks
#pragma omp single
        {
            int tid = omp_get_thread_num();
            printf("Thread %d launching tasks\n",tid);

#pragma omp task
        add(c, a, b);

#pragma omp task
        mul(c, a, b);

#pragma omp task
        add(d, a, b);

#pragma omp task
        mul(d, a, b);
        }  // end tasks

    }  // end parallel (threads waiting here will steal work)
    free(a); free(b); free(c); free(d);
}
