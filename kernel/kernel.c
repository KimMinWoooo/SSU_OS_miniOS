#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "system.h"
void print_minios(char* str);

int main() {
    print_minios("[MiniOS SSU] Hello, World!");

    char *input;

    while(1) {
        // readline을 사용하여 입력 받기
        input = readline("커맨드를 입력하세요(종료:exit) : ");

        if (strcmp(input,"exit") == 0) {
            break;
        }
        if (strcmp(input, "Round") == 0 )
	    {
	     Round();
	    }
        if (strcmp(input, "process") == 0 )
	    {
	     process();
	    }

        if (strcmp(input,"minisystem") == 0){
            minisystem();
        }
	if (strcmp(input, "minwoo") == 0) {
            printf("20192576 KimMinWoo OS\n");
	}
	if (strcmp(input,"ipc") == 0 )
        {
            ipc();
        }
	if (strcmp(input, "pimonte") == 0 ) // Mutext 동기화
	{
	 pimonte();
	}
    if (strcmp(input, "Semaphorepimonte") == 0 ) // Semaphore 동기화
    {
        sema();
    }
    
        else system(input);
    }

    // 메모리 해제
    free(input);
    print_minios("[MiniOS SSU] MiniOS Shutdown........");

    return(1);
}

void print_minios(char* str) {
        printf("%s\n",str);
}
