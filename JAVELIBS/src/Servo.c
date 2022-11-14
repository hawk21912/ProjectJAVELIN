/*
 * Servo.c
 *
 *  Created on: Aug 30, 2022
 *      Author: joshh
 */

#include "Servo.h"


static int SERVOMAX = 180;
static int SERVOMIN = 0;

static int SERVOFACTOR = 7;

void Servo_Set(TIM_HandleTypeDef *htim, uint8_t chl, int deg){


	deg+=90;

	if(deg <= SERVOMAX && deg >= SERVOMIN){


		int input = (htim->Instance->ARR)*deg/SERVOMAX;


		input= input*SERVOFACTOR/100;

		int *p = (htim->Instance->CCR1);

		int shift = (chl-1)*0x04;




		 *p = (uint32_t) input;

	}




}

