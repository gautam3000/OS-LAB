#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
using namespace std;

int resources = 5;
sem_t sema;

void * f1(void *) {
    int a;
    sem_getvalue(&sema, &a);
    cout << "Semaphore F1 = " << a << endl << endl;
    while (a <= 0)
        ;

    cout << "Lock acquired , in f1" << endl
         << endl;
    sem_wait(&sema);
    resources++;
    sleep(2);
    sem_post(&sema);
    cout << "Lock released, in f1" << endl;
    cout << "Current value is " << resources << ", in f1" << endl;
}

void * f2(void *) {
    int b;
    sem_getvalue(&sema, &b);
    cout << "Semaphore F2 = " << b << endl << endl;
    while (b <= 0)
        ;
    cout << "Lock acquired, in f2" << endl
         << endl;
    sem_wait(&sema);
    resources--;
    sleep(2);
    sem_post(&sema);
    cout << "Lock released, in f2" << endl;
    cout << "Current value is " << resources << ", in f2" << endl;
    
}
int main() {
    pthread_t thread1, thread2;
    sem_init( & sema, 0, 1);
    int sg;
    sem_getvalue(&sema, &sg);
    cout << "Current value  = " << sg<<endl;
    
    int j = 3;
    while (j--)
    {
        pthread_create( & thread1, NULL, f1, NULL);
        pthread_create( & thread2, NULL, f2, NULL);
        sleep(5);
        cout << endl
             << "Loop = " << j-- << endl
             << endl;
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    cout << "Current value of resources = " << resources << endl;
  
    return 0;
}
