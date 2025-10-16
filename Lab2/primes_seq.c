#include <stdio.h>
#include <time.h>

// returns 1 if argument is prime, 0 if not
// NOT an efficient prime calculator; do not use in real code!
int is_prime(unsigned long number) {
    unsigned long tNum;
    unsigned long tLim;

    if (number == 1 || number == 2) {
        return 1;
    }
    if ((number % 2) == 0) {
        return 0;
    }

    // Reminder: (initialisers, condition, incrementers)
    // Can have multiple expressions for each, as used here.
    for (tNum = 3, tLim = number; tLim > tNum; tLim = number / tNum, tNum += 2) {
        if ((number % tNum) == 0) {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char *argv[]) {
    unsigned long limit = 100;
    unsigned long count = 0;

    // Let the user specify the limit they want
    if (argc > 2) {
        fprintf(stderr, "usage: ./primes [limit]\n");
        return -1;
    } else if (argc == 2) {
        sscanf(argv[1], "%lu", &limit);
    }

    printf("Computing up to limit: %lu\n", limit);

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 1; i < limit; i++) {
        if (is_prime(i)) {
            count++;
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    long long unsigned diff_ms  =
        (((double)end.tv_sec*1e9 + end.tv_nsec)
         - ((double)start.tv_sec*1e9 + start.tv_nsec))
        / 1000000;

    printf("%lu primes computed in %llu ms, %llu ms per prime (avg)\n",
           count, diff_ms, diff_ms / limit);

    return 0;
}
