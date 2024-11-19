#include "race.h"

int finished = 0;
pthread_mutex_t finished_lock = PTHREAD_MUTEX_INITIALIZER;

racer create_racer(int id){
    racer temp;
    temp.id = id;
    temp.time = 0.0;
    temp.counter = 0;
    return temp;
}

void *race(void *cur_racer){
    clock_t start = clock();
    racer* r = (racer*) cur_racer;
    while(r->counter < TARGET){
        double number = (double)rand() / RAND_MAX;
        if (number > 0.2)
            r->counter++;
    }
    clock_t end = clock();
    r->time = (double)(end - start) / CLOCKS_PER_SEC;

    pthread_mutex_lock(&finished_lock);
    finished++;
    printf("Racer %d has finished the race in %d place, with a time of %f seconds\n",r->id, finished, r->time);
    pthread_mutex_unlock(&finished_lock);

    pthread_exit(NULL);
}

int main(){
    srand(time(NULL));
    racer racers_list[RACERS_COUNT];
    for (int i=0;i<RACERS_COUNT;i++) {
        racers_list[i] = create_racer(i);
        if (pthread_create(&racers_list[i].thread, NULL, race, &racers_list[i]) != 0) 
            return 1;
    }
    for (int i=0;i<RACERS_COUNT;i++)
        pthread_join(racers_list[i].thread, NULL);

}