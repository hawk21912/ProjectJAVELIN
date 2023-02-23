/*
 * Servo.c
 *
 *  Created on: Aug 30, 2022
 *      Author: joshh
 */

/*
 * servo_t STR;
    STR.rawMIN=100;
    STR.rawMAX=200;
    STR.degMAX = 100;
    STR.chl= 3;
    STR.htim = &htim2;
 */

#include "Servo.h"


void servo_Set(servo_t *servo, int deg) {
    deg += servo->degMAX; // centers requested degree from -degMAX to degMAX to 0 - 2*degreeMAX

    if (0 <= deg && deg <= 2 * servo->degMAX) {

        uint16_t value = servo->rawMIN + (((100*deg) / (2 * servo->degMAX)) * (servo->rawMAX - servo->rawMIN))/100;
        volatile uint32_t *p = (&servo->htim->Instance->CCR1);
        p = p + servo->chl - 1;
        *p = (uint32_t) value;
        servo->deg = deg - servo->degMAX;
        servo->raw = value;
    }


}

void Servo_Set_Force(TIM_HandleTypeDef *htim, uint8_t chl, uint16_t val) {

        volatile uint32_t *p = (&htim->Instance->CCR1);
        p = p+ (chl - 1) ;
        *p = (uint32_t) val;

}

