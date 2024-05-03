#include "../lib/limitSwitch.h"

LimitSwitch::LimitSwitch(uint8_t pin)
{
  this->_ls_gpio = pin;
  this->init();
}

// static void LimitSwitch::external_interrupt_gpio() 
// {
//   LimitSwitch::_status = this->read();

//   if (this->_status == LIMIT_SWITCH_IS_PRESSED) 
//   {
//     // Do something
//   }
//   else // this->_status ==  !LIMIT_SWITCH_IS_PRESSED
//   {
//     // Do something
//   }
// }

void LimitSwitch::init()
{
  pinMode(this->_ls_gpio, INPUT);
  // attachInterrupt(digitalPinToInterrupt(this->_ls_gpio), this->external_interrupt_gpio, CHANGE);
}


boolean LimitSwitch::read()
{
  return digitalRead(this->_ls_gpio);
}

boolean LimitSwitch::is_pressed()
{
  this->_status = this->read();
  if (this->_status == LIMIT_SWITCH_IS_PRESSED)
    return LIMIT_SWITCH_IS_PRESSED;
  else
    return !LIMIT_SWITCH_IS_PRESSED;
}
