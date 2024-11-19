#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <string.h>

#define TEAMS 12
#define TARGET 500000

typedef struct{
    char name[20];
    float time;
    int counter;
    pthread_t thread;
}team_t;


team_t create_racer(char* name);
void *race(void *team);
