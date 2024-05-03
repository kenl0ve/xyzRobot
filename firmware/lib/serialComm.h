#ifndef SerialComm_h
#define SerialComm_h
#include "Arduino.h"
#include "../lib/logger.h"

// QueueArray <char*> msgQueue;


void rxThread();
void send_log(char *message);
boolean emergencyRequest(char *buffer);

#endif