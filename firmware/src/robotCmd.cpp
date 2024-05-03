
#include "../lib/robotCmd.h"

extern RobotController robotController;
extern LimitSwitch emergencyButton;

boolean execute_move_cmd(String data)
{
    String xPulseStr;
    String zPulseStr;
    String rPulseStr;

    uint16_t xPulse;
    uint16_t zPulse;
    uint16_t rPulse;

    uint8_t count = 0;
    for (uint8_t i = 0; i < data.length(); i++)
    {
      if (data[i] == '-')
      {
        count++;
        continue;
      }

      if (count == 0)
      {
        xPulseStr += data[i];
      }
      else if (count == 1)
      {
        zPulseStr += data[i];
      }
      else if (count == 2)
      {
        rPulseStr += data[i];
      }
    }
    if (count == 2)
    {
      xPulse = xPulseStr.toInt();
      zPulse = zPulseStr.toInt();
      rPulse = rPulseStr.toInt();
      robotController.move_3_axis_with_expected_pulses(xPulse, zPulse, rPulse);
      return true;
    }
    return false;
}

boolean execute_move_axis_with_pulse_number(String data)
{
  String axisName;
  String pulseStr;
  uint16_t pulseNumber;
  uint8_t count = 0;
    for (uint8_t i = 0; i < data.length(); i++)
    {
      if (data[i] == '-')
      {
        count++;
        continue;
      }
      if (count == 0)
      {
        axisName += data[i];
      }
      else if (count == 1)
      {
        pulseStr += data[i];
      }
    }
    if (count == 1)
    {
      pulseNumber = pulseStr.toInt();
      return robotController.move_axis_with_pulse_number(pulseNumber, axisName);
    }
    return false;
}

boolean execute_move_axis_to_home(String data)
{
  return robotController.move_axis_to_home(data);
}

boolean execute_move_axis_to_end(String data)
{
  return robotController.move_axis_to_end(data);
}

boolean execute_set_direction(String data)
{
  uint8_t count = 0;
  String xDirStr;
  String zDirStr;
  String rDirStr;

  for (uint8_t i = 0; i < data.length(); i++)
  {
    if (data[i] == '-')
    {
      count++;
      continue;
    }
    if (count == 0)
    {
      xDirStr += data[i];
    }
    else if (count == 1)
    {
      zDirStr += data[i];
    }
    else if (count == 2)
    {
      rDirStr += data[i];
    }
  }
  if (count == 2)
  {
    uint8_t xDir = xDirStr.toInt();
    uint8_t zDir = zDirStr.toInt();
    uint8_t rDir = rDirStr.toInt();
    robotController.set_direction_for_3_axis(xDir, zDir, rDir);
  }
}

boolean execute_set_step_delay(String data)
{
  uint16_t stepDelay = data.toInt();
  return robotController.configure_default_step_delay(stepDelay);
}
boolean execute_return_to_end()
{
  robotController.return_robot_to_end();
}

boolean execute_return_to_virtual_end()
{
  return robotController.return_robot_to_virtual_end();
}

boolean execute_disable_enable_steppers(String data)
{
  uint8_t count = 0;
  String xStatusStr;
  String zStatusStr;
  String rStatusStr;

  for (uint8_t i = 0; i < data.length(); i++)
  {
    if (data[i] == '-')
    {
      count++;
      continue;
    }
    if (count == 0)
    {
      xStatusStr += data[i];
    }
    else if (count == 1)
    {
      zStatusStr += data[i];
    }
    else if (count == 2)
    {
      rStatusStr += data[i];
    }
  }
  if (count == 2)
  {
    uint8_t xStatus = xStatusStr.toInt();
    uint8_t zStatus = zStatusStr.toInt();
    uint8_t rStatus = rStatusStr.toInt();
    robotController.enable_disable_3_axis_steppers(xStatus, zStatus, rStatus);
  }
}

boolean execute_get_limit_switch_status(String data)
{
  uint8_t count = 0;
  String limitSwitchName;
  String axisName;
  boolean limitSwitchStatus;

  for (uint8_t i = 0; i < data.length(); i++)
  {
    if (data[i] == '-')
    {
      count++;
      continue;
    }
    if (count == 0)
    {
      limitSwitchName += data[i];
    }
    else if (count == 1)
    {
      axisName += data[i];
    }
  }
  if (count == 1)
  {
    limitSwitchStatus = robotController.get_limit_switch_status(limitSwitchName, axisName);
    data = "{" + data;

    if (limitSwitchStatus == LIMIT_SWITCH_IS_PRESSED)
    {
      data += ":1}" ;
    }
    else if (limitSwitchStatus == !LIMIT_SWITCH_IS_PRESSED)
    {
      data +=  ":0}" ;
    }
    else
    {
      data +=  ":error}" ;
    }
    Serial.println(data);
    return true;
  }
  return false;
}

boolean execute_get_emergency_status()
{
  if (emergencyButton.is_pressed())
  {
    Serial.println("{EMERGENCY:0}");
  }
  else
  {
    Serial.println("{EMERGENCY:1}");
  }
}
