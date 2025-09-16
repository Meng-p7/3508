/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    can.h
  * @brief   This file contains all the function prototypes for
  *          the can.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CAN_H__
#define __CAN_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include <stdint.h>
/* USER CODE END Includes */

extern CAN_HandleTypeDef hcan1;

/* USER CODE BEGIN Private defines */
typedef struct
{
 uint16_t ecd;
 int16_t speed_rpm;
 int16_t given_current;
 uint8_t temperate;
 int16_t last_ecd;
} motor_measure_t;

#define get_motor_measure(ptr, data) \
 { \
 (ptr)->last_ecd = (ptr)->ecd; \
 (ptr)->ecd = (uint16_t)((data)[0] << 8 | (data)[1]); \
 (ptr)->speed_rpm = (uint16_t)((data)[2] << 8 | (data)[3]); \
 (ptr)->given_current = (uint16_t)((data)[4] << 8 | (data)[5]); \
 (ptr)->temperate = (data)[6]; \
 }

extern motor_measure_t motor_chassis[4];  // 声明数组
extern float current_speed_4;
extern float current_location_4;
extern int32_t motor_total_ecd[4];


/* USER CODE END Private defines */

void MX_CAN1_Init(void);

/* USER CODE BEGIN Prototypes */
void CAN_cmd_chassis(int16_t motor1, int16_t motor2, int16_t motor3, int16_t motor4);
void can_filter_init(void);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __CAN_H__ */

