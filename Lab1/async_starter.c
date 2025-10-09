#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "future_starter.c"

void* foo(void*) {
    unsigned* myInt = malloc(sizeof(unsigned));
    myInt = 42;
    return myInt;
}

// Arguments to pass to the thread
struct targs {
    Future* f; // Future to write the results to
    void*(*func)(void*); // Function to execute
    void* fnargs; // Arguments for the function
};

void* thread_runner(void* args) {
    struct targs* as = args;
    // What else does the thread need to do
}

Future* async(void*(*fn)(void*), void* args) {
    // TODO Careful with memory management: async might return before the thread
    // executes so anything passed to it needs to remain alive (i.e. on the heap)
}

int main() {
    Future* f = async(foo, NULL);
    int* v = get_future(f);
    printf("Got %d\n", *v);
    free(v); free(f);
}
