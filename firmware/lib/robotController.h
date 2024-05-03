#ifndef RobotControl_h
#define RobotControl_h


#include "axisControl.h"
#include "rotateAxisControl.h"
#define MAXIMUM_PULSE_ARRAY        1000

class RobotController {
    public:
        RobotController(AxisControl &x_axis, AxisControl &z_axis, RotateAxisControl &r_axis) :
            xAxisController(x_axis),
            zAxisController(z_axis),
            rAxisController(r_axis){};

        boolean set_direction_for_3_axis(boolean xDir, boolean zDir, boolean rDir);
        boolean move_3_axis_with_expected_pulses(uint16_t xPulses, uint16_t zPulses, uint16_t rPulses);
        boolean configure_default_step_delay(uint16_t stepDelay);
        boolean return_robot_to_home();
        boolean return_robot_to_virtual_home();
        boolean return_robot_to_end();
        boolean return_robot_to_virtual_end();
        boolean enable_disable_3_axis_steppers(boolean xStatus, boolean zStatus, boolean rStatus);
        boolean move_stepper_motors_with_a_pulse_indicator(uint8_t indicator);
        boolean get_limit_switch_status(String, String);
        uint8_t get_direction_status();
        boolean move_axis_to_home(String axisName);
        boolean move_axis_to_end(String axisName);
        boolean move_axis_with_pulse_number(uint16_t pulse, String axisName);

    private:
        AxisControl xAxisController;
        AxisControl zAxisController;
        RotateAxisControl rAxisController;
        uint16_t stepDelayForRobot = 500;
        void move_stepper_motors_with_a_pulses_array(boolean xDir, boolean zDir, boolean rDir, boolean xPulse, boolean zPulse, boolean rPulse);
        boolean *RobotController::generate_pulse_logic_array(uint16_t xPulses, uint16_t zPulses, uint16_t rPulses, uint16_t &length);
};   

#endif

