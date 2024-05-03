#include "../config.h"
// #include "Arduino.h"
// #include "../lib/serialComm.h"
static boolean arduino_debug_log   = false;

void log_info(const char *msg)
{
    if (arduino_debug_log)
    {
        char msg_temp[250] = " [Arduino - INFO]:    ";
        strcat(msg_temp, msg);
        send_log(msg_temp);
    }
}
void log_error(const char *msg)
{
    if (arduino_debug_log)
    {
        char msg_temp[250] = " [Arduino - ERROR]:    ";
        strcat(msg_temp, msg);
        send_log(msg_temp);
    }
}
void log_warning(const char *msg)
{
    if (arduino_debug_log)
    {
        char msg_temp[250] = " [Arduino - WARNING]: ";
        strcat(msg_temp, msg);
        send_log(msg_temp);
    }
}