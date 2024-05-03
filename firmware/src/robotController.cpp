#include "../lib/robotController.h"

#include "Arduino.h"


boolean RobotController::set_direction_for_3_axis(boolean xDir, boolean zDir, boolean rDir)
{
    this->xAxisController.set_direction(xDir);
    this->zAxisController.set_direction(zDir);
    this->rAxisController.set_direction(rDir);
    return true;
}

boolean RobotController::configure_default_step_delay(uint16_t stepDelay)
{
    this->stepDelayForRobot = stepDelay;
    this->xAxisController.set_step_delay(stepDelay);
    this->zAxisController.set_step_delay(stepDelay);
    this->rAxisController.set_step_delay(stepDelay);
    return true;
}

boolean RobotController::enable_disable_3_axis_steppers(boolean xStatus, boolean zStatus, boolean rStatus)
{
    this->xAxisController.set_enable_disable_axis(xStatus);
    this->zAxisController.set_enable_disable_axis(zStatus);
    this->rAxisController.set_enable_disable_axis(rStatus);
    return true;
}

boolean RobotController::move_axis_to_home(String axisName)
{
    if (axisName == "X")
    {
        return this->xAxisController.axis_goes_to_home_position();
    }
    else if (axisName == "Z")
    {
        return this->zAxisController.axis_goes_to_home_position();
    }
    else if (axisName == "R")
    {
        return this->rAxisController.axis_goes_to_home_position();
    }
    return false;
}

boolean RobotController::move_axis_to_end(String axisName)
{
    if (axisName == "X")
    {
        return this->xAxisController.axis_goes_to_end_position();
    }
    else if (axisName == "Z")
    {
        return this->zAxisController.axis_goes_to_end_position();
    }
    return false;
}

boolean RobotController::move_3_axis_with_expected_pulses(uint16_t xPulses, uint16_t zPulses, uint16_t rPulses)
{
    uint16_t length;
    uint16_t xPulseExecuted;
    uint16_t zPulseExecuted;
    uint16_t rPulseExecuted;
    uint16_t ratio           = 20;

    xPulseExecuted = xPulses/ratio;
    zPulseExecuted = zPulses/ratio;
    rPulseExecuted = (int)(rPulses/ratio);

    while (xPulses != 0 | zPulses != 0 | rPulses != 0)
    {
        length = 0;
        if (xPulseExecuted < xPulses)
        {
            xPulses = xPulses - xPulseExecuted;
        }
        else
        {
            xPulseExecuted = xPulses;
            xPulses = 0;
        }
        if (zPulseExecuted < zPulses)
        {
            zPulses = zPulses - zPulseExecuted;
        }
        else
        {
            zPulseExecuted = zPulses;
            zPulses = 0;
        }
        if (rPulseExecuted < rPulses)
        {
            rPulses = rPulses - rPulseExecuted;
        }
        else
        {
            rPulseExecuted = rPulses;
            rPulses = 0;
        }

        boolean *array = generate_pulse_logic_array(xPulseExecuted, zPulseExecuted, rPulseExecuted, length);

        for (uint16_t i = 0; i < length*3; i+=3)
        {
            this->move_stepper_motors_with_a_pulses_array(true, true,true, array[i], array[i+1], array[i+2]);
        }

    }
}
boolean RobotController::move_axis_with_pulse_number(uint16_t pulse, String axisName)
{
    if (axisName == "X")
    {
        return this->xAxisController.move_with_pulse_number(pulse);
    }
    else if (axisName == "Z")
    {
        return this->zAxisController.move_with_pulse_number(pulse);
    }
    if (axisName == "R")
    {
        return this-rAxisController.move_with_pulse_number(pulse);
    }
    return false;
}


void RobotController::move_stepper_motors_with_a_pulses_array(boolean xDir, boolean zDir, boolean rDir, boolean xPulse, boolean zPulse, boolean rPulse)
{
    // this->xAxisController.set_direction(xDir);
    // this->zAxisController.set_direction(zDir);
    // this->rAxisController.set_direction(rDir);

    this->xAxisController.set_pulse_signal(xPulse);
    this->zAxisController.set_pulse_signal(zPulse);
    this->rAxisController.set_pulse_signal(rPulse);
    delayMicroseconds(this->stepDelayForRobot);
    this->xAxisController.set_pulse_signal(false);
    this->zAxisController.set_pulse_signal(false);
    this->rAxisController.set_pulse_signal(false);
    delayMicroseconds(this->stepDelayForRobot);
}

boolean RobotController::move_stepper_motors_with_a_pulse_indicator(uint8_t indicator)
{
    this->xAxisController.set_direction((boolean)(indicator >> 5 | 0x01));
    this->zAxisController.set_direction((boolean)(indicator >> 4 | 0x01));
    this->rAxisController.set_direction((boolean)(indicator >> 3 | 0x01));

    this->xAxisController.set_pulse_signal((boolean)(indicator >> 2 | 0x01));
    this->zAxisController.set_pulse_signal((boolean)(indicator >> 1 | 0x01));
    this->rAxisController.set_pulse_signal((boolean)(indicator >> 0 | 0x01));
    delayMicroseconds(this->stepDelayForRobot);
    this->xAxisController.set_pulse_signal(false);
    this->zAxisController.set_pulse_signal(false);
    this->rAxisController.set_pulse_signal(false);
    delayMicroseconds(this->stepDelayForRobot);
    return true;
}

boolean RobotController::get_limit_switch_status(String limitSwitchName, String axisName)
{
    if (axisName == "X")
    {
        return this->xAxisController.get_limit_switch_status(limitSwitchName);
    }
    else if (axisName == "Z")
    {
        return this->zAxisController.get_limit_switch_status(limitSwitchName);
    }
    else if (axisName == "R")
    {
        return this->rAxisController.get_limit_switch_status(limitSwitchName);
    }
    return false;
}
uint8_t RobotController::get_direction_status()
{
    uint8_t direction = (this->xAxisController.get_direction() << 2) | (this->zAxisController.get_direction() << 1) | this->rAxisController.get_direction();
    return direction;
}

boolean *RobotController::generate_pulse_logic_array(uint16_t xPulses, uint16_t zPulses, uint16_t rPulses, uint16_t &length)
{
    static boolean temp[MAXIMUM_PULSE_ARRAY];
    if ((rPulses < xPulses) or (rPulses < zPulses))
    {
        uint16_t r, r0, c, c0, steep = 0;
        uint16_t r1 = xPulses;
        uint16_t c1 = zPulses;

        uint8_t sc = 0;
        uint8_t sr = 0;

        uint16_t dr = r1-r0;
        uint16_t dc = c1-c0;

        length = max(dr, dc);
        uint16_t rr[MAXIMUM_PULSE_ARRAY];
        uint16_t cc[MAXIMUM_PULSE_ARRAY];
        if (c1 > c) 
        {
            sc = 1;
        }
        else
        {
            sc = -1;
        }
        
        if (r1 > r)
        {
            sr = 1;
        }
        else
        {
            sr = -1;
        }

        if (dr > dc)
        {
            steep = 1;
            uint16_t temp;
            temp = c;
            c = r;
            r = temp;

            temp = dc;
            dc = dr;
            dr = temp;

            temp = sc;
            sc = sr;
            sr = temp;
        }
        int16_t d = (dr << 1) - dc;

        for (uint16_t i = 0; i < dc; i++)
        {
            if (steep != 0)
            {
                rr[i] = c;
                cc[i] = r;
            }
            else
            {
                rr[i] = r;
                cc[i] = c;
            }
            while (d > -1)
            {
                r = r + sr;
                d = d - (dc << 1);
            }
            c = c + sc;
            d = d + (dr << 1);
        }

        rr[dc] = r1;
        cc[dc] = c1;
        boolean *arrayLogic = (boolean *)temp;

        int16_t rPulsesTemp = (int16_t)rPulses;

        for (uint16_t i = 0; i < length; i++)
        {
            arrayLogic[i*3 + 0] = (rr[i] != rr[i+1]);
            arrayLogic[i*3 + 1] = (cc[i] != cc[i+1]);
            arrayLogic[i*3 + 2] = (rPulsesTemp-- > 0);
        }
        return arrayLogic;
    }
    else
    {   
        length = rPulses;
        int16_t xPulsesTemp = (int16_t)xPulses;
        int16_t zPulsesTemp = (int16_t)zPulses;
        int16_t rPulsesTemp = (int16_t)rPulses;

        //boolean *arrayLogic = (boolean *)calloc(sizeof(boolean), length * 3);
        boolean *arrayLogic = (boolean *)temp;
        for (uint16_t i = 0; i < length; i++)
        {
            arrayLogic[i*3 + 0] = (xPulsesTemp-- > 0);
            arrayLogic[i*3 + 1] = (zPulsesTemp-- > 0);
            arrayLogic[i*3 + 2] = (rPulsesTemp-- > 0);
        }
        return arrayLogic;
    }
}

