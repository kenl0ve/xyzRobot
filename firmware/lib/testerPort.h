#ifndef RobotPort_h
#define RobotPort_h
#include "Arduino.h"
#include "../lib/logger.h"

boolean receive_command_from_robot_controller(String &readString);
boolean receive_command_from_robot_controller_v2();
boolean receive_command_from_robot_controller_v3(String &commponent, String &command, String &data);
void send_log();
void send_pass();
void send_fail();
void send_emergency_executed();
void send_ping();


#endif