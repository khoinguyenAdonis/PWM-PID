/*
 * pid.c
 *
 *  Created on: Sep 10, 2023
 *      Author: khoi7
 */

#include "main.h"
#include "pid.h"
#include "math.h"
#define Kp 3
#define Ki 0.0001
#define Kd 2
#define max_crr_value  760

extern TIM_HandleTypeDef htim1;

double output;
float current_error = 0, previous_error = 0;
float integral = 0, derivative = 0;
uint32_t crr_value,CRR_value;
float  pid_value = 0;
uint32_t a =0;
static uint32_t convert_pid_to_crr(float pid_value)
{

    float max_pid_value = 1000.0;
  //  uint32_t max_crr_value = 999;

    crr_value = (uint32_t)(fabs (pid_value / max_pid_value * max_crr_value));

    // Giới hạn giá trị CRR trong phạm vi cho phép
    if (crr_value > max_crr_value) {
      return  crr_value = max_crr_value;
    } else if (crr_value < 0) {
        return crr_value = 0;
    }else   return crr_value;

}

void calculate_pid(float setpoint, float actual_value)
{

    current_error = setpoint - actual_value;


    integral += current_error;


    derivative = current_error - previous_error;


     pid_value = Kp*current_error + Ki*integral + Kd*derivative;


    previous_error = current_error;


     CRR_value = convert_pid_to_crr( pid_value);
     if (current_error < 0 ) {
     	 if ( HAL_GetTick() - a <2000){

              __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, CRR_value);
              __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
              }
     	 else{a =HAL_GetTick();
     	 current_error = 0;
     	 integral = 0;
     	 derivative = 0;
     	 previous_error = 0;}

          } else {
              __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, CRR_value);
              __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
     }

}


