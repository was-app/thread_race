#include "race.h"

int finished = 0;
pthread_mutex_t finished_lock = PTHREAD_MUTEX_INITIALIZER;

char* teams[] = {
        "Cruzeiro", "Atletico", "Flamengo", "Vasco",
        "Corinthians", "Palmeiras", "Gremio", "Internacional",
        "Sao Paulo", "Santos", "Fluminense", "Botafogo"
    };

team_t create_team(char* name){
    team_t temp = {0};
    strcpy(temp.name,name);
    temp.time = 0.0;
    temp.counter = 0;
    return temp;
}

void *race(void *cur_team){
    clock_t start = clock();
    team_t* r = (team_t*) cur_team;
    while(r->counter < TARGET){
        double number = (double)rand() / RAND_MAX;
        if (number > 0.2)
            r->counter++;
    }
    clock_t end = clock();
    r->time = (double)(end - start) / CLOCKS_PER_SEC;

    pthread_mutex_lock(&finished_lock);
    finished++;
    printf("%d : %s, with a time of %f seconds\n",finished, r->name, r->time);
    pthread_mutex_unlock(&finished_lock);

    pthread_exit(NULL);
}

int main(){
    srand(time(NULL));
    team_t teams_list[TEAMS];
    for (int i=0;i<TEAMS;i++) {
        teams_list[i] = create_team(teams[i]);
        if (pthread_create(&teams_list[i].thread, NULL, race, &teams_list[i]) != 0) 
            return 1;
    }
    for (int i=0;i<TEAMS;i++)
        pthread_join(teams_list[i].thread, NULL);

}