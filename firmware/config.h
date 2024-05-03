#ifndef Config_h
#define Config_h

#include "Arduino.h"
#include "TimerOne.h"
#include "lib/robotPort.h"
#include "lib/command.h"
#include "lib/serialComm.h"
#include "lib/robotCmd.h"
#include "lib/logger.h"
#include "lib/stepper.h"
#include "lib/limitSwitch.h"
#include "lib/axisControl.h"
#include "lib/rotateAxisControl.h"
#include "lib/robotController.h"


#define AR_GPIO25_X_MOTOR_ENABLE            25
#define AR_GPIO26_X_MOTOR_PULSE             26
#define AR_GPIO27_X_MOTOR_DIRECTION         27
#define AR_GPIO19_X_LIMIT_SWITCH_HOME       19
#define AR_GPIO18_X_LIMIT_SWITCH_END        18

#define AR_GPIO22_Z_MOTOR_ENABLE            22 
#define AR_GPIO23_Z_MOTOR_PULSE             23
#define AR_GPIO24_Z_MOTOR_DIRECTION         24
#define AR_GPIO21_Z_LIMIT_SWITCH_HOME       21
#define AR_GPIO20_Z_LIMIT_SWITCH_END        20

#define AR_GPIO28_ROTATE_MOTOR_ENABLE       28
#define AR_GPIO29_ROTATE_MOTOR_PULSE        29
#define AR_GPIO30_ROTATE_MOTOR_DIRECTION    30
#define AR_GPIO2_ROTATE_LIMIT_SWITCH_HOME   2
#define AR_GPIO3_ROTATE_LIMIT_SWITCH_END    3

#define AR_GPIO4_INPUT_BACKUP_01            4
#define AR_GPIO5_INPUT_BACKUP_02            5
#define AR_GPIO6_INPUT_BACKUP_03            6

#define AR_GPIO7_LED_DRIVER_PWM             7

#define DISABLE_STEPPER                     false
#define ENABLE_STEPPER                      true


#endif