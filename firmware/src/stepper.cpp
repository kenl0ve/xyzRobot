#include "../lib/stepper.h"

Stepper::Stepper(uint8_t enable_gpio, uint8_t direction_gpio, uint8_t pulse_gpio)
{
    this->_enable_gpio      = enable_gpio;
    this->_pulse_gpio       = pulse_gpio;
    this->_direction_gpio   = direction_gpio;

    this->init();
}

void Stepper::set_stepper_runs_1_pulse_with_default_step_delay()
{
    this->set_pulse_gpio_high();
    delayMicroseconds(this->stepDelay);
    this->set_pulse_gpio_low();
    delayMicroseconds(this->stepDelay);
}

void Stepper::set_stepper_runs_multiple_pulses_with_default_step_delay(uint16_t number)
{
    while(number > 0)
    {
        number -= 1;
        this->set_stepper_runs_1_pulse_with_default_step_delay();
    }
}

void Stepper::set_stepper_direction(boolean direction)
{
    if (direction == STEPPER_ROTATE_COUNTER_CLOCKWISE)
    {
        this->set_counter_clockwise_direction();
    }
    else 
    {
        this->set_clockwise_direction();
    }
}

void Stepper::enable_motor()
{
    digitalWrite(this->_enable_gpio, HIGH);
}
void Stepper::disable_motor()
{
    digitalWrite(this->_enable_gpio, LOW);
}

// Private functions
void Stepper::init()
{
    pinMode(this->_enable_gpio, OUTPUT);
    pinMode(this->_direction_gpio, OUTPUT);
    pinMode(this->_pulse_gpio, OUTPUT);
    // delay(100);
    digitalWrite(this->_enable_gpio, LOW);
    digitalWrite(this->_direction_gpio, LOW);
    digitalWrite(this->_pulse_gpio, LOW);
}
void Stepper::set_pulse_gpio(boolean status)
{
    if (status == true)
        this->set_pulse_gpio_high();
    else if (status == false)
        this->set_pulse_gpio_low();

}
void Stepper::set_pulse_gpio_high()
{
    digitalWrite(this->_pulse_gpio, HIGH);
}
void Stepper::set_pulse_gpio_low()
{
    digitalWrite(this->_pulse_gpio, LOW);
}
void Stepper::set_clockwise_direction()
{
    digitalWrite(this->_direction_gpio, HIGH);
}
void Stepper::set_counter_clockwise_direction()
{
    digitalWrite(this->_direction_gpio, LOW);
}
void Stepper::set_step_delay(uint16_t stepDelay)
{
    this->stepDelay = stepDelay;
}