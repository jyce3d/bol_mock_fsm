#include <pthread.h>
#include <stdio.h>
#include "motor_fsm.h"
#include "motor_task.h"


/* MOTOR Task (Thread) */

void *motor_task_receiv_event(void *arg) {
       while(1) {
           /* A remplacer par un hook venant d'un .h */
            pthread_mutex_lock(&evt_mutex);
            while (g_event[EVT_MOTOR_TASK]==NONE)
                pthread_cond_wait(&evt_cv, &evt_mutex); /* make the thread sleep */
            cur_motor_task_event = g_event[EVT_MOTOR_TASK];
            g_event[EVT_MOTOR_TASK]=NONE;
            pthread_mutex_unlock(&evt_mutex);
            motor_fsm.poll_event(&cur_motor_task_event);

       }
}
int create_motor_task(void) {
    /* Register to the event observer */
    observer_ptr[EVT_MOTOR_TASK] = motor_task_receiv_event;
    pthread_t th_motor_task;
    printf("MotorTask:Create Motor_FSM\n");
    motor_fsm_init();
    motor_fsm.calibrating();

    motor_fsm.running();
    pthread_create(&th_motor_task,NULL,motor_task_receiv_event,NULL);
    printf("MotorTask:Listener Thread created and sleep\n");

    /*pthread_join(th_motor_task, NULL);*/ 
    printf("MotorTask:Exit\n");

    return 0;
}

