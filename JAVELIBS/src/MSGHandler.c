#include <memory.h>
#import "gpio.h"
#include "MSGHandler.h"

#include "usart.h"
#include "stdio.h"
#include "TraxxasESC.h"
#include "Servo.h"

osMessageQueueId_t RX_msg_queueHandle;
osMessageQueueAttr_t RX_msg_queue_attributes;
uint32_t lastRecMsg;

void MSGinit(){
    RX_msg_queue_attributes.name = "RX_msg_queue";
    RX_msg_queueHandle = osMessageQueueNew (64, sizeof(JAVMSG_t), &RX_msg_queue_attributes);
    HAL_UART_Transmit(&huart3,"MSG Queue Init\r\n",20,10);
}


void MSGHandleLoop(){
JAVMSG_t msg;
uint32_t mas[8];
memset(&msg, 0, sizeof(msg)); //resets struct to 0

    if(osMessageQueueGetCount(RX_msg_queueHandle) >0){

        int status = osMessageQueueGet(RX_msg_queueHandle,(void *)&msg,0,0);
        if(status ==osOK){
            MSGReceive(msg);
        } else if(status == osErrorParameter ) {
            HAL_UART_Transmit(&huart3, "os is not okay\n\r",16,10);
        } else if(status == osErrorTimeout){
            HAL_UART_Transmit(&huart3, "MSG TIMEOUT\n\r",16,10);
        } else if(status == osErrorResource){
            HAL_UART_Transmit(&huart3, "MSG bad\n\r",16,10);
        }


        //HAL_UART_Transmit(&huart3,"msg receviced\n\r",20,10);
    }
    else {
        //HAL_UART_Transmit(&huart3, "no msg receviced\n\r", 25, 10);
    }
}

uint16_t PWMRT;
uint16_t PWMLT;
int governer = 4;
void MSGReceive(JAVMSG_t msg){

    char debug[100];

    int len = sprintf(debug,"id %d byte 2: %d byte 3: %d byte 4 %d  byte 5: %d byte 6 %d byte 7 %d byte 8 %d\r\n",
                      msg.id,msg.Byte2,msg.Byte3,msg.Byte4,msg.Byte5,msg.Byte6,msg.Byte7,msg.Byte8);
    //HAL_UART_Transmit(&huart3,debug,len,10);
	switch( msg.id){
        case 0xa1:
            HAL_GPIO_WritePin(GPIOB, LD1_Pin, msg.Byte2 != 0);
            HAL_GPIO_WritePin(RELAY_GPIO_Port,RELAY_Pin,msg.Byte2 != 0);
            break;

        case 0xa3:;
            uint16_t PWMVAL = (msg.Byte2<< 8) | msg.Byte3;
            TIM12->CCR1 = PWMVAL;
            PWMVAL = (msg.Byte4<< 8) | msg.Byte5;

            servo_InputPWM(&STR,PWMVAL);
        break;

        case 0x12:

            if(msg.Byte2 == 0x01){
                HAL_UART_Transmit(&huart3, "test msg recieved\r\n",20,10);
            }

            break;

        case 0xa4:

           // PWMRT = (msg.Byte2<<8)| msg.Byte3;
           // PWMLT = (msg.Byte4<<8)| msg.Byte5;

           PWMRT = msg.Byte2/governer;
           PWMLT = msg.Byte3/governer;

            ESC_InputPWM(&DRV,PWMRT,PWMLT);
           // HAL_UART_Transmit(&huart3, "motor set to\n",20,10);
           // HAL_UART_Transmit(&huart3,debug,len,10);

            break;

        default:

            break;

	}


}
