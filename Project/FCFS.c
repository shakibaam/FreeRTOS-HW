#include <stdio.h>
#include <stdlib.h>
#include "FreeRTOS.h"		/* RTOS firmware */
#include "task.h"			/* Task */
#include "timers.h"
#include<time.h>

#define NUMBER_OF_TASKS 5

struct My_Task {
    float arrival_time;
    float period;

}

struct My_Task fcfs_tasks[NUMBER_OF_TASKS];



void FCFS(struct My_Task tasks){
    //sort by arrival_time by bubble sort
    for(i=0;i<NUMBER_OF_TASKS-1;i++){ 
        for (j = 0; j < NUMBER_OF_TASKS - i-1; j++) {
            if(tasks[i].arrival_time > tasks[j].arrival_time){
                temp = tasks[i];
                tasks[i] = tasks[j];
                tasks[j] = temp;
            }

        }
    }

    // run task after sorting without preemption

    for(i=0;i<NUMBER_OF_TASKS-1;i++){ 

        sprintf(str, "Task %d", i);
    }


}




int main(void){


    for(i=0;i<NUMBER_OF_TASKS;i++){ 
    fcfs_tasks[i].arrival_time = srand(time(0));
    fcfs_tasks[i].period = 0;
}


    return 0;
}