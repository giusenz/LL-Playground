#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include <stdatomic.h>

#include <semaphore.h>
#define LOCK(m)   pthread_mutex_lock(m)
#define UNLOCK(m) pthread_mutex_unlock(m)
#define P(sem)    sem_wait(sem)
#define V(sem)    sem_post(sem)   

#define THINKING  0
#define HUNGRY    1 
#define EATING    2

typedef struct threadArgs {
    int thid;
    int N;
    int* state;
    sem_t **sem;
    pthread_mutex_t *m;
} threadArgs_t;

static atomic_long ITER = 2000;

static inline long atomicDec(atomic_long *v) {
    return atomic_fetch_sub(v,1) -1;
}

void Mangia(int myid, unsigned int *seed) {
    fprintf(stdout, "%d -- Mangio\n", myid);
    
    long r = rand_r(seed) % 800000;
    struct timespec t={0, r};
    nanosleep(&t,NULL);
    
    fprintf(stdout, "%d -- Finito di mangiare\n", myid);
}

void Pensa(int myid, unsigned int *seed) {
    fprintf(stdout, "%d -- Penso\n", myid);
    
    long r = rand_r(seed) % 1000000;
    struct timespec t={0, r};
    nanosleep(&t,NULL);
    
    fprintf(stdout, "%d -- Finito di pensare\n", myid);
}

void *Filosofo(void *arg) {
    int   myid   = ((threadArgs_t*)arg)->thid;
    int   N      = ((threadArgs_t*)arg)->N;
    int   *state = ((threadArgs_t*)arg)->state;
    
    sem_t        **sem = ((threadArgs_t*)arg)->sem;
    pthread_mutex_t *m = ((threadArgs_t*)arg)->m;
    
    unsigned int seed = myid * time(NULL);
    
    int mangia = 0;
    int pensa  = 0;
    
    while (1) {
        if (atomicDec(&ITER) <= 0) break;
        
        int l = myid + N - 1;
        int r = myid + N + 1;
        
        Pensa(myid, &seed);
        ++pensa;
        LOCK(m);
        state[myid] = HUNGRY;
        while (state[l % N] == EATING || state[r % N] == EATING) {
            UNLOCK(m);
            P(sem[myid]);
            LOCK(m);
        }
        state[myid] = EATING;
        UNLOCK(m);
    
        ++mangia;
        Mangia(myid, &seed);
    
        LOCK(m);
        state[myid] = THINKING;
        if (state[l % N] == HUNGRY && state[(l - 1) % N] != EATING) {
            V(sem[l % N]);
        }
        if (state[r % N] == HUNGRY && state[(r + 1) % N] != EATING) {
            V(sem[r % N]);
        }
        UNLOCK(m);
    }
    fprintf(stdout, "Filosofo %d:  ho mangiato %d volte e pensato %d volte\n", myid, mangia, pensa);
    fflush(stdout);
    return (NULL);
}

int main(int argc, char *argv[]) {
    int N = 5;
    if (argc > 1) {
	    N = atoi(argv[1]);
	    if (N < 2) {
	        fprintf(stderr, "N deve essere >= 2\n");
	        exit(EXIT_FAILURE);
	    }
	    if (N > 100) {
	        fprintf(stderr, "N ridotto a 100\n");
	        N = 100;
	    }
    }

    pthread_t *th        = malloc(N * sizeof(pthread_t));
    threadArgs_t *thARGS = malloc(N * sizeof(threadArgs_t));
    
    int   *state   = malloc(N * sizeof(int));
    sem_t **semarr = malloc(N * sizeof(sem_t *));
    for (int i = 0; i < N; i++) semarr[i] = malloc(sizeof(sem_t));

    pthread_mutex_t *mutex = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(mutex, NULL);

    for (int i = 0; i < N; i++) {
        state[i] = THINKING;
        sem_init(semarr[i], 0, 0);
    }

    for (int i = 0; i < N; i++) {
        thARGS[i].thid  = i;
        thARGS[i].N     = N;
        thARGS[i].state = state;
        thARGS[i].sem   = semarr;
        thARGS[i].m     = mutex;
        pthread_create(&th[i], NULL, Filosofo, &thARGS[i]);
    }

    for (int i = 0; i < N; i++) pthread_join(th[i], NULL);

    free(state);
    free(th);
    for (int i = 0; i < N; i++) {sem_destroy(semarr[i]); free(semarr[i]);}
    free(semarr);
    free(thARGS);
    pthread_mutex_destroy(mutex);
    free(mutex);
    
    return (0);
}













