/*
 * RGB_LED.c
 *
 *  Created on: Aug 15, 2022
 *      Author: joshh
 */

#include "RGB_LED.h"


 RGB_Type GREEN = {0,255,0};
 RGB_Type RED = {255,0,0};
 RGB_Type BLUE = {0,0,255};
 RGB_Type WHITE = {255,255,255};
 RGB_Type BLACK = {0,0,0};

void RGB_FORCE(TIM_HandleTypeDef *htim,uint8_t chnl,uint8_t val){

	if(chnl > 0 && chnl <7){
		int input = htim->Instance->ARR*(255-val)/255;
		uint32_t *p = (&htim->Instance->CCR1);
		p = p +chnl-1;
		*p = (uint32_t) input;
	}
}




void RGB_PWM_SET(uint8_t R,uint8_t G,uint8_t B){

	int val[] = {R,G,B};

	for(int i = 0;i<=2;i++){

		switch(chnl[i]){



		case 1:
			RGB->Instance->CCR1 = PWMMAX*(255-val[i])/255;
			break;

		case 2:
			RGB->Instance->CCR2 = PWMMAX*(255-val[i])/255;
			break;

		case 3:
			RGB->Instance->CCR3 = PWMMAX*(255-val[i])/255;
			break;

		case 4:
			RGB->Instance->CCR4 = PWMMAX*(255-val[i])/255;
			break;

		case 5:
			RGB->Instance-> CCR5 = PWMMAX*(255-val[i])/255;
			break;

		case 6:
			RGB->Instance->CCR6 = PWMMAX*(255-val[i])/255;
			break;
		}
	}
}






void RGB_PWM_Define(TIM_HandleTypeDef *htim, __IO uint32_t r, __IO uint32_t g, __IO uint32_t b){



	RGB = htim;

	chnl[0]= r;
	chnl[1] = g;
	chnl[2] = b;


	PWMMAX = RGB->Instance->ARR;

	uint32_t temp = (r-1)*4U;

	HAL_TIM_PWM_Start(&htim->Instance,(r-1)*4U);
	HAL_TIM_PWM_Start(&htim->Instance,(g-1)*4U);
	HAL_TIM_PWM_Start(&htim->Instance,(b-1)*4U);




}


