#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include "eventobserver.h"
#include "motor_task.h"


typedef enum motor_status_t  {STOP, ROTATE_CKWISE, 
ROTATE_RCKWISE} motor_status_t;

typedef struct motor_driver_t {
    motor_status_t direction;
} motor_driver_t;

motor_driver_t motor_driver;

typedef enum switch_status_t  {OFF, ON}
switch_status_t;

switch_status_t switch_up, switch_down;



static void send_event( int evt_target,  bol_event_t evt, void *data) {
 /* creer un mutex */
  pthread_mutex_lock(&evt_mutex);
  g_event[evt_target] = evt;
  g_event_data[evt_target] = data;

  /*NOTIFY and Awake Thread (<EVT_Target>Task)*/
  pthread_cond_signal(&evt_cv);

  pthread_mutex_unlock(&evt_mutex);

}


/* Private functions */
void set_switch_down() {
            motor_driver.direction = ROTATE_CKWISE;
            printf("SwitchDriver:switch down\n");
            /* notifier le moteur Task que le switch down est activé*/
            switch_down = ON;
            send_event(EVT_MOTOR_TASK, EVT_SWITCH_DOWN,  &switch_down);
            sleep(0.005);
            switch_down = OFF;

}
void set_switch_up() {
            motor_driver.direction = ROTATE_RCKWISE;
            printf("SwitchDriver:switch up\n");
            /* notifier le moteur Task que le switch down est activé*/
            switch_up = ON;
            send_event(EVT_MOTOR_TASK, EVT_SWITCH_UP, &switch_up);
            sleep(0.005);
            switch_up = OFF;

}
void th_motor_driver_run() {
    motor_driver.direction = ROTATE_CKWISE;
    /* on assume que le moteur est à mis course */
    /* et qu'il faut 6 secondes pour faire une course 
        complète. */
    printf("MotorDriver:motor start\n");
    time_t ti=time(0);
    time_t tf=time(0);
    switch_up = OFF;
    switch_down = OFF;
    while ((int)(tf-ti)<=3) {
        /*printf("%d\n", (int)(tf-ti));*/
        tf=time(0);
    }
    /* notifier le moteur que le switch up activé*/
    /*motor_driver.direction = ROTATE_RCKWISE;
    printf("switch up\n");*/
    set_switch_up();

    while (1) {
        ti=time(0);
        tf=time(0);
        while ((int)(tf-ti)<=6) {
            tf=time(0);
        }
        if (motor_driver.direction == ROTATE_RCKWISE) {
            set_switch_down();
        }
        else {
            /*notifier le swith up est activé*/
            set_switch_up();

        }

    }

}
void init() {
    pthread_cond_t evt_cv= PTHREAD_COND_INITIALIZER;
    pthread_mutex_t evt_mutex = PTHREAD_MUTEX_INITIALIZER;

    const int EVT_GLOBAL_TASK = 0;
    const int EVT_MOTOR_TASK = 1;

    void *(*observer_ptr[5])()={NULL, NULL, NULL, NULL, NULL};

}
void main() {
    init();
    printf("MainTask:Initialized\n");
    create_motor_task();
    printf("MainTask:MotorTask created\n");
    th_motor_driver_run();
    printf("MainTask:Drivers (motor and switches) runs");
}