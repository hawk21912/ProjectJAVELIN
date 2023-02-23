
#ifndef JAVELIN_MSGHANDLER_H
#define JAVELIN_MSGHANDLER_H

#include "cmsis_os2.h"

#define MotorSet 13



typedef struct JAVMSG_typeDef{
    uint8_t source;
    uint8_t msgID;
    uint8_t databyte2;
    uint8_t databyte3;
    uint8_t databyte4;
    uint8_t databyte5;
    uint8_t databyte6;
    uint8_t databyte7;
    uint8_t databyte8;

}JAVMSG_t;

extern osMessageQueueId_t RX_msg_queueHandle;
extern osMessageQueueAttr_t RX_msg_queue_attributes;


void MSGReceive(char *msg);
void RXMessageQueueProcess(JAVMSG_t *msg);
#endif
