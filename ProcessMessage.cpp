#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#define LEFT (nemo + 4) % 5
#define RIGHT (nemo + 1) % 5


sem_t simo;
sem_t boo[5];  

enum Declare{
 EATING , HUNGRY , THINKING
};

struct Philosopher{
    char * name;
    int id;
};

struct Philosopher P[5] = {{"Philosopher 1", 0},{"Philosopher 2", 1},{"Philosopher 3", 2},{"Philosopher 4", 3},{"Philosopher 5", 4}};

int pflag[5];

void test(int nemo)
{
    if ( pflag[LEFT] != EATING && pflag[RIGHT] != EATING){
        
        pflag[nemo] = EATING;
 
        sleep(2);
        printf("**********************\n");
        printf("Philosopher %s ,id : %d,\n Picking up Chopsticks %d and %d  \n",P[nemo].name, nemo + 1, LEFT + 1, nemo + 1);
        printf("**********************\n\n");

        printf("**********************\n");
        printf("Philosopher %s , id : %d, is Eating.\n",P[nemo].name, nemo + 1);
        printf("**********************\n\n");
        sem_post(&boo[nemo]);
    }
}

void take_chopsticks(int nemo)
{
 
    sem_wait(&simo);

    pflag[nemo] = HUNGRY;

    printf("**********************\n");
    printf("Philosopher %s , id : %d, is Hungry.\n",P[nemo].name, nemo + 1);
    printf("**********************\n\n");

    test(nemo); 
    sem_post(&simo);
 
    sem_wait(&boo[nemo]);
 
    sleep(1);
}
 
void drop_chopsticks(int nemo)
{
    sem_wait(&simo);
 
    pflag[nemo] = THINKING;
    printf("**********************\n");
    printf("Philosopher %s , id : %d, puting down Chopsticks %d and %d \n", P[nemo].name, nemo + 1, LEFT + 1, nemo + 1);
    printf("....................................................................\n");
    printf("Philosopher %s , id : %d, is thinking. \n",P[nemo].name, nemo + 1);
    printf("**********************\n\n");

    test(LEFT);
    test(RIGHT);
    sem_post(&simo);
}
 
void* philospher(void* num)
{   
    while (1) {
        int  i = (int)num;
        sleep(1);
        take_chopsticks(i) ;
        sleep(0);
        drop_chopsticks(i);
    }
}
 
int main()
{
    pthread_t Thread[5];
 
    sem_init(&simo, 0, 1);

    for (int i = 0; i < 5; i++){
        sem_init(&boo[i], 0, 0);
    }
   
   
    for (int i = 0; i < 5; i++) {
        pthread_create(&Thread[i], NULL,philospher, (void*)P[i].id);
        printf("**********************\n");
        printf("Philosopher %s , id : %d, is thinking. \n",P[i].name, i + 1);
        printf("**********************\n");
    }
 
    for (int i = 0; i < 5; i++){
        pthread_join(Thread[i], NULL);
    }
    return 0;
}
