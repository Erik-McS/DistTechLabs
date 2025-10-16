#include <omp.h>
#include <stdio.h>

#define N 100
#define CHUNK 10

int main (int argc, char* argv)  {
    float a[N], b[N];

    // Generate some random data
    for (int i = 0; i < N; i++) {
        a[i] = i * 1.0;
        b[i] = i * 2.0;
    }

    float result = 0.0f;
#pragma omp parallel for                        \
    schedule(static,CHUNK)                      \
    reduction(+:result)
    for (int i = 0; i < N; i++) {
        result = result + (a[i] * b[i]);
    }

    printf("Final result = %f\n",result);
}
