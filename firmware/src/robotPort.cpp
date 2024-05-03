#include "../lib/robotPort.h"

#define MAXIMUM_SERIAL_BUFFER_LENGTH    64
#define MAXIMUM_BUFFER_FOR_A_COMMAND    200

// void split_string_into_substrings(String * readString)
// {
//     uint8_t stringCount = 0;
//     String *msgTemp = readString;
//     String strs[20];

//     while (msgTemp.length() > 0)
//     {
//         int index = msgTemp.indexOf(':');
//         if (index == -1) // No space found
//         {
//             break;
//         }
//         else
//         {
//             strs[stringCount] = msgTemp.substring(0, index);
//             msgTemp = msgTemp.substring(index+1);
//         }
//         stringCount++;
//     }
// }

// void send_execution_pass(){}
// void send_execution_fail(){}
// void send_ping(){}
// void send_discard_msg(){}
void send_continue_receiving_command_data()
{
    // Serial.println("please continue");
}

void send_pass()
{
    Serial.write("{P}");
    // Serial.println("{P}");
}

void send_fail()
{
    Serial.write("{F}");
    // Serial.println("{F}");
}

void send_emergency_executed()
{
    Serial.write("{Emergency}");    
}

boolean receive_command_from_robot_controller(String &readString)
{
    // static char msg_buff[250];
    int count = 0;

    if (Serial.available()>0)
    {
        if (Serial.read() == '{')
        {
            readString += '{';
            while (true)
            {
                if (Serial.available() > 0) 
                {
                    char inComingByte = Serial.read();
                    
                    // Serial.print(inComingByte);

                    readString += inComingByte;
                    if (inComingByte == '}') 
                    { 
                        // log_info("Receive a full Command!");  
                        // Serial.println("Receive a full Command");
                        return true;
                    }
                    else if (readString.length() > MAXIMUM_BUFFER_FOR_A_COMMAND - 1)
                    {
                        // send_discard_msg();
                        return false;
                    }
                } else if (count++ < 100) {
                    delay(10);
                } else {
                    // log_info("Reading Command Timeout!");
                    // log_info(readString);
                    // Serial.println("Timeout!");
                    // // Serial.println(readString);
                    break;
                }
            }
        }
    }
    return false;
}

/*
Receive the pulse indicator
*/
boolean receive_command_from_robot_controller_v2()
{
    // static char msg_buff[250];
    int timeerCount = 0;
    uint16_t dataIndex = 0;
    boolean dataPulseArray[10000] = {0};
    String strTemp;
    String testStr;
    String component;
    String command;
    uint8_t count = 0;
    boolean receiveStatedHeader = false;
    boolean receiveEndHeader = false;

    if (Serial.available()>0)
    {
        if (Serial.read() == '{')
        {
            receiveStatedHeader = true;
            // uint8_t bufferLengthCounter = 1;
            while (true)
            {
                if (Serial.available() > 0) 
                {
                    char inComingByte = Serial.read();
                    // bufferLengthCounter++;
                    
                    if (inComingByte == ':' && count == 0)
                    {
                        count++;
                        component = strTemp;
                        // Serial.println("Receive component");
                        // Serial.println(component);
                        strTemp = testStr;
                    }
                    else if (inComingByte == ':' && count == 1)
                    {
                        count++;
                        command = strTemp;
                        // Serial.println("Receive command");
                        // Serial.println(command);
                        strTemp = testStr;
                    }
                    else if (inComingByte == '}') 
                    { 
                        // log_info("Receive a full Command!");  
                        // Serial.println("Receive a full Command");
                        // Serial.println(strTemp);
                        return true;
                    }
                    else if (count == 2 && component == 'TESTER' && command == 'PULSE')
                    {
                        dataPulseArray[dataIndex] = inComingByte;
                        dataIndex++;
                    }
                    else  strTemp += inComingByte;

                } 
                else if (timeerCount++ < 100) 
                {
                    if (receiveStatedHeader == true)
                    {
                        send_continue_receiving_command_data();
                    }
                    delay(10);
                } 
                else 
                {
                    // Serial.println("Timeout!");
                    break;
                }

            }
        }
    }
    return false;
}

boolean receive_command_from_robot_controller_v3(String &component, String &command, String &data)
{
    uint8_t count = 0;
    uint8_t timerCount = 0;
    String strTemp;
    String testStr;
    String componentTemp;
    String commandTemp;
    String dataTemp;

    boolean receivedFullCmd = false;
    boolean receivedCorrectCmd = false;

    if (Serial.available()>0)
    {
        if (Serial.read() == '{')
        {   
            while (true)
            {
                if (Serial.available() > 0) 
                {
                    char inComingByte = Serial.read();
                    
                    if (inComingByte == ':' && count == 0)
                    {
                        count++;
                        componentTemp = strTemp;
                        strTemp = testStr;
                    }
                    else if (inComingByte == ':' && count == 1)
                    {
                        count++;
                        commandTemp = strTemp;
                        strTemp = testStr;
                    }
                    else if (inComingByte == '}') 
                    { 
                        receivedFullCmd = true;

                        if (count == 2 ) 
                        {
                            receivedCorrectCmd = true;
                        }
                        if (receivedCorrectCmd == true && receivedFullCmd == true)
                        {
                            dataTemp  = strTemp;
                            component = componentTemp;
                            command   = commandTemp;
                            data      = dataTemp;
                            // Serial.flush();
                            return true;
                        }
                        else
                        {
                            return false;
                        }
                    }
                    else  strTemp += inComingByte;

                } 
                else if (timerCount++ < 100) 
                {
                    delay(10);
                } 
                else 
                {
                    break;
                }
            }
        }
    }
    return false;
}

