#ifndef T_MOTOR_FSM_
#define T_MOTOR_FSM_
#ifdef __cplusplus
  extern "C" {
#endif
#include "eventobserver.h"
#include <pthread.h>

typedef enum motor_status_t {STOP, RUNNING, CALIBRATING}
motor_status_t;

typedef struct motor_fsm_t {
    motor_status_t cur_status;
  /* TODO: calib_fsm_t calib_fsm;*/
    void (*poll_event)(bol_event_t*);
    void (*running)();
    void (*stop)();
    void (*calibrating)();
} motor_fsm_t;

motor_fsm_t motor_fsm;

void motor_fsm_running(void);
void motor_fsm_stop(void);
void motor_fsm_calibrating(void);
void motor_fsm_poll_event(bol_event_t *);
void motor_fsm_init();


#ifdef __cplusplus
}
#endif
#endif