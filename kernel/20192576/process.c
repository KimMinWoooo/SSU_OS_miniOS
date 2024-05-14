#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_PROCESSES 10
#define TIME_SLICE 2 // 시간 슬라이스 (예: 2초)

typedef enum process_state {
    PROCESS_RUNNING,
    PROCESS_WAITING,
    PROCESS_TERMINATED
} process_state;

typedef struct {
    int process_id;
    process_state status;
    char *process_memory;  
    int memory_size;
} process_info;

process_info process_list[MAX_PROCESSES];
int current_process_index = -1; // 현재 실행 중인 프로세스 인덱스

// Function prototypes
void initialize_process_list();
int create_process(int memory_size);
void schedule();
void terminate_process(int pid);
void display_processes();
void round_robin_schedule();

int process() {
    initialize_process_list();
    int pid1 = create_process(1024);  
    int pid2 = create_process(2048);
    int pid3 = create_process(4096);
    
    round_robin_schedule();
    
    terminate_process(pid1);
    terminate_process(pid2);
    terminate_process(pid3); 
    display_processes();

    return 0;
}


void initialize_process_list() {
    for (int i = 0; i < MAX_PROCESSES; i++) {
        process_list[i].process_id = -1;  
        process_list[i].status = PROCESS_TERMINATED;
        process_list[i].process_memory = NULL;
        process_list[i].memory_size = 0;
    }
}

int create_process(int memory_size) {
    for (int i = 0; i < MAX_PROCESSES; i++) {
        if (process_list[i].process_id == -1) {
            process_list[i].process_id = i;
            process_list[i].status = PROCESS_WAITING;
            process_list[i].process_memory = (char *)malloc(memory_size);
            process_list[i].memory_size = memory_size;
            printf("프로세스 생성 %d번 : %d bytes of memory.\n", i, memory_size);
            return i;
        }   
    }
    return -1;
}

void schedule() {
    for (int i = 0; i < MAX_PROCESSES; i++) {
        if (process_list[i].process_id != -1 && process_list[i].status != PROCESS_TERMINATED) {
            process_list[i].status = PROCESS_RUNNING;
            printf("프로세스 %d번 running.\n", i);
        }
    }
}

void round_robin_schedule() {
    int remaining_processes = MAX_PROCESSES;
    int next_process_index = 0;
    
    while (remaining_processes > 0) {
        if (process_list[next_process_index].process_id != -1 && process_list[next_process_index].status != PROCESS_TERMINATED) {
            process_list[next_process_index].status = PROCESS_RUNNING;
            printf("프로세스 %d번 running.\n", next_process_index);
            usleep(TIME_SLICE * 1000000); // 시간 슬라이스 만큼 대기
            process_list[next_process_index].status = PROCESS_WAITING; // 현재 프로세스 대기 상태로 변경
            printf("프로세스 %d번 Terminated.\n", next_process_index);
            remaining_processes--;
        }
        next_process_index = (next_process_index + 1) % MAX_PROCESSES;
    }
}


void terminate_process(int pid) {
    if (pid >= 0 && pid < MAX_PROCESSES && process_list[pid].process_id != -1) {
        process_list[pid].status = PROCESS_TERMINATED;
        free(process_list[pid].process_memory);
        process_list[pid].process_memory = NULL;
        process_list[pid].memory_size = 0;
        printf("프로세스 %d번 Terminated.\n", pid);
    }
}

void display_processes() {
    for (int i = 0; i < MAX_PROCESSES; i++) {
        if (process_list[i].process_id != -1) {
            printf("%d번 프로세스, 상태: %d, 메모리 크기: %d\n", i, process_list[i].status, process_list[i].memory_size);
        }
    }
}
