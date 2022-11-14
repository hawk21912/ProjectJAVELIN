//
// Created by joshh on 10/13/2022.
//

#ifndef JAVELIN_STEPPER_H
#define JAVELIN_STEPPER_H

#include "gpio.h"

typedef struct  {

    int pos;
    int des;
    GPIO_TypeDef* StepPort;
    uint16_t StepPin;
    GPIO_TypeDef* DirPort;
    uint16_t DirPin;
    GPIO_TypeDef* EnPort;
    uint16_t EnPin  ;
    int enabled;
    int dir;
    int state;
    int step;

}StepperMotorTypeDef;

void StepInit(StepperMotorTypeDef* motor);
void StepMoveDir(StepperMotorTypeDef* motor, int D);
int StepChkDir(StepperMotorTypeDef* motor,int DesLoc);
void StepGoTo(StepperMotorTypeDef* motor, int DesLoc);
void StepUpdate(StepperMotorTypeDef* motor, int DesLoc);
void StepSetDir(StepperMotorTypeDef* motor,int D);
void StepEnable(StepperMotorTypeDef* motor, int EN);
void Step(StepperMotorTypeDef* motor);
#endif //JAVELIN_STEPPER_H
