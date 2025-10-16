#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {

    // 800 million elements; Nothing a modern machine can't handle, but enough
    // to time in ms (which is more stable than ns). Adjust if needed.
    long int arraySize = 800000000;

    // Allocate some arrays
    double* x = (double*) malloc((size_t) (arraySize * sizeof(double)));
    double* y = (double*) malloc((size_t) (arraySize * sizeof(double)));

    // Initialize x with some random junk
    for (int i = 0; i < arraySize; i++) {
        x[i] = ( (double) i ) / ( i + 1000 );
    }

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    // Compute values of y based on neighbours in x
    for (int i = 0; i < (arraySize-1); i++) {
        y[i] = (x[i]/x[i+1]) + (x[i+1]*2.14) - (x[i]/5.84);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    free(x);
    free(y);

    long long unsigned diff_ms  =
        (((double)end.tv_sec*1e9 + end.tv_nsec)
         - ((double)start.tv_sec*1e9 + start.tv_nsec))
        / 1000000;

    printf("Elapsed CPU time = %llu ms\n", diff_ms);
    return 0;
}
