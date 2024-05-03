#ifndef Stepper_h
#define Stepper_h

#include "Arduino.h"

#define STEPPER_STEP_DELAY_10_US                10
#define STEPPER_STEP_DELAY_20_US                20
#define STEPPER_STEP_DELAY_DEFAULT              800

#define STEPPER_ROTATE_CLOCKWISE                false
#define STEPPER_ROTATE_COUNTER_CLOCKWISE        true

#define STEPPER_ENABLE                          true
#define STEPPER_DISABLE                         false

class Stepper {
  public:
    Stepper(uint8_t enable_gpio, uint8_t direction_gpio, uint8_t pulse_gpio);
    
    void set_stepper_runs_1_pulse_with_default_step_delay();
    void set_stepper_runs_multiple_pulses_with_default_step_delay(uint16_t);
    void set_stepper_direction(boolean);
    void enable_motor();
    void disable_motor();
    void set_step_delay(uint16_t);
    void set_pulse_gpio(boolean);
  private:
    uint8_t _enable_gpio;
    uint8_t _direction_gpio;
    uint8_t _pulse_gpio;
    uint16_t stepDelay = STEPPER_STEP_DELAY_DEFAULT;

    void init();
    void set_pulse_gpio_high();
    void set_pulse_gpio_low();
    void set_clockwise_direction();
    void set_counter_clockwise_direction();
};

#endif

