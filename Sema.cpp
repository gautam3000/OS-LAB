#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
using namespace std;

int resources = 5;
sem_t semaphor;

void * firstFunction(void *) {
    int q;
    sem_getvalue(&semaphor, &q);
    cout << "Semaphore F1 = " << q << endl << endl;
    while (q <= 0)
        ;

    cout << "Lock acquired on semaphore, in First Function" << endl
         << endl;
    sem_wait(&semaphor);
    resources++;
    sleep(2);
    sem_post(&semaphor);
    cout << "Lock released on semaphore, in First Function" << endl;
    cout << "Current value of resources is " << resources << ", in First Function" << endl;
}

void * secondFunction(void *) {
    int p;
    sem_getvalue(&semaphor, &p);
    cout << "Semaphore F2 = " << p << endl << endl;
    while (p <= 0)
        ;
    cout << "Lock acquired on semaphore, in Second Function" << endl
         << endl;
    sem_wait(&semaphor);
    resources--;
    sleep(2);
    sem_post(&semaphor);
    cout << "Lock released on semaphore, in Second Function" << endl;
    cout << "Current value of resources is " << resources << ", in Second Function" << endl;
    
}
int main() {
    pthread_t thread1, thread2;
    sem_init( & semaphor, 0, 1);
    int sg;
    sem_getvalue(&semaphor, &sg);
    cout << "Corrent value of the semaphore = " << sg<<endl;
    
    int i = 3;
    while (i--)
    {
        pthread_create( & thread1, NULL, firstFunction, NULL);
        pthread_create( & thread2, NULL, secondFunction, NULL);
        sleep(5);
        cout << endl
             << "Loop = " << i << endl
             << endl;
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    cout << "Current value of resources = " << resources << endl;
  
    return 0;
}
