#ifndef __PID_H__
#define __PID_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

/* PID结构体定义 */
typedef struct {
    float kp;         
    float ki;         
    float kd;         
    
    float current_error;  // 当前误差
    float last_error;     // 上一次误差
    float prev_error;     // 上上次误差
    
    int16_t output_max;   // 最大输出限制
    int16_t output_min;   // 最小输出限制
    
    int16_t output;       // 本次输出
} pid_type_def;

void pid_init(pid_type_def *pid, float kp, float ki, float kd, 
              int16_t output_max, int16_t output_min);
int16_t pid_calculate(pid_type_def *pid, float target, float current);
void pid_reset(pid_type_def *pid);

#ifdef __cplusplus
}
#endif

#endif 
