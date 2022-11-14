//
// Created by joshh on 10/13/2022.
//

#include "stepper.h"

void StepMoveDir(StepperMotorTypeDef* motor, int D);


int StepChkDir(StepperMotorTypeDef* motor,int DesLoc){

    if(DesLoc > motor->pos ){
        return 1;

    }
    else if( DesLoc < motor->pos){
        return 2;
    }
    else if( DesLoc == motor->pos){
        return 0;
    }
    else{
        return -1;
    }

}
void StepUpdate(StepperMotorTypeDef* motor, int DesLoc){

    //checks the motor direction
    /* 0 = no spin
     * 1 = Spin Clockwise
     * 2 = Spin Counter
     * -1 = oh shit what happened
     */
    int dir =StepChkDir(motor,DesLoc);

    /* if old direction = new direciton then step \
     *
     * if old direciton != new directino then change inputs this is
     * done since it takes change for the device to adjust
     *
     * if new direciton = -1 ABORT
     */

    if( dir == -1){
        //put in some error codes
    }
    else if( dir == motor->dir){
        Step(motor);
    }
    else if(dir != motor->dir){
        StepSetDir(motor,dir);
    }

}

void Step(StepperMotorTypeDef* motor){

    if(motor->step == 1){
        motor->step =0;
        HAL_GPIO_WritePin(motor->StepPort,motor->StepPin,GPIO_PIN_SET);
    }
    else if(motor->step ==0){
        motor->step =1;
        HAL_GPIO_WritePin(motor->StepPort,motor->StepPin,GPIO_PIN_RESET);
        motor->pos +=1;
    }
    else{

        //put in some error codes
    }

}


void StepGoTo(StepperMotorTypeDef* motor, int DesLoc){
    motor->des = DesLoc;
}

void StepSetDir(StepperMotorTypeDef* motor,int D){


    if(D == 1){
        motor->dir =1;
        HAL_GPIO_WritePin(motor->DirPort,motor->DirPin,GPIO_PIN_SET);
    }
    else if(D ==0){
        motor->dir =0;
        HAL_GPIO_WritePin(motor->DirPort,motor->DirPin,GPIO_PIN_RESET);
    }
    else{

        //put in some error codes
    }

}
void StepEnable(StepperMotorTypeDef* motor, int EN){

    if(EN == 1){
        motor->enabled =1;
        HAL_GPIO_WritePin(motor->EnPort,motor->EnPin,GPIO_PIN_SET);
    }
    else if(EN ==0){
        motor->enabled =0;
        HAL_GPIO_WritePin(motor->EnPort,motor->EnPin,GPIO_PIN_RESET);
    }
    else{

        //put in some error codes
    }
}

void StepInit(StepperMotorTypeDef* motor){

    StepEnable(motor,motor->enabled);
    StepSetDir(motor,motor->dir);

}
/*example define
 *
 *
    StepperMotorTypeDef* mot;
    mot->pos =0;
    mot->des =0;
    mot->StepPort =LD1_GPIO_Port;
    mot->StepPin = LD1_Pin;
    mot->DirPort = LD2_GPIO_Port;
    mot->DirPin =LD2_Pin;
    mot->EnPort = LD3_GPIO_Port;
    mot->EnPin =LD3_Pin;
    mot->enabled = 0;
    mot->dir = 0;
    mot->state = 0;
    mot->step = 0;
 *
 *
 *
 *
 */