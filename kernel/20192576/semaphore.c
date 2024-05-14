#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <semaphore.h>

#define TOTAL_POINTS 100000000 // 랜덤 점 개수
#define THREAD_COUNT 4 // 스레드
#define POINTS_PER_THREAD (TOTAL_POINTS / THREAD_COUNT) 

long long totals = 0; // 원 안에 있는 점 개수
sem_t sem; // 세마포어

// 스레드마다 실행될 함수
void* monte_carlos(void* arg) {
    int thread_id = *(int*) arg;
    int circle = 0;
    int i;
    double x, y;

    unsigned int seed = time(NULL) + thread_id; 

    for (i = 0; i < POINTS_PER_THREAD; i++) {
        x = (double)rand_r(&seed) / RAND_MAX * 2.0 - 1.0; 
        y = (double)rand_r(&seed) / RAND_MAX * 2.0 - 1.0; 
        if ((x*x) + (y*y) <= 1.0) {
            circle++;
        }
    }

    sem_wait(&sem); // 세마포어 잠금
    totals += circle;
    sem_post(&sem); // 세마포어 해제

    pthread_exit(NULL);
}

int Semaphorepimonte() {
    pthread_t threads[THREAD_COUNT];
    int thread_ids[THREAD_COUNT];
    int i;

    sem_init(&sem, 0, 1); // 세마포어 초기화

    // 각 스레드 ID 할당 및 스레드 생성
    for (i = 0; i < THREAD_COUNT; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, monte_carlos, &thread_ids[i]);
    }
   
    for (i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("pi = %f\n", (double)totals / TOTAL_POINTS * 4);

    sem_destroy(&sem); // 세마포어 파괴

    return 0;
}

int sema() {
    Semaphorepimonte();
    return 0;
}
