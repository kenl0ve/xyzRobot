/*

*/
#ifndef LimitSwitch_h
#define LimitSwitch_h

#include "Arduino.h"

#define LIMIT_SWITCH_IS_PRESSED 1
class LimitSwitch
{
  public:
    LimitSwitch(uint8_t ls_gpio);

    void init();
    boolean read();
    boolean is_pressed();

  private:
    uint8_t _ls_gpio;
    boolean _status;
    static void external_interrupt_gpio();
};
#endif