
#ifndef RobotCmd_h
#define RobotCmd_h
#include "Arduino.h"
#include "robotController.h"

boolean execute_move_cmd(String);
boolean execute_set_direction(String);
boolean execute_set_step_delay(String);
boolean return_limit_switch_status(String);
boolean execute_disable_enable_steppers(String);
boolean execute_get_limit_switch_status(String);
boolean execute_move_axis_to_home(String);
boolean execute_move_axis_to_end(String);
boolean execute_move_axis_with_pulse_number(String);
boolean execute_get_emergency_status();

#endif