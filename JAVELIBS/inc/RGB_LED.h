/*
 * RGB_LED.h
 *
 *  Created on: Aug 15, 2022
 *      Author: joshh
 */

#ifndef INC_RGB_LED_H_
#define INC_RGB_LED_H_

#include "main.h"
#include "tim.h"


typedef struct{
  uint8_t Red;
  uint8_t Green;
  uint8_t Blue;
}RGB_Type;



extern RGB_Type GREEN;
extern RGB_Type RED;
extern RGB_Type BLUE;
extern RGB_Type WHITE;
extern RGB_Type BLACK;


TIM_HandleTypeDef *RGB;


uint32_t PWMMAX;


uint32_t chnl[3];


void RGB_PWM_SET(uint8_t R,uint8_t G,uint8_t B);
void RGB_SET(RGB_Type *color);
void RGB_PWM_Define(TIM_HandleTypeDef *htim, __IO uint32_t r, __IO uint32_t g, __IO uint32_t b);
void RGB_FORCE(TIM_HandleTypeDef *htim,uint8_t chnl,uint8_t val);



#endif /* INC_RGB_LED_H_ */
