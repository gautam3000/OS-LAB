#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
using namespace std;

int resources = 5;
sem_t semaphor;

void * F1(void *) {
    int a;
    sem_getvalue(&semaphor, &a);
    cout << "Semaphore F1 = " << a << endl << endl;
    while (a <= 0)
        ;

    cout << "Lock obtain, in F1" << endl
         << endl;
    sem_wait(&semaphor);
    resources++;
    sleep(2);
    sem_post(&semaphor);
    cout << "Lock free on semaphore, in f1" << endl;
    cout << "Current value  is " << resources << ", in F1" << endl
}

void * F2(void *) {
    int b;
    sem_getvalue(&semaphor, &b);
    cout << "Semaphore F2 = " << b << endl << endl;
    while (b <= 0)
        ;
    cout << "Lock obtain, in F2" << endl
         << endl;
    sem_wait(&semaphor);
    resources--;
    sleep(2);
    sem_post(&semaphor);
    cout << "Lock free on semaphore, in f2" << endl;
    cout << "Current value is " << resources << ", in f2" << endl;
    
}
int main() {
    pthread_t thread1, thread2;
    sem_init( & semaphor, 0, 1);
    int sg;
    sem_getvalue(&semaphor, &sg);
    cout << "Current value of the semaphore = " << sg<<endl;
    
    int j = 3;
    while (j--)
    {
        pthread_create( & thread1, NULL, F1, NULL);
        pthread_create( & thread2, NULL, F2, NULL);
        sleep(5);
        cout << endl
             << "Loop = " << j << endl
             << endl;
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    cout << "Current value is = " << resources << endl;
  
    return 0;
}
