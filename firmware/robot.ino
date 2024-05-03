
#include "config.h"


Stepper z_stepper         = Stepper(AR_GPIO22_Z_MOTOR_ENABLE,AR_GPIO24_Z_MOTOR_DIRECTION,AR_GPIO23_Z_MOTOR_PULSE);
LimitSwitch z_ls_home     = LimitSwitch(AR_GPIO21_Z_LIMIT_SWITCH_HOME);
LimitSwitch z_ls_end      = LimitSwitch(AR_GPIO20_Z_LIMIT_SWITCH_END);
AxisControl z_axis_ctrl   = AxisControl(z_stepper, z_ls_home, z_ls_end);

Stepper x_stepper         = Stepper(AR_GPIO25_X_MOTOR_ENABLE,AR_GPIO27_X_MOTOR_DIRECTION,AR_GPIO26_X_MOTOR_PULSE);
LimitSwitch x_ls_home     = LimitSwitch(AR_GPIO19_X_LIMIT_SWITCH_HOME);
LimitSwitch x_ls_end      = LimitSwitch(AR_GPIO18_X_LIMIT_SWITCH_END);
AxisControl x_axis_ctrl   = AxisControl(x_stepper, x_ls_home, x_ls_end);

Stepper r_stepper         = Stepper(AR_GPIO28_ROTATE_MOTOR_ENABLE,AR_GPIO30_ROTATE_MOTOR_DIRECTION,AR_GPIO29_ROTATE_MOTOR_PULSE);
LimitSwitch r_ls_home     = LimitSwitch(AR_GPIO2_ROTATE_LIMIT_SWITCH_HOME);
// LimitSwitch r_ls_end      = LimitSwitch(AR_GPIO3_ROTATE_LIMIT_SWITCH_END);
RotateAxisControl r_axis_ctrl   = RotateAxisControl(r_stepper, r_ls_home);

LimitSwitch emergencyButton = LimitSwitch(AR_GPIO4_INPUT_BACKUP_01);

RobotController robotController = RobotController(x_axis_ctrl, z_axis_ctrl, r_axis_ctrl);
String component, command, data;
boolean executionStatus; 

void setup() 
{
  Serial.begin(115200);
  Timer1.initialize(10000); // Initialize Timer1 with 10000us/10ms

  // robotController.enable_disable_3_axis_steppers(DISABLE_STEPPER, DISABLE_STEPPER, DISABLE_STEPPER);
  robotController.enable_disable_3_axis_steppers(ENABLE_STEPPER, ENABLE_STEPPER, ENABLE_STEPPER);
  analyze_led_command("START", "20");

  Timer1.attachInterrupt(emergency_execution);
}

void loop() 
{
  executionStatus = false;
    if (receive_command_from_robot_controller_v3(component, command, data))
    {
      executionStatus = analyze_and_execute_robot_command(component, command, data);
      if (executionStatus == true)
      {
        send_pass();
      }
      else
      {
        send_fail();
      }
    }  
}

void emergency_execution()
{
  if (!emergencyButton.is_pressed()) // The signal is reversed compared with the normal Limit switch
  {
    robotController.enable_disable_3_axis_steppers(DISABLE_STEPPER, DISABLE_STEPPER, DISABLE_STEPPER);
  }
}