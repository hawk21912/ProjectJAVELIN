/*
 * Servo.h
 *
 *  Created on: Aug 30, 2022
 *      Author: joshh
 */

#ifndef INC_SERVO_H_
#define INC_SERVO_H_



#include "main.h"
typedef struct Servo_TypeDef{
    TIM_HandleTypeDef *htim; //Timer used
    uint8_t chl;            // timer channel
    int deg;                // current position in degrees
    uint16_t raw;           // raw value currently inputed
    uint16_t rawMAX;        // max acceptable input rawMIN - TIM->INSTANCE->ARR;
    uint16_t rawMIN;        // min accaptable input
    uint8_t  degMAX;        // sets range to -degMAX to degMAX
}servo_t;
void servo_Set(servo_t *servo, int deg);

#endif /* INC_SERVO_H_ */
