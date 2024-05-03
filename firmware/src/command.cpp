
#include "../lib/command.h"

boolean analyze_and_execute_robot_command(String component, String command, String data)
{
  boolean status = false;
  if (component == "TESTER")
  {    
    status = analyze_robot_command(command, data);
  }
  else if (component == "LED")
  {
    status = analyze_led_command(command, data);
  }
  else if (component == "ARDUINO")
  {
    status = analyze_arduino_command(command, data);
  }
  
  else
  {
    // return false;
  }
  return status;
}

boolean analyze_arduino_command(String command, String data)
{
  if (command == "GET")
  {
    if (data == "VERSION")
    {
      Serial.write("{TETSTER.ARDUINO.DVT.TEST.v1.3}");
      return true;
    }
    if (data == "PING")
    {
      return true;
    }
  }
  return false;
}

boolean analyze_led_command(String command, String data)
{
    if (command == "START")
    {
      uint8_t dutyCircle = data.toInt();
      if (dutyCircle > 100) dutyCircle = 100;
      else if (dutyCircle < 0) dutyCircle = 0;
      uint8_t pwm = (uint8_t)dutyCircle*255/100;
      analogWrite(AR_GPIO7_LED_DRIVER_PWM, pwm);
      return true;
    }
    return false;
}

boolean analyze_robot_command(String command, String data)
{
  if (command == "MOVE")
  {
    return execute_move_cmd(data);
  }
  else if (command == "AXIS")
  {
    return execute_move_axis_with_pulse_number(data);
  }
  else if (command == "HOME")
  {
    return execute_move_axis_to_home(data);
  }
  else if (command == "END")
  {
    return execute_move_axis_to_end(data);
  }
  else if(command == "DIR")
  {
    return execute_set_direction(data);
  }
  else if (command == "DELAY")
  {
    return execute_set_step_delay(data);
  }
  else if (command == "ENABLE")
  {
    return execute_disable_enable_steppers(data);
  }
  else if (command == "LIMIT")
  {
    return execute_get_limit_switch_status(data);
  }
  else if (command == "EMERGENCY")
  {
    if (data == "STATUS")
    {
      return execute_get_emergency_status();
    }
  }
  return false;
  
}

