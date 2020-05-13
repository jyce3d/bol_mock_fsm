/*******************************************************

    EventObserver module.
    Used by drivers and tasks to send event in a controlled way
    by using Mutex
    Jean-Yves Célis, MAY 2020
***/
#ifndef T_EVENT_OBSERVER_
#define T_EVENT_OBSERVER_
#ifdef __cplusplus
  extern "C" {
#endif
#include<pthread.h>
typedef enum bol_event_t  {NONE, EVT_SWITCH_UP, EVT_SWITCH_DOWN}
bol_event_t;
bol_event_t g_event[5];
void *g_event_data[5];

pthread_cond_t  evt_cv;
pthread_mutex_t evt_mutex;

const int EVT_GLOBAL_TASK;
const int EVT_MOTOR_TASK;

/* observer allowing observable function to register */
/* In this simple case, the Thread register itself in this module */

void *(*observer_ptr[5])();

#ifdef __cplusplus
}
#endif
#endif