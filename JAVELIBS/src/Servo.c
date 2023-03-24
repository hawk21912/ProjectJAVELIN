/*
 * Servo.c
 *
 *  Created on: Aug 30, 2022
 *      Author: joshh
 */

#include <stdio.h>
#include "Servo.h"
#include "usart.h"
servo_t STR;
void servo_Set(servo_t *servo, int deg) {
    servo->deg = deg;

    //deg -= servo->degMAX; // centers requested degree from -degMAX to degMAX to 0 - 2*degreeMAX

    if (0 <= deg && deg <= 2 * servo->degMAX) {
        //val          = ESC->rawMIN + (((100 * power) / (2 * ESC->MAXIMUMOVERDRIVE)) * (ESC->rawMAX - ESC->rawMIN)) / 100;
        uint16_t value = servo->rawMIN + (((100*deg) / (2 * servo->degMAX)) * (servo->rawMAX - servo->rawMIN))/100;
        volatile uint32_t *p = (&servo->htim->Instance->CCR1);
        p = p + servo->chl - 1;
        *p = (uint32_t) value;
        servo->raw = value;
    }

    char msg[100];
    int len = sprintf(msg, "servo set to | pwm:%d | deg:%d\n\r",servo->raw ,servo->deg);
    HAL_UART_Transmit(&huart3, msg, len, 100);

}
void servo_InputPWM(servo_t *servo,int PWM){

    servo->degMSG =(servo->degMAX* PWM) / 32767 ;


}
void Servo_Set_Force(TIM_HandleTypeDef *htim, uint8_t chl, uint16_t val) {

        volatile uint32_t *p = (&htim->Instance->CCR1);
        p = p+ (chl - 1) ;
        *p = (uint32_t) val;

}


