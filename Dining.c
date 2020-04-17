#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#define end "\n"
#define LEFT (PhilNum + 4) % 5
#define RIGHT (PhilNum + 1) % 5

//semaphore declaration
sem_t quantum;
sem_t boo[5];  


//three states of philosophers
enum anvi{
 EATING , HUNGRY , THINKING
};

struct Philosopher{
    char * name;
    int id;
};

//giving the values to the struct
struct Philosopher P[5]={
    {
        "Professor A",0
    },
    {
        "Professor B",1
    },
    {
        "Professor C",2
    },
    {
        "Professor D",3
    },
    {
        "Professor E",4
    }
};

//philosopher flag = globle decleration for the current state of every professer.
int pflag[5];

 
void test(int PhilNum)
{
    if ( pflag[LEFT] != EATING && pflag[RIGHT] != EATING){
        
        pflag[PhilNum] = EATING;
 
        sleep(2);
        printf("....................................................................\n");
        printf(">>> Philosopher %s ,id : %d,\n Picking up Chopsticks %d and %d  \n",P[PhilNum].name, PhilNum + 1, LEFT + 1, PhilNum + 1);
        printf("....................................................................\n\n");

        printf("....................................................................\n");
        printf(">>> Philosopher %s , id : %d, is Eating.\n",P[PhilNum].name, PhilNum + 1);
        printf("....................................................................\n\n");
        sem_post(&boo[PhilNum]);
    }
}

void take_chopsticks(int PhilNum)
{
 
    sem_wait(&quantum); /* critical section */

    pflag[PhilNum] = HUNGRY;

    printf("....................................................................\n");
    printf(">>> Philosopher %s , id : %d, is Hungry.\n",P[PhilNum].name, PhilNum + 1);
    printf("....................................................................\n\n");

    test(PhilNum); 
    sem_post(&quantum); /* end critical section */
 
    // if unable to eat wait to be signalled
    sem_wait(&boo[PhilNum]); /* Eat if enabled */
 
    sleep(1);
}
 
void drop_chopsticks(int PhilNum)
{
    sem_wait(&quantum); /* critical section */
 
    pflag[PhilNum] = THINKING;
    printf("....................................................................\n");
    printf(">>> Philosopher %s , id : %d, puting down Chopsticks %d and %d \n", P[PhilNum].name, PhilNum + 1, LEFT + 1, PhilNum + 1);
    printf("....................................................................\n");
    printf(">>> Philosopher %s , id : %d, is thinking. \n",P[PhilNum].name, PhilNum + 1);
    printf("....................................................................\n\n");

    test(LEFT); /* Let phil. on left eat if possible */
    test(RIGHT); /* Let phil. on rght eat if possible */
    sem_post(&quantum); /* up critical section */
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
 
    // initialize the values to the semaphores

    //initially to 1, for mutual exclusion
    sem_init(&quantum, 0, 1);
 
    //semaphore boo[5] will be initially 0, for synchronization
    for (int i = 0; i < 5; i++){
        sem_init(&boo[i], 0, 0);
    }
   
   
    // creating philosopher processes
   
    for (int i = 0; i < 5; i++) {
        pthread_create(&Thread[i], NULL,philospher, (void*)P[i].id);
        printf("....................................................................\n");
        printf(">>> Philosopher %s , id : %d, is thinking. \n",P[i].name, i + 1);
        printf("....................................................................\n");
    }
 
    for (int i = 0; i < 5; i++){
        pthread_join(Thread[i], NULL);
    }
    return 0;
}
