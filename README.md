# bol_mock_fsm
This small project is an example of a new C architecture managing the tasks (Linux Threads) the communication by events between threads. Implements FSM architecture and could be used as a Mock framework to mimic to ventilator behavior on a Linux PC. (Not yet tested it in Windows).

./make.sh
to compile
./motor
to run, the program emulates the move of the motor moving up, touching a SWITCH_UP awakes the motor_task and pass the event to the MOTOR_FSM that will process it. Then the motor_task go back to sleep until the SWITCH_DOWN event.
The moto_driver emulates the move down until the motor touches the SWITCH_DOWN then awakes the motor_task and pass the SWITCH_DOWN event to the MOTOR_FSM. Then go up and down again and again. 

https://www.youtube.com/watch?v=Di-z4XSnus8
