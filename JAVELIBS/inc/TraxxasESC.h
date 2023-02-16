//
// Created by joshh on 10/20/2022.
//

#ifndef JAVELIN_TRAXXASESC_H
#define JAVELIN_TRAXXASESC_H


#include "tim.h"
#include "cmsis_os2.h"

enum RLO_state{
    cleared,
    notCleared,
};
enum direction{
    Forward,
    Reverse,
    Arming,
};

enum state{
    UnArmed,
    Armed,

};

typedef struct TraxxasESC_TypeDef{

    TIM_HandleTypeDef *htim;
    int PWM_CHNL;
    int state;
    int pwr; //    -MAXIMUMOVERDRIVE < pwr < MAXIMUMOVERDRIVE
    uint16_t raw;
    uint16_t rawMAX;
    uint16_t rawMIN;
    int MAXIMUMOVERDRIVE; //power range
    int direction;    // 0 for pos 1 for neg
    int reverseLockOut;

}traxxasESC_t;
void revsereLockout_clear( traxxasESC_t *ESC);
void setPower(traxxasESC_t *ESC,int power,int dir);
void armESC_RTOS(traxxasESC_t *ESC);
void armESC(traxxasESC_t *ESC);
#endif //JAVELIN_TRAXXASESC_H
