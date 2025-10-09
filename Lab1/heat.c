#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

// Model parameters
static float BARLEN = 100.0f;
static unsigned NCELLS = 100;
static float TIMESTEP = 0.05f;
static float MAXTIME = 200.0f;
static float TEMP_COEFFICIENT = 1.0f;
static unsigned PRINTEVERY = 20;

// Calculate the next temperature for a cell of size "dist", over timestep ts
float nextTemp(float ts, float dist,
               float currentT, float leftT, float rightT) {
    float f = (ts * TEMP_COEFFICIENT) / dist;
    float adjustment = f * (leftT - 2 * currentT + rightT);
    return currentT + adjustment;
}

void initialiseTemp(float* cells) {
    for (unsigned i = 0; i < NCELLS; i++) {
        cells[i] = 0.5 + 0.2 * sin(20 * i);
    }
}

void printBar(float* cells) {
    printf("-------\n");
    printf("|");
    for (unsigned i = 0; i < NCELLS; i++) {
        printf(" %0.3f |", cells[i]);
    }
    printf("\n-------\n");
}

int main() {
    float buf1[NCELLS];
    float buf2[NCELLS];
    float* cells = buf1;
    float* prev = buf2;

    initialiseTemp(cells);
    printBar(cells);

    unsigned steps = 0;
    for (float t = 0; t < MAXTIME; t += TIMESTEP, steps++) {
        // Flip current and prevous time step buffers
        float* tmp = prev;
        prev = cells;
        cells = tmp;

        for (unsigned i = 0; i < NCELLS; i++) {
            // Handle left boundary
            if (i == 0) {
                cells[i] = nextTemp(TIMESTEP, BARLEN/NCELLS, prev[i], 0, prev[i+1]);
                continue;
            }

            // Handle right boundary
            if (i == NCELLS-1) {
                cells[i] = nextTemp(TIMESTEP, BARLEN/NCELLS, prev[i], prev[i-1], 0);
                continue;
            }

            // Everything else
            cells[i] = nextTemp(TIMESTEP, BARLEN/NCELLS, prev[i], prev[i-1], prev[i+1]);
        }

        if (!(steps % PRINTEVERY)) {
            printBar(cells);
        }
    }

    printBar(cells);

    return 0;
}
