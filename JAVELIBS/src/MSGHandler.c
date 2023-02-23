#import "gpio.h"
#import "MSGHandler.h"

osMessageQueueAttr_t RX_msg_queue_attributes = {
        .name = "RX_msg_queue"
};


void RXMessageAdd(char *msg){


	JAVMSG_t MSG;

    RX_msg_queueHandle = osMessageQueueNew (32, sizeof(JAVMSG_t), &RX_msg_queue_attributes);

}

void RXMessageQueueProcess(JAVMSG_t *msg){

    switch(msg->msgID){

        case MotorSet:
            break;
        case 0xa1:
            HAL_GPIO_WritePin(GPIOB, LD1_Pin, msg->databyte2 != 0);
            break;

        case 0xa3:;

            uint16_t PWMVAL = (msg->databyte2 << 8) | msg->databyte3;
            TIM12->CCR1 = PWMVAL;
            break;
    }

}