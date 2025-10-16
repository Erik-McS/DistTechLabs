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
/*
The reduction clause is used when you have a loop that updates a variable cumulatively, like a sum, product, min, max, etc., and you want to do it safely in parallel.

Without reduction, if multiple threads update the same variable, you get race conditions.

With reduction, OpenMP:
    -Gives each thread its own private copy of the variable.
    -Performs the loop in parallel.
    -Combines all the private copies into a single result at the end, using the specified operator.
*/
#pragma omp parallel for                        \
    schedule(static,CHUNK)                      \
    reduction(+:result)
    for (int i = 0; i < N; i++) {
        result = result + (a[i] * b[i]);
    }

    printf("Final result = %f\n",result);
}
