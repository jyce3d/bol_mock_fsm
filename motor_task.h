#ifndef T_MOTOR_TASK_
#define T_MOTOR_TASK_
#ifdef __cplusplus
  extern "C" {
#endif
#include "eventobserver.h"

int create_motor_task(void);
bol_event_t cur_motor_task_event;

#ifdef __cplusplus
}
#endif

#endif