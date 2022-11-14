//
// Created by joshh on 10/20/2022.
//

#ifndef JAVELIN_TRAXXASESC_H
#define JAVELIN_TRAXXASESC_H


#include "tim.h"

enum DriveStates{MAXIMUMOVERDRIVE=100,NEUTRAL=0,OHSHITRUNAWAY=-100};
typedef struct {

    TIM_HandleTypeDef *htim;
    int PWM_CHNL;
    int state;
    int pwr;

}TraxxasESC;

void setPower(TraxxasESC* ESC,int power);
void armESC();
#endif //JAVELIN_TRAXXASESC_H
