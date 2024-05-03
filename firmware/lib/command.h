
#ifndef Command_h
#define Command_h
#include "../config.h"

boolean analyze_and_execute_robot_command(String component, String command, String data);
boolean analyze_robot_command(String command, String data);
boolean analyze_led_command(String command, String data);
boolean analyze_arduino_command(String command, String data);
#endif