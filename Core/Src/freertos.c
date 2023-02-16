/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usart.h"
#include "tcpserver.h"
#include "iwdg.h"
#include "stdio.h"
#include "adc.h"
#include "TraxxasESC.h"
#include "Servo.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
volatile uint32_t adcval[3];
/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Blink */
osThreadId_t BlinkHandle;
const osThreadAttr_t Blink_attributes = {
  .name = "Blink",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for IDWGTrigger */
osThreadId_t IDWGTriggerHandle;
const osThreadAttr_t IDWGTrigger_attributes = {
  .name = "IDWGTrigger",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for ADCPoll */
osThreadId_t ADCPollHandle;
const osThreadAttr_t ADCPoll_attributes = {
  .name = "ADCPoll",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for PSFunctions */
osThreadId_t PSFunctionsHandle;
const osThreadAttr_t PSFunctions_attributes = {
  .name = "PSFunctions",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for SSFunctions */
osThreadId_t SSFunctionsHandle;
const osThreadAttr_t SSFunctions_attributes = {
  .name = "SSFunctions",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for DSFunctions */
osThreadId_t DSFunctionsHandle;
const osThreadAttr_t DSFunctions_attributes = {
  .name = "DSFunctions",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for RX_msg_queue */
osMessageQueueId_t RX_msg_queueHandle;
const osMessageQueueAttr_t RX_msg_queue_attributes = {
  .name = "RX_msg_queue"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void Blink_Init(void *argument);
void IDWGTrigger_Init(void *argument);
void ADCPoll_Init(void *argument);
void PSFunctions_Init(void *argument);
void SSFunctions_Init(void *argument);
void DSFunctions_Init(void *argument);

extern void MX_LWIP_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void configureTimerForRunTimeStats(void);
unsigned long getRunTimeCounterValue(void);

/* USER CODE BEGIN 1 */
/* Functions needed when configGENERATE_RUN_TIME_STATS is on */
__weak void configureTimerForRunTimeStats(void)
{

}

__weak unsigned long getRunTimeCounterValue(void)
{
return 0;
}
/* USER CODE END 1 */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of RX_msg_queue */
  RX_msg_queueHandle = osMessageQueueNew (32, sizeof(uint16_t), &RX_msg_queue_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of Blink */
  BlinkHandle = osThreadNew(Blink_Init, NULL, &Blink_attributes);

  /* creation of IDWGTrigger */
  IDWGTriggerHandle = osThreadNew(IDWGTrigger_Init, NULL, &IDWGTrigger_attributes);

  /* creation of ADCPoll */
  ADCPollHandle = osThreadNew(ADCPoll_Init, NULL, &ADCPoll_attributes);

  /* creation of PSFunctions */
  PSFunctionsHandle = osThreadNew(PSFunctions_Init, NULL, &PSFunctions_attributes);

  /* creation of SSFunctions */
  SSFunctionsHandle = osThreadNew(SSFunctions_Init, NULL, &SSFunctions_attributes);

  /* creation of DSFunctions */
  DSFunctionsHandle = osThreadNew(DSFunctions_Init, NULL, &DSFunctions_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* init code for LWIP */
  MX_LWIP_Init();
  /* USER CODE BEGIN StartDefaultTask */
 // osThreadDef(TCPServer, tcpserver_init, osPriorityNormal, 0, 1024);
 // TCPServerHandle = osThreadCreate(osThread(TCPServer), NULL);
  tcpserver_init();
  /* Infinite loop */


  for(;;)
  {

    osDelay(1000);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_Blink_Init */
#define TEMPSENSOR_CAL1_ADDR ((uint16_t*) (0x1FF1E820U)
#define TEMPSENSOR_CAL2_ADDR ((uint16_t*) (0x1FF1E840U)
#define TEMPSENSOR_CAL1_TEMP (( int32_t)   30)
#define TEMPSENSOR_CAL2_TEMP (( int32_t)  110)
/**
* @brief Function implementing the Blink thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Blink_Init */
void Blink_Init(void *argument)
{
  /* USER CODE BEGIN Blink_Init */
  /* Infinite loop */
    float tempcal = (TEMPSENSOR_CAL2_TEMP-TEMPSENSOR_CAL1_TEMP) /( (uint32_t) *TEMPSENSOR_CAL2_ADDR)  -   (uint32_t) *TEMPSENSOR_CAL1_ADDR)   ) ;

	int cnt = 0;
		  char msg[100];
		uint32_t tick;
  //  HAL_ADC_Start(&hadc3);
  //  HAL_ADC_PollForConversion(&hadc3, 100);
  float vref,vbat,temp;
  for(;;)
  {
	  tick=  osKernelGetTickCount();
    //  adcval = HAL_ADC_GetValue(&hadc3);
    vref= adcval[2]*4*3.3/65536;
    vbat = adcval[1]*4*3.3/65536;
    temp = .02*(adcval[0]-(uint32_t) *TEMPSENSOR_CAL2_ADDR) )+30;
	 // int len = sprintf(msg,"MS Since last issue :%d\n\r",tick);
      int len = sprintf(msg,"MS Since last issue :%d Temp =%f Vbat = %f vref = %f\n\r",tick,temp,vbat,vref );
	 	 // HAL_UART_Transmit(&huart3, msg,len , 100);
	 	  cnt++;


    osDelay(1000);
  }
  /* USER CODE END Blink_Init */
}

/* USER CODE BEGIN Header_IDWGTrigger_Init */
/**
* @brief Function implementing the IDWGTrigger thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_IDWGTrigger_Init */
void IDWGTrigger_Init(void *argument)
{
  /* USER CODE BEGIN IDWGTrigger_Init */
  /* Infinite loop */
  for(;;)
  {
	  HAL_IWDG_Refresh(&hiwdg1);
    osDelay(1);
  }
  /* USER CODE END IDWGTrigger_Init */
}

/* USER CODE BEGIN Header_ADCPoll_Init */

uint32_t ADC3_Chnls[3] = {ADC_CHANNEL_TEMPSENSOR,ADC_CHANNEL_VBAT,ADC_CHANNEL_VREFINT};

void ADC_ChnlSel(ADC_HandleTypeDef *hadc, int Chnl){

    ADC_ChannelConfTypeDef sConfig = {0};

    sConfig.Channel = ADC3_Chnls[Chnl];
    //sConfig.Channel = ADC_CHANNEL_TEMPSENSOR;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_387CYCLES_5;
    sConfig.SingleDiff = ADC_SINGLE_ENDED;
    sConfig.OffsetNumber = ADC_OFFSET_NONE;
    sConfig.Offset = 0;
    sConfig.OffsetSignedSaturation = DISABLE;
    if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
    {
        Error_Handler();
    }

}

/**
* @brief Function implementing the ADCPoll thread.
* @param argument: Not used
* @retval None
 * TODO calculate time to see if all can be converted in one go
*/
/* USER CODE END Header_ADCPoll_Init */
void ADCPoll_Init(void *argument)
{
  /* USER CODE BEGIN ADCPoll_Init */
  /* Infinite loop */
    int adcchnl = 0;
    HAL_ADC_Start(&hadc3);
    HAL_ADC_PollForConversion(&hadc3, 100);
  for(;;)
  {
         adcval[adcchnl] = HAL_ADC_GetValue(&hadc3);
         HAL_ADC_Stop(&hadc3);

         adcchnl++;
         if(adcchnl >2){
             adcchnl = 0;
         }
         ADC_ChnlSel(&hadc3,adcchnl);
         HAL_ADC_Start(&hadc3);
         HAL_ADC_PollForConversion(&hadc3, 100);


    osDelay(1);
  }
  /* USER CODE END ADCPoll_Init */
}

/* USER CODE BEGIN Header_PSFunctions_Init */
/**
* @brief Function implementing the PSFunctions thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_PSFunctions_Init */
void PSFunctions_Init(void *argument)
{
    HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_4);

    servo_t STR;
    STR.rawMIN=100;
    STR.rawMAX=200;
    STR.degMAX = 100;
    STR.chl= 3;
    STR.htim = &htim2;


    traxxasESC_t LED;
    LED.reverseLockOut=notCleared;
    LED.state =UnArmed;
    LED.rawMIN=0;
    LED.rawMAX=TIM12->ARR;
    LED.MAXIMUMOVERDRIVE = 100;
    LED.direction=Forward;
    LED.PWM_CHNL= 1;
    LED.htim = &htim12;

    traxxasESC_t ESC;
    ESC.reverseLockOut=notCleared;
    ESC.state =UnArmed;
    ESC.rawMIN=100;
    ESC.rawMAX=200;
    ESC.MAXIMUMOVERDRIVE = 100;
    ESC.direction=Forward;
    ESC.PWM_CHNL= 4;
    ESC.htim = &htim2;



    int cnt = -100;
  /* USER CODE BEGIN PSFunctions_Init */
  /* Infinite loop */
  for(;;)
  {

      /*while(ESC.state != Armed){
          armESC_RTOS(&ESC);
      }*/

      revsereLockout_clear(&ESC);
    while( cnt <= 100){

        setPower(&LED, cnt,Arming);
        cnt++;
        osDelay(5);
    }
    while(cnt >= -100){
        setPower(&LED, cnt,Arming);
        cnt--;
        osDelay(5);
    }


      osDelay(5);
  }
  /* USER CODE END PSFunctions_Init */
}

/* USER CODE BEGIN Header_SSFunctions_Init */
/**
* @brief Function implementing the SSFunctions thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_SSFunctions_Init */
void SSFunctions_Init(void *argument)
{
  /* USER CODE BEGIN SSFunctions_Init */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END SSFunctions_Init */
}

/* USER CODE BEGIN Header_DSFunctions_Init */
/**
* @brief Function implementing the DSFunctions thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_DSFunctions_Init */
void DSFunctions_Init(void *argument)
{
  /* USER CODE BEGIN DSFunctions_Init */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END DSFunctions_Init */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */


/* USER CODE END Application */

