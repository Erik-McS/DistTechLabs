#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <pthread.h>

// Model parameters
static float BARLEN = 100.0f;
static unsigned NCELLS = 100;
static float TIMESTEP = 0.05f;
static float MAXTIME = 200.0f;
static float TEMP_COEFFICIENT = 1.0f;
static unsigned PRINTEVERY = 20;
static unsigned char CHUNK = 25;


// struct for parameters to threads
typedef struct {
    unsigned char start;
    unsigned char end;
    float* cells;
    float* prev;
} tArgs;

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

void* heatCells(void* arg){

        tArgs* args = (tArgs*)arg;

        for (unsigned i = args->start; i <= args->end; i++) {
        // Handle left boundary
            if (i == 0) {
                args->cells[i] = nextTemp(TIMESTEP, BARLEN/NCELLS, args->prev[i], 0, args->prev[i+1]);
                continue;
            }

            // Handle right boundary
            if (i == NCELLS-1) {
                args->cells[i] = nextTemp(TIMESTEP, BARLEN/NCELLS, args->prev[i], args->prev[i-1], 0);
                continue;
            }

            // Everything else
            args->cells[i] = nextTemp(TIMESTEP, BARLEN/NCELLS, args->prev[i], args->prev[i-1], args->prev[i+1]);
        }
}

int main() {
    float buf1[NCELLS];
    float buf2[NCELLS];
    float* cells = buf1;
    float* prev = buf2;
    char accu = 0;

    pthread_t workers[NCELLS/CHUNK];

    initialiseTemp(cells);
    // printBar(cells);

    unsigned steps = 0;
    //for (float t = 0; t < MAXTIME; t += TIMESTEP, steps++) {
        // Flip current and prevous time step buffers
        float* tmp = prev;
        prev = cells;
        cells = tmp;
        int nThreads = NCELLS/CHUNK;


        for(unsigned i=0;i<(NCELLS/CHUNK)-1;i++){
            tArgs* args = malloc(sizeof(tArgs));

            args->start = i * CHUNK;
            args->end = (i+1) * CHUNK-1;
            args->cells = cells;
            args->end;

            printf("Start %d , End: %d \n",args->start,args->end);

            pthread_create(&workers[i],NULL,heatCells,&args);
        }

        /*



        if (!(steps % PRINTEVERY)) {
            printBar(cells);
        }
    }
        */
    //printBar(cells);

    return 0;
    
}
