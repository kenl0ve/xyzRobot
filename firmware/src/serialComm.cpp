#include "../lib/serialComm.h"

#define ATE_MESSAGE_REQUEST_ID              0xF0
#define ATE_MESSAGE_ACK_ID                  0xF1
#define ATE_MESSAGE_NACK_ID                 0xF2
#define ATE_MESSAGE_RESPONSE_ID             0xF3
#define ATE_MESSAGE_END_ASYN_1_ID           0xFD
#define ATE_MESSAGE_END_ASYN_2_ID           0xFE
#define ARDUINO_MESSAGE_LOGGER_ID           0xFC

extern char * msgQueue;


boolean emergencyRequest(char *buffer)
{
    if (buffer[3] == 0xA0 && buffer[4] == 0x01)
    {
        // Need to toggle the flag of stopping the robot
        return true;
    }
    else
    {
        return false;
    }
}

void send_ack(byte origId)
{
    char msg_buff[5];
    msg_buff[0] = ATE_MESSAGE_ACK_ID;
    msg_buff[1] = origId;
    msg_buff[2] = 0xFF;
    msg_buff[3] = ATE_MESSAGE_END_ASYN_1_ID;
    msg_buff[4] = ATE_MESSAGE_END_ASYN_2_ID;
    Serial.write(msg_buff, 5);
    delay(10);
}
void send_nack(byte origId)
{
    char msg_buff[5];
    msg_buff[0] = ATE_MESSAGE_NACK_ID;
    msg_buff[1] = origId;
    msg_buff[2] = 0xFF;
    msg_buff[3] = ATE_MESSAGE_END_ASYN_1_ID;
    msg_buff[4] = ATE_MESSAGE_END_ASYN_2_ID;
    Serial.write(msg_buff, 5);
    delay(10);
}

void send_pass_message(byte componentId, byte commandId, const char* msg)
{
///
    char msgReturned[250] = "P";
    char payload[250];
    strcat(msgReturned, ",");
    strcat(msgReturned, msg);

    uint16_t payload_len = sprintf(payload, "%s", msgReturned) + 3; // 3: componentID, commandID, CRC


    char msg_buff[250];
    msg_buff[0] = ATE_MESSAGE_RESPONSE_ID;
    msg_buff[1] = (char)payload_len;
    msg_buff[2] = (char)(payload_len >> 8);

    // Copy requested msg to msg
    memcpy(&msg_buff[3], payload, payload_len - 3);
    msg_buff[3+payload_len] = 0xFF;
    msg_buff[4+payload_len] = ATE_MESSAGE_END_ASYN_1_ID;
    msg_buff[5+payload_len] = ATE_MESSAGE_END_ASYN_2_ID;

    Serial.write(msg_buff, 5);
    delay(10);
}



boolean read_a_whole_message(char* msg)
{
    byte lengthArray[2];
    byte payload[256];
    uint16_t length;
    byte crc;
    byte end1;
    byte end2;

    msg[1] = Serial.read();
    msg[2] = Serial.read();
    length = msg[1] | (msg[2] << 8);
    uint16_t full_length = length + 5;

    // Read payload
    int i = 3;
    while (length > 0)
    {
        msg[i] = Serial.read();
        length -= 1;
        i += 1;
    }

    msg[full_length - 2] = Serial.read();   // End1
    msg[full_length - 1] = Serial.read();   // End2

    if (byte(msg[full_length - 2]) == ATE_MESSAGE_END_ASYN_1_ID && byte(msg[full_length - 1]) == ATE_MESSAGE_END_ASYN_2_ID && Serial.available()==0)
    {
        return true;
    }
    else
    {
        log_warning("Invalid ATE Message");
        return false;
    }
}

void create_logger_message(byte messageId, uint16_t payloadLength, char * payload, char * msg)
{
    uint16_t msgLength = payloadLength + 1;
    *msg = messageId;
    *(msg+1) = (char)msgLength;
    *(msg+2) = (char)(msgLength >> 8);

    // Copy requested msg to msg
    memcpy(&msg[3], payload, payloadLength);
    *(msg+3+payloadLength) = 0xFF;
    *(msg+4+payloadLength) = ATE_MESSAGE_END_ASYN_1_ID;
    *(msg+5+payloadLength) = ATE_MESSAGE_END_ASYN_2_ID;
}

boolean verify_request_message(char * msg)
{
    // msg[0] = ATE_MESSAGE_REQUEST_ID;
    *msg = ATE_MESSAGE_REQUEST_ID;
    boolean ret = read_a_whole_message(msg);
    if (ret == true)
    {
        send_ack(ATE_MESSAGE_REQUEST_ID);
        log_info("Checked --> Valid ATE Request Message --> Send Ack");
    }
    else
    {
        send_nack(ATE_MESSAGE_REQUEST_ID);
        log_warning("Checked --> Invalid ATE Message --> Send Nack");
    }

    return ret;
}
void verify_ack_message()
{

}
void verify_nack_message()
{

}

void send_log(char *message) // send_log("Cannot init X-Axis")
{
    char msg_buff[250];
    char payload[250];
    uint16_t payload_len;
    payload_len = sprintf(payload, "%s", message);

    create_logger_message(ARDUINO_MESSAGE_LOGGER_ID, payload_len, payload, msg_buff);
    Serial.write(msg_buff, payload_len+6);
    delay(10);
}


void rxThread()
{
    // delay(100);
    static char msg_buff[250];

    if (Serial.available()>0)
    {
        byte byteData = Serial.read();

        if (byteData == ATE_MESSAGE_REQUEST_ID)
        {
            log_info("Receive a Request Message ID from ATE");
            if (verify_request_message(msg_buff))
            {
                send_ack(ATE_MESSAGE_REQUEST_ID);
                log_info("Checked --> Valid ATE Request Message --> Send Ack");

                if (!emergencyRequest(msg_buff))
                {
                    msgQueue = &msg_buff[0];
                }
            }
            else
            {
                send_nack(ATE_MESSAGE_REQUEST_ID);
                log_warning("Checked --> Invalid ATE Message --> Send Nack");
            }
        }
        else if (byteData == ATE_MESSAGE_ACK_ID)
        {
            verify_ack_message();
        }
        else if (byteData == ATE_MESSAGE_NACK_ID)
        {
            verify_nack_message();
        }
        else if (byteData == ATE_MESSAGE_END_ASYN_1_ID)
        {
            // Read the next byte to make sure we missed a correct message, then send NACK
            byte byteData = Serial.read();
            if (byteData != ATE_MESSAGE_END_ASYN_2_ID)
            {
                // send_nack();
            }
        }
        else
        {
            // log_info("Wrong Message ID!. Discard!");
            // Serial.println(byteData);
        }
    }
}
