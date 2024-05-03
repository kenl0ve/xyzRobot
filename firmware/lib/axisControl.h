#ifndef AxisControl_h
#define AxisControl_h

#include "stepper.h"
#include "limitSwitch.h"

#define X_RATIO_PULSE_PER_MM                155

class AxisControl {
  public:
    AxisControl(Stepper &stepper, LimitSwitch &homeSwitch , LimitSwitch &endswitch) :
        stepperController(stepper),
        limitSwitchHome(homeSwitch),
        limitSwitchEnd(endswitch){};
    boolean axis_goes_to_end_position();
    boolean axis_goes_to_home_position();
    void disable_stepper();
    void enable_stepper();
    
    void set_direction(boolean dir);
    void set_step_delay(uint16_t stepDelay);
    void set_enable_disable_axis(boolean status);
    void set_pulse_signal(boolean);
    boolean get_limit_switch_status(String);
    boolean get_direction();
    boolean move_with_pulse_number(uint16_t pulse);

    // void set_axis_moves_backward();
    // void set_axis_moves_forward(); 

  private:
    Stepper stepperController;
    LimitSwitch limitSwitchHome;
    LimitSwitch limitSwitchEnd;

    boolean axisMoveForwardIs = STEPPER_ROTATE_COUNTER_CLOCKWISE;
    uint16_t ratio_pulses_per_mm = X_RATIO_PULSE_PER_MM;


};
#endif