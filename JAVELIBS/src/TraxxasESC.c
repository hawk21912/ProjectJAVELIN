#include <stdio.h>
#include "TraxxasESC.h"
#include "usart.h"

//
// Created by joshh on 10/20/2022.
//

traxxasESC_t DRV;
traxxasESC_t LED;


void setPower(traxxasESC_t *ESC, int power, int dir) {
    ESC->pwr = power;
    static int prevDir = Arming;
    int chnl = ESC->PWM_CHNL;
    uint16_t val = 0;

    /*  if(prevDir != dir && dir == Reverse && ESC->reverseLockOut != cleared){
      } else if(prevDir != dir && dir == Forward){
          ESC->reverseLockOut = notCleared;
      }
  */
    power += ESC->MAXIMUMOVERDRIVE;
    val = ESC->rawMIN + (((100 * power) / (2 * ESC->MAXIMUMOVERDRIVE)) * (ESC->rawMAX - ESC->rawMIN)) / 100;
    if (chnl > 0 && chnl < 14) {
        volatile uint32_t *p = (&ESC->htim->Instance->CCR1);
        p = p + chnl - 1;
        *p = (uint32_t) val;
    }
    char msg[100];
    int len = sprintf(msg, "pwm set to | pwm:%d | pwr:%d\n\r", val,power);
    ESC->raw = val;

    //HAL_UART_Transmit(&huart3, msg, len, 100);

}

void revsereLockout_clear(traxxasESC_t *ESC) {

    if (ESC->reverseLockOut != cleared) {
        setPower(ESC, 0, Arming);
        osDelay(200);
        setPower(ESC, -10, Arming);
        osDelay(200);
        setPower(ESC, 0, Arming);
        osDelay(200);
        setPower(ESC, -15, Arming);
        osDelay(200);
        ESC->reverseLockOut = cleared;
    }
};

void armESC(traxxasESC_t *ESC) {

    setPower(ESC, 0, Arming);
    HAL_Delay(50);
    setPower(ESC, 100, Arming);
    HAL_Delay(50);
    setPower(ESC, -100, Arming);
    HAL_Delay(50);
    setPower(ESC, 0, Arming);

}

void armESC_RTOS(traxxasESC_t *ESC) {

    static int armingstate = 0;

    if (ESC->state == UnArmed) {

        setPower(ESC, 0, Arming);
        osDelay(200);
        setPower(ESC, 10, Arming);
        osDelay(200);
        setPower(ESC, -10, Arming);
        osDelay(200);
        setPower(ESC, 0, Arming);

        ESC->state = Armed;
        HAL_UART_Transmit(&huart3, "ESC armed!\n\r", 15, 10);
        osDelay(200);


    }

}


void ESC_InputPWM(traxxasESC_t *ESC,uint16_t RT,uint16_t LT){

    //pwm value is raw uint16_t
    // TODO: set power to be based off of RT - LT and center around 0

    int val = (((RT - LT)*(1000*ESC->MAXIMUMOVERDRIVE) / 255)/1000); //I HATE FLOATS!!!!!!!!!!!
    ESC->msgPwr = val;
}

