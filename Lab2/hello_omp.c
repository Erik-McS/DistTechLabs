#include <omp.h>
#include <stdio.h>

int main (int argc, char* argv[]) {
    // Fork a team of threads
#pragma omp parallel
    {
        // Print id
        int tid = omp_get_thread_num();
        printf("Hello World from thread = %d\n", tid);

        // Only master thread does this
        if (tid == 0) {
            int nthreads = omp_get_num_threads();
            printf("Number of threads = %d\n", nthreads);
        }
    }  // All threads join master thread and terminate
}
