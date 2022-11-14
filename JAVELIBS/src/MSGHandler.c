#import "gpio.h"
#import "MSGHandler.h"
#import "tim.h"

void MSGReceive(char *msg){


	switch( msg[0]){
	case 0xa1:

		HAL_GPIO_WritePin(GPIOB,LD1_Pin,msg[1] && 0b01);
		/*
		if(msg[1]==0x11){
			HAL_GPIO_WritePin(GPIOB,LD1_Pin,1);
		} else if (msg[1]==0x00){
			HAL_GPIO_WritePin(GPIOB,LD1_Pin,0);
		}*/
		break;
	case 0xa3:;

	uint16_t PWMVAL = (msg[1] << 8) | msg[2];
	TIM12->CCR1 = PWMVAL;
	break;


	}


}
