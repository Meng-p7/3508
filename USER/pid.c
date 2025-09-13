#include "pid.h"

void pid_init(pid_type_def *pid, float kp, float ki, float kd, 
              int16_t output_max, int16_t output_min) {
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
    
    pid->current_error = 0.0f;
    pid->last_error = 0.0f;
    pid->prev_error = 0.0f;
    
    pid->output_max = output_max;
    pid->output_min = output_min;
    
    pid->output = 0;
}

int16_t pid_calculate(pid_type_def *pid, float target, float current) {
    float delta;  // 增量值
    float p_out, i_out, d_out;  // 比例、积分、微分输出
    
    // 计算当前误差
    pid->current_error = target - current;
    
    // 计算增量式PID的各部分
    p_out = pid->kp * (pid->current_error - pid->last_error);
    i_out = pid->ki * pid->current_error;
    d_out = pid->kd * (pid->current_error - 2 * pid->last_error + pid->prev_error);
    
    // 计算总增量
    delta = p_out + i_out + d_out;
    
    // 积分限幅处理
    if (i_out > 200.0f) {
        i_out = 200.0f;
    } else if (i_out < -200.0f) {
        i_out = -200.0f;
    }
	
//	//微分限幅处理
//	if (d_out > 500.0f) {
//      d_out = 500.0f;
//   } else if (d_out < -500.0f) {
//        d_out = -500.0f;
//    }
//	
    
    // 计算输出值
    pid->output += delta;
    
    // 输出限幅
    if (pid->output > pid->output_max) {
        pid->output = pid->output_max;
    } else if (pid->output < pid->output_min) {
        pid->output = pid->output_min;
    }
    
    // 更新误差历史
    pid->prev_error = pid->last_error;
    pid->last_error = pid->current_error;
    
    return pid->output;
}


void pid_reset(pid_type_def *pid) {
    pid->current_error = 0.0f;
    pid->last_error = 0.0f;
    pid->prev_error = 0.0f;
    pid->output = 0;
}
