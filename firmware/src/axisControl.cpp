#include "../lib/axisControl.h" 
#include "../lib/stepper.h"

// AxisControl::AxisControl(Stepper *_step, LimitSwitch *_ls_home, LimitSwitch *_ls_end)
// {
//   this->stepperController   = *_step;
//   this->limitSwitchEnd      = *_ls_end;
//   this->limitSwitchHome     - *_ls_home;
// }

boolean AxisControl::axis_goes_to_home_position()
{
    // this->set_axis_moves_backward();
    uint16_t excutedPulses = 0;
    while (!this->limitSwitchHome.is_pressed() && excutedPulses < 20000)
    {
        excutedPulses++;
        this->stepperController.set_stepper_runs_1_pulse_with_default_step_delay();
    }
    if (this->limitSwitchHome.is_pressed())
    {
        return false;
    }
    else
    {
        return true;
    }
}
boolean AxisControl::axis_goes_to_end_position()
{
    // this->set_axis_moves_forward();

    uint16_t excutedPulses = 0;
    while (!this->limitSwitchEnd.is_pressed() && excutedPulses < 20000)
    {
        excutedPulses++;
        this->stepperController.set_stepper_runs_1_pulse_with_default_step_delay();
    }
    if (this->limitSwitchEnd.is_pressed())
    {
        return false;
    }
    else
    {
        return true;
    }

}

boolean AxisControl::move_with_pulse_number(uint16_t pulse)
{
    this->stepperController.set_stepper_runs_multiple_pulses_with_default_step_delay(pulse);
}


void AxisControl::set_direction(boolean dir)
{
    this->stepperController.set_stepper_direction(dir);
    // if (dir == this->axisMoveForwardIs)
    // {
    //     this->set_axis_moves_forward();
    // }
    // else if (dir != this->axisMoveForwardIs)
    // {
    //     this->set_axis_moves_backward();
    // } 
}

boolean AxisControl::get_limit_switch_status(String limitSwitchName)
{   
    if (limitSwitchName == "HOME")
    {
        return this->limitSwitchHome.is_pressed();
    }
    else if(limitSwitchName == "END")
    {
        return this->limitSwitchEnd.is_pressed();
    }
}
boolean AxisControl::get_direction()
{
    return this->axisMoveForwardIs;
}

void AxisControl::set_pulse_signal(boolean status)
{
    this->stepperController.set_pulse_gpio(status);
}

void AxisControl::set_step_delay(uint16_t stepDelay)
{
    this->stepperController.set_step_delay(stepDelay);
}

// void AxisControl::set_axis_moves_backward()
// {
//     // this->stepperController.set_stepper_direction(!this->axisMoveForwardIs);
// }

// void AxisControl::set_axis_moves_forward()
// {
//     // this->stepperController.set_stepper_direction(this->axisMoveForwardIs);
// }

void AxisControl::enable_stepper()
{
    this->stepperController.enable_motor();
}
void AxisControl::disable_stepper()
{
    this->stepperController.disable_motor();
}
void AxisControl::set_enable_disable_axis(boolean status)
{
    if (status == STEPPER_DISABLE)
    {
        this->stepperController.disable_motor();
    }
    else if(status == STEPPER_ENABLE)
    {
        this->stepperController.enable_motor();
    }
}
