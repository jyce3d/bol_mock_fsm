
#include "motor_fsm.h"
#include <pthread.h>
#include <stdio.h>

void motor_fsm_running(void) {
    if (motor_fsm.cur_status == CALIBRATING )
        motor_fsm.cur_status = RUNNING;
    
}
void motor_fsm_stop(void) {
    motor_fsm.cur_status= STOP;
}
void motor_fsm_calibrating(void) {
    if (motor_fsm.cur_status == STOP)
        motor_fsm.cur_status= CALIBRATING;

}

void motor_fsm_poll_event(bol_event_t *evt) {
    if (*evt == EVT_SWITCH_UP) {
        printf("MOTOR_FSM:Catch Switch Up\n");
    } else if (*evt == EVT_SWITCH_DOWN)
        printf("MOTOR_FSM:Catch Switch down\n");
}

void motor_fsm_init() {
    motor_fsm.cur_status=STOP;
    motor_fsm.calibrating = motor_fsm_calibrating;
    motor_fsm.stop = motor_fsm_stop;
    motor_fsm.running = motor_fsm_running;
    motor_fsm.poll_event = motor_fsm_poll_event;
   /*TODO: calib_fsm_init(motor_fsm.calib_fsm);*/
}



