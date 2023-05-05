//
// Created by joshh on 10/13/2022.
//

#ifndef JAVELIN_STEPPER_H
#define JAVELIN_STEPPER_H

#include "gpio.h"

typedef struct  StepperMotorTypeDef{

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

}stepper_t;

extern stepper_t SRC;
extern stepper_t SRN;

void StepInit(stepper_t* motor);
void StepMoveDir(stepper_t* motor, int D);
int StepChkDir(stepper_t* motor,int DesLoc);
void StepGoTo(stepper_t* motor, int DesLoc);
void StepUpdate(stepper_t* motor, int DesLoc);
void StepSetDir(stepper_t* motor,int D);
void StepEnable(stepper_t* motor, int EN);
void Step(stepper_t* motor);
#endif //JAVELIN_STEPPER_H
