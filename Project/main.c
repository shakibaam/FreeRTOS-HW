/*
    FreeRTOS V9.0.0 - Copyright (C) 2016 Real Time Engineers Ltd.
    All rights reserved

    VISIT http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation >>>> AND MODIFIED BY <<<< the FreeRTOS exception.

    ***************************************************************************
    >>!   NOTE: The modification to the GPL is included to allow you to     !<<
    >>!   distribute a combined work that includes FreeRTOS without being   !<<
    >>!   obliged to provide the source code for proprietary components     !<<
    >>!   outside of the FreeRTOS kernel.                                   !<<
    ***************************************************************************

    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  Full license text is available on the following
    link: http://www.freertos.org/a00114.html

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS provides completely free yet professionally developed,    *
     *    robust, strictly quality controlled, supported, and cross          *
     *    platform software that is more than just the market leader, it     *
     *    is the industry's de facto standard.                               *
     *                                                                       *
     *    Help yourself get started quickly while simultaneously helping     *
     *    to support the FreeRTOS project by purchasing a FreeRTOS           *
     *    tutorial book, reference manual, or both:                          *
     *    http://www.FreeRTOS.org/Documentation                              *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org/FAQHelp.html - Having a problem?  Start by reading
    the FAQ page "My application does not run, what could be wrong?".  Have you
    defined configASSERT()?

    http://www.FreeRTOS.org/support - In return for receiving this top quality
    embedded software for free we request you assist our global community by
    participating in the support forum.

    http://www.FreeRTOS.org/training - Investing in training allows your team to
    be as productive as possible as early as possible.  Now you can receive
    FreeRTOS training directly from Richard Barry, CEO of Real Time Engineers
    Ltd, and the world's leading authority on the world's leading RTOS.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool, a DOS
    compatible FAT file system, and our tiny thread aware UDP/IP stack.

    http://www.FreeRTOS.org/labs - Where new FreeRTOS products go to incubate.
    Come and try FreeRTOS+TCP, our new open source TCP/IP stack for FreeRTOS.

    http://www.OpenRTOS.com - Real Time Engineers ltd. license FreeRTOS to High
    Integrity Systems ltd. to sell under the OpenRTOS brand.  Low cost OpenRTOS
    licenses offer ticketed support, indemnification and commercial middleware.

    http://www.SafeRTOS.com - High Integrity Systems also provide a safety
    engineered and independently SIL3 certified version for use in safety and
    mission critical applications that require provable dependability.

    1 tab == 4 spaces!
*/

/*
 * main() creates all the demo application tasks, then starts the scheduler.
 * The web documentation provides more details of the standard demo application
 * tasks, which provide no particular functionality but do provide a good
 * example of how to use the FreeRTOS API.
 *
 * In addition to the standard demo tasks, the following tasks and tests are
 * defined and/or created within this file:
 *
 * "Check" task - This only executes every five seconds but has a high priority
 * to ensure it gets processor time.  Its main function is to check that all the
 * standard demo tasks are still operational.  While no errors have been
 * discovered the check task will print out "OK" and the current simulated tick
 * time.  If an error is discovered in the execution of a task then the check
 * task will print out an appropriate error message.
 *
 */


/* Standard includes. */
#include <stdio.h>
#include <stdlib.h>
#include "FreeRTOS.h"		/* RTOS firmware */
#include "task.h"			/* Task */
#include "timers.h"
//#include "queue.h"
int counter1 = 0;
int counter4 = 0;
TaskHandle_t xHandle;

/* Examples */
#define ERTS2_TASKMANAGEMENT

/* --------------------------------------------- */
#ifdef ERTS2_TASKMANAGEMENT
// you need make your task visible @TODO
// example 
void vTask1(void* parameter){
    TickType_t xLastWaketime = xTaskGetTickCount();
    
    while(1){
        printf("Task1 with 250ms\n");
        vTaskDelayUntil(&xLastWaketime , pdMS_TO_TICKS(2250));
        vTaskDelay(pdMS_TO_TICKS(4750));
        sleep(250);
        
        counter1++;
        // 8 * 250ms = 2s
        // after 2s suspend
        if(counter1==8){
            vTaskSuspend(xHandle);
            
            counter1 = 0;
        }
    }
}


void vTask2(void* parameter){
    TickType_t xLastWaketime = xTaskGetTickCount();
    while(1){
        printf("Task2 with 500ms\n");
        vTaskDelayUntil(&xLastWaketime , pdMS_TO_TICKS(2500));
        vTaskDelay(pdMS_TO_TICKS(2500));
        sleep(0.5);
        
    }
}

void vTask3(void* parameter){
    TickType_t xLastWaketime = xTaskGetTickCount();
    while(1){
        printf("Task3 with 750ms\n");
        vTaskDelayUntil(&xLastWaketime , pdMS_TO_TICKS(2750));
        vTaskDelay(pdMS_TO_TICKS(1250));
        sleep(0.75);
    }
}

void vTask4(void* parameter){
    TickType_t xLastWaketime = xTaskGetTickCount();
    
    while(1){
        printf("Task4 with 1000ms\n");
        vTaskDelayUntil(&xLastWaketime , pdMS_TO_TICKS(4000));
        vTaskDelay(pdMS_TO_TICKS(3000));
        sleep(1);
        counter4++;
        //Resume Task1
        if(counter4 == 2){
            vTaskResume(xHandle);
            counter4 = 0;
        }
        
    }
}

// void AperiodicInterrupt(void* parameter){
//     TickType_t execution_time = 100;
//     TickType_t current_time = 0;
//     TickType_t previous_tick = 0;
//     TickType_t relative_deadline = 0;
//     TickType_t start_time = 0;
//     unint32_t execution_counter = 0;
//     while(1){
//         current_time = xTaskGetTickCount();
//         previous_tick = current_time;
//         start_time = current_time;
//         printf("Interrupt start\n");
//         while(execution_counter < execution_time) {
//             execution_counter++;
            
//         }

//         printf("Interrupt finish\n");
//         DD_Task_Delete(xTaskGetCurrentTaskHandle());

//     }
// }

// void AperiodicTaskGenerator(void* parameter){
//     ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
//     printf("Aperiodc created\n");
//     DD_TaskHandle_t generated_task = DD_Task_Allocate();
//     generated_task->task_function = AperiodicInterrupt();
//     generated_task->task_name = "Interrupt1";
//     generated_task->task_type = DD_TT_Aperiodic();

//     TickType_t current_time = xTaskGetTickCount();
//     generated_task->creation_time = current_time;
//     // generated_task->deadline = current_time;

//     DD_Task_Create(generated_task);
// }



#endif

void vApplicationIdleHook(void);

int main ( void )
{
#ifdef ERTS2_TASKMANAGEMENT
	/* Creating Four Task with different Priorities and Delay*/
    // search and find xTaskCreate how it is work   
    xTaskCreate( vTask1, "Task 1", 1000, NULL, 4, &xHandle );
    xTaskCreate( vTask2, "Task 2", 1000, NULL, 3, NULL );
    xTaskCreate( vTask3, "Task 3", 1000, NULL, 2, NULL );
    xTaskCreate( vTask4, "Task 4", 1000, NULL, 1, NULL );


#endif

	vTaskStartScheduler();
	return 0;
}

void vAssertCalled( unsigned long ulLine, const char * const pcFileName )
{
 	taskENTER_CRITICAL();
	{
        printf("[ASSERT] %s:%lu\n", pcFileName, ulLine);
        fflush(stdout);
	}
	taskEXIT_CRITICAL();
	exit(-1);
}


#ifdef ERTS2_TASKMANAGEMENT
//define your Task here @TODO





#endif
/* CH3_TASKMANAGEMENT ends */


void vApplicationIdleHook(void)
{
//	printf("Idle\r\n");
}
/*-----------------------------------------------------------*/
