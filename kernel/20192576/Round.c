#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PROCESSES 5
#define TIME_SLICE 3

typedef struct Process {
    int arrival_time;   // 도착 시간
    int burst_time;     // 실행 시간
    int remaining_time; // 남은 실행 시간
} Process;

// 랜덤 실행 시간을 생성
int generate_burst_time() {
    return rand() % 11 + 5; 
}

int Round() {
    srand(time(NULL)); 

    int num_processes = MAX_PROCESSES; 
    Process processes[MAX_PROCESSES]; 

    printf("Round Robin Scheduling:\n");

    for (int i = 0; i < num_processes; i++) {
        processes[i].arrival_time = i * 2; // 도착 시간은 0, 2, 4, 6, 8로 설정
        processes[i].burst_time = generate_burst_time(); // 실행 시간은 랜덤하게 설정
        processes[i].remaining_time = processes[i].burst_time;
        printf("Process %d: Arrival Time = %d, Burst Time = %d\n", i + 1, processes[i].arrival_time, processes[i].burst_time);
    }
    int current_time = 0; 
    int completed_processes = 0;
    while (completed_processes < num_processes) {
        for (int i = 0; i < num_processes; i++) {
            if (processes[i].remaining_time > 0) {
                printf("Time %d: Process %d is running\n", current_time, i + 1);
                
                // 프로세스 실행
                if (processes[i].remaining_time > TIME_SLICE) {
                    current_time += TIME_SLICE;
                    processes[i].remaining_time -= TIME_SLICE;
                } else {
                    current_time += processes[i].remaining_time;
                    processes[i].remaining_time = 0;
                    completed_processes++; // 프로세스 완료
                    printf("Time %d: Process %d is completed\n", current_time, i + 1);
                }
            }
        }
    }
    return 0;
}
