


#include "cmsis_os.h"

typedef struct {
    uint32_t id;
    uint32_t Byte2;
    uint32_t Byte3;
    uint32_t Byte4;
    uint32_t Byte5;
    uint32_t Byte6;
    uint32_t Byte7;
    uint32_t Byte8;
}JAVMSG_t;

void MSGReceive(JAVMSG_t msg);
void MSGHandleLoop();
void MSGinit();
extern int johnny;
extern osMessageQueueId_t RX_msg_queueHandle;
extern osMessageQueueAttr_t RX_msg_queue_attributes;
