#include "TraxxasESC.h"

//
// Created by joshh on 10/20/2022.
//
void setPower(TraxxasESC* ESC,int power){

    ESC->htim->Instance->CCR1;
    int chnl = ESC->PWM_CHNL;

    if(chnl > 0 && chnl <7){
        int input = ESC->htim->Instance->ARR*(1.5+ (power/200));
        uint32_t *p = (&ESC->htim->Instance->CCR1);
        p = p +chnl-1;
        *p = (uint32_t) input;
    }


}
void armESC(TraxxasESC* ESC){

    setPower(&ESC,100);
    HAL_Delay(100);
    setPower(&ESC,-100);
    HAL_Delay(100);
    setPower(&ESC,0);
    HAL_Delay(500);


}