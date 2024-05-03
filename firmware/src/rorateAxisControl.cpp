#include "../lib/rotateAxisControl.h"
#include "Arduino.h"

void RotateAxisControl::find_direction()
{

}
void RotateAxisControl::set_step_delay(uint16_t stepDelay)
{
    this->stepperController.set_step_delay(stepDelay);
}

boolean RotateAxisControl::get_direction()
{
    return this->axisMoveForwardIs;
}

boolean RotateAxisControl::move_with_pulse_number(uint16_t pulse)
{
    this->stepperController.set_stepper_runs_multiple_pulses_with_default_step_delay(pulse);
}



// void RotateAxisControl::move_axis_with_expected_degrees(uint16_t expectedDegree)
// {
//     if (expectedDegree > this->maximumDegrees)
//     {
//         return;
//     }
//     else
//     {
//         int16_t executedDegrees = 0;
//         if (expectedDegree >= this->currentDegrees)
//         {
//             this->set_axis_moves_forward();
//             executedDegrees = (int16_t)expectedDegree - (int16_t)this->currentDegrees;
//         }
//         else
//         {
//             this->set_axis_moves_backward();
//             executedDegrees = (int16_t)this->currentDegrees - (int16_t)expectedDegree;
//         }
//         int32_t executedPulses = (int32_t)executedDegrees * (int32_t)PULSE_PER_360_DEGREES / 360;
//         // while (!this->limitSwitchHome.is_pressed() && executedPulses > 0)
//         while (executedPulses > 0)
//         {
//             executedPulses -= 1;
//             this->stepperController.set_stepper_runs_1_pulse_with_default_step_delay();
//         }

//         this->set_degree(expectedDegree);
//         // this->stepperController.set_stepper_runs_multiple_pulses_with_default_step_delay(executedPulses);
//     }
// }

boolean RotateAxisControl::axis_goes_to_home_position()
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
// void RotateAxisControl::axis_goes_to_end_position()
// {
//     // this->set_axis_moves_forward();

//     while (!this->limitSwitchHome.is_pressed())
//     {
//         this->stepperController.set_stepper_runs_1_pulse_with_default_step_delay();
//     }
// }

// void RotateAxisControl::set_axis_moves_backward()
// {
//     this->stepperController.set_stepper_direction(!this->axisMoveForwardIs);
// }

// void RotateAxisControl::set_axis_moves_forward()
// {
//     this->stepperController.set_stepper_direction(this->axisMoveForwardIs);
// }

void RotateAxisControl::enable_stepper()
{
    this->stepperController.enable_motor();
}
void RotateAxisControl::disable_stepper()
{
    this->stepperController.disable_motor();
}

void RotateAxisControl::set_direction(boolean dir)
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

boolean RotateAxisControl::get_limit_switch_status(String limitSwitchName)
{
    if (limitSwitchName == "HOME")
    {
        return this->limitSwitchHome.is_pressed();
    }
    return false;
}

void RotateAxisControl:: set_degree(uint16_t degree)
{
    this->currentDegrees = degree;
}

void RotateAxisControl::set_enable_disable_axis(boolean status)
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

void RotateAxisControl::set_pulse_signal(boolean status)
{
    this->stepperController.set_pulse_gpio(status);
}

