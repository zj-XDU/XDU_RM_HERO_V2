/**
  ****************************(C) COPYRIGHT 2019 DJI****************************
  * @file       shoot.c/h
  * @brief      射击功能。
  * @note       
  * @history
  *  Version    Date            Author          Modification
  *  V1.0.0     Dec-26-2018     RM              1. 完成
  *
  @verbatim
  ==============================================================================

  ==============================================================================
  @endverbatim
  ****************************(C) COPYRIGHT 2019 DJI****************************
  */

#ifndef SHOOT_H
#define SHOOT_H
#include "struct_typedef.h"

#include "bsp_can.h"
#include "gimbal_task.h"
#include "remote_control.h"
#include "user_lib.h"



//一发大弹丸的热量
#define SHOOT_HEAT_REMAIN_VALUE		100
//初始状态枪口热量上限
#define SHOOT_HEAT_LIMIT_INIT		100	

//爆发优先枪口热量上限
#define heat_first_SHOOT_HEAT_LIMIT_LEVEL_1  200
#define heat_first_SHOOT_HEAT_LIMIT_LEVEL_2	 350
#define heat_first_SHOOT_HEAT_LIMIT_LEVEL_3	 500
//射速优先枪口热量上限
#define speed_first_SHOOT_HEAT_LIMIT_LEVEL_1	100
#define speed_first_SHOOT_HEAT_LIMIT_LEVEL_2	200
#define speed_first_SHOOT_HEAT_LIMIT_LEVEL_3	300

#define trigle_pid_kp               1000.0f
#define trigle_pid_ki               100.0f
#define trigle_pid_kd               0.0f
#define trigle_pid_max              8000.0f
#define trigle_pid_maxi             3000.0f


#define trigle_pid_speed_kp               13.0f
#define trigle_pid_speed_ki               0.0f
#define trigle_pid_speed_kd               0.0f
#define trigle_pid_speed_max              15000.0f
#define trigle_pid_speed_maxi             500.0f


#define TRIGLE_ANGLE_ADD				  8

//射击发射开关通道数据
#define SHOOT_RC_MODE_CHANNEL       1
//云台模式使用的开关通道

#define SHOOT_CONTROL_TIME          GIMBAL_CONTROL_TIME

#define SHOOT_FRIC_PWM_ADD_VALUE    100.0f

//射击摩擦轮激光打开 关闭
#define SHOOT_ON_KEYBOARD           KEY_PRESSED_OFFSET_Q
#define SHOOT_OFF_KEYBOARD          KEY_PRESSED_OFFSET_E

//射击完成后 子弹弹出去后，判断时间，以防误触发
#define SHOOT_DONE_KEY_OFF_TIME     15
//鼠标长按判断
#define PRESS_LONG_TIME             5
#define KEY_UP_TIME					466//500
#define STOP_TIME					800
//遥控器射击开关打下档一段时间后 连续发射子弹 用于清单
#define RC_S_LONG_TIME              2000
//摩擦轮高速 加速 时间
#define UP_ADD_TIME                 100
//电机反馈码盘值范围
#define HALF_ECD_RANGE              4096
#define ECD_RANGE                   8191
//电机rmp 变化成 旋转速度的比例
#define MOTOR_RPM_TO_SPEED          0.00290888208665721596153948461415f
#define MOTOR_ECD_TO_ANGLE          0.000021305288720633905968306772076277f
#define FULL_COUNT                  18
//拨弹速度
#define TRIGGER_SPEED               -1300.0f
#define CONTINUE_TRIGGER_SPEED      15.0f
#define READY_TRIGGER_SPEED         5.0f

#define KEY_OFF_JUGUE_TIME          500
#define SWITCH_TRIGGER_ON           0
#define SWITCH_TRIGGER_OFF          1

//卡单时间 以及反转时间
#define BLOCK_TRIGGER_SPEED         20.0f
#define BLOCK_TIME                  700
#define REVERSE_TIME                130
#define REVERSE_SPEED_LIMIT         13.0f

#define PI_FOUR                     0.43//0.78539816339744830961566084581988f
#define PI_TEN                      0.314f

//拨弹轮电机PID
#define TRIGGER_ANGLE_PID_KP        800.0f
#define TRIGGER_ANGLE_PID_KI        0.5f
#define TRIGGER_ANGLE_PID_KD        0.0f

#define TRIGGER_BULLET_PID_MAX_OUT  10000.0f
#define TRIGGER_BULLET_PID_MAX_IOUT 9000.0f

#define TRIGGER_READY_PID_MAX_OUT   16000.0f
#define TRIGGER_READY_PID_MAX_IOUT  7000.0f


#define SHOOT_HEAT_REMAIN_VALUE     100
#define SHOOT_SPEED_SET				4600


//摩擦轮转速三级挡位
#define SHOOT_FRIC_SPEED_LOW		5000
#define SHOOT_FRIC_SPEED_MID		7000
#define	SHOOT_FRIC_SPEED_HIG		10000

typedef enum
{
    SHOOT_STOP = 0,
    SHOOT_READY_FRIC,       //摩擦轮开始转动
    //SHOOT_READY_BULLET,	//转速达到目标转速之后进入子弹预装载
    //SHOOT_READY,			//
    SHOOT_BULLET,
    //SHOOT_CONTINUE_BULLET,
    SHOOT_DONE,
} shoot_mode_e;

struct shoot_data
{
	float pit_set;
	float yaw_set;
	uint8_t shoot_en;

};


typedef struct
{
    shoot_mode_e shoot_mode;
    const RC_ctrl_t *shoot_rc;
	const motor_measure_t *trigle_motor_meaure;
    const motor_measure_t *shoot_motor_measure0;
	const motor_measure_t *shoot_motor_measure1;
	struct shoot_data my_shoot_data;			//自瞄数据结构体指针
    pid_type_def trigger_motor_pid;			//拨盘PID结构体
	pid_type_def trigger_motor_speed_pid;			//拨盘PID结构体
	
	pid_type_def fric_motor0_pid;			//摩擦轮0PID结构体
	pid_type_def fric_motor1_pid;			//摩擦轮1PID结构体
	
	
    fp32 trigger_speed_set;
    fp32 speed;
    fp32 speed_set;
    fp32 angle;
    fp32 set_angle;
    int16_t given_current;
    int8_t ecd_count;

    bool_t press_l;
    bool_t press_r;
    bool_t last_press_l;
    bool_t last_press_r;
    uint16_t press_l_time;
    uint16_t press_r_time;
    uint16_t rc_s_time;

    uint16_t block_time;
    uint16_t reverse_time;
    bool_t move_flag;

    bool_t key;
    uint8_t key_time;

    uint16_t heat_limit;
    uint16_t heat;
	
	int16_t fric0_speed_set;
	int16_t fric1_speed_set;
	
	uint8_t 	shoot_start_flag;		//发射使能标志位
	uint16_t 	shoot_key_up_count;		//发射按键抬起计数器，只有当计数器超过一定数值之后，发射使能标志位才会被置位
	
	int fric_flag;
	int16_t shoot_current[3];
} shoot_control_t;

//由于射击和云台使用同一个can的id故也射击任务在云台任务中执行
extern void shoot_init(void);
extern void shoot_task(void const *pvParameters);

extern shoot_control_t shoot_control;          //射击数据

#endif
