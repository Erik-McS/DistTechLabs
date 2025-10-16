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
// parallel block, the 3 arrays are shared.    
#pragma omp parallel for shared(a,b,c) schedule(dynamic, CHUNKSIZE)
    {
        //get thread ID
        int tid = omp_get_thread_num();
        // Run on "master" thread (arbitrary tid)
        if (tid == 0) {
            int nthreads = omp_get_num_threads();
            printf("Number of threads = %d\n", nthreads);
        } 
        printf("Thread %d starting...\n",tid);
/*
        omp for: divide the for iterations in chunksize ( 10 here, )
        schedule is used to tell openMP how to run the loop
        - dynamic: assign chunks to the first free threads

*/

        for (int i = 0; i < N; i++) {
            c[i] = a[i] + b[i];
            printf("Thread %d: c[%d] = %f\n",tid,i,c[i]);
        }

    }

}

/*
grouping for readability

awk '
  /^Thread [0-9]+ starting/ { thread = $2; gsub(":", "", thread); buffer[thread] = buffer[thread] $0 "\n"; next }
  /^Thread [0-9]+:/ { thread = $2; gsub(":", "", thread); buffer[thread] = buffer[thread] $0 "\n" }
  END { for (i=0; i<8; i++) printf "%s", buffer[i] }
' output.txt > grouped_omp_for.txt


*/