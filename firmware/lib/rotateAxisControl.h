#ifndef RotateAxisControl_h
#define RotateAxisControl_h

#include "stepper.h"
#include "limitSwitch.h"

#define PULSE_PER_360_DEGREES                 1600
#define PULSE_PER_45_DEGREE                   1600*45/360
#define PULSE_PER_90_DEGREE                   1600*90/360
#define PULSE_PER_135_DEGREE                  1600*135/360


class RotateAxisControl {
  public:
    RotateAxisControl(Stepper &stepper, LimitSwitch &homeSwitch) :
        stepperController(stepper),
        limitSwitchHome(homeSwitch){};
    void find_direction();
    boolean axis_goes_to_home_position();
    boolean axis_goes_to_end_position();
    // void move_axis_with_expected_degrees(uint16_t);
    void set_degree(uint16_t);
    // void set_axis_moves_forward();
    // void set_axis_moves_backward();
    void set_step_delay(uint16_t stepDelay);
    void set_pulse_signal(boolean);
    boolean move_with_pulse_number(uint16_t pulse);

    void set_enable_disable_axis(boolean status);
    void set_direction(boolean dir);
    boolean get_limit_switch_status(String limitSwitchName);
    boolean get_direction();

  private:
    Stepper stepperController;
    LimitSwitch limitSwitchHome;

    boolean axisMoveForwardIs             = STEPPER_ROTATE_CLOCKWISE;
    uint16_t ratio_pulses_per_360_degrees = PULSE_PER_360_DEGREES;
    uint16_t maximumDegrees               = 360;
    uint16_t maximumPulses                = maximumDegrees * ratio_pulses_per_360_degrees / 360;

    uint16_t currentDegrees               = 0;
    
    void disable_stepper();
    void enable_stepper();
    void convert_degrees_to_stepper_pulses(uint16_t degrees);
};
#endif