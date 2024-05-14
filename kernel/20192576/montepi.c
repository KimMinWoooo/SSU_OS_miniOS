#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#define TOTAL_POINTS 100000000 // 랜덤 점 개수
#define THREAD_COUNT 4 // 스레드
#define POINTS_PER_THREAD (TOTAL_POINTS / THREAD_COUNT) // 스레드 당 처리할 점 개수

long long total = 0; // 원 안에 있는 점 개수
pthread_mutex_t mutex; // 뮤텍스 선언 -> 여러 스레드가 동시에 공유 자원에 접근하는 것을 막기 위함!!

// 스레드마다 실행될 함수
void* monte_carlo(void* arg) {
    int thread_id = *(int*) arg;
    int circle = 0;
    int i;
    double x, y;

    unsigned int seed = time(NULL) + thread_id; // 고유한 시드 생성

    // POINTS_PER_THREAD 개수 만큼 랜덤 좌표 생성하여 원 안 점 개수 계산
    for (i = 0; i < POINTS_PER_THREAD; i++) {
        x = (double)rand_r(&seed) / RAND_MAX * 2.0 - 1.0; // 고유한 시드를 사용하여 랜덤 숫자 생성
        y = (double)rand_r(&seed) / RAND_MAX * 2.0 - 1.0; // 고유한 시드를 사용하여 랜덤 숫자 생성
        if ((x*x) + (y*y) <= 1.0) {
            circle++;
        }
    }

    pthread_mutex_lock(&mutex); 
    total += circle;
    pthread_mutex_unlock(&mutex); 

    pthread_exit(NULL);
}

int pimonte() {
    pthread_t threads[THREAD_COUNT];
    int thread_ids[THREAD_COUNT];
    int i;

    pthread_mutex_init(&mutex, NULL); 

    // 각 스레드 ID 할당 및 스레드 생성
    for (i = 0; i < THREAD_COUNT; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, monte_carlo, &thread_ids[i]);
    }
   
    for (i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("pi = %f\n", (double)total / TOTAL_POINTS * 4);

    pthread_mutex_destroy(&mutex);

    return 0;
}
