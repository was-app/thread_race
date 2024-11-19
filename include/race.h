#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define RACERS_COUNT 8
#define TARGET 500000

typedef struct{
    int id;
    float time;
    int counter;
    pthread_t thread;
}racer;


racer create_racer(int id);
void *race(void *racer);
