# Simple robot control software layer（简单机器人控制软件层）

一个硬件无关的函数库，旨在减少开发简单的轮式机器人时的重复性工作，可使你在完成硬件驱动后以极少的代码量跳过繁杂的功能开发，直接编写用户逻辑

本项目有良好的注释，亦可用于教学




**文件编码：GB2312**

## 头文件
| 文件名 | 功能 |
|-|-|
|srcsl.h        |头文件集合|
|srcslsys.h     |配置文件|

## 结构
| 模块 | 功能 | 依赖 |
|-|-|-|
|srcsl_beep         |蜂鸣器控制和蜂鸣器音乐 |srcsl_timer
|srcsl_chassis      |简单底盘控制           |srcsl_motor
|srcsl_datastruct   |向量和链表             |srcsl_memmang
|srcsl_encoder      |编码器                 |
|srcsl_filter       |常用滤波器             |
|srcsl_key          |按键                   |
|srcsl_log          |简易日志               |
|srcsl_memmang      |内存管理               |
|srcsl_menu         |简易菜单               |
|srcsl_motor        |电机和舵机控制          |srcsl_pid, srcsl_encoder
|srcsl_pid          |PID                    |
|srcsl_timer        |计时器和动作播放器      |



**注：**

* 所有函数均不保证线程安全性

* 动作播放器和蜂鸣器音乐功能依赖于定时器，请确保srcsl_timer_updata()函数1000Hz运行；

* datastruct默认采用memmang提供的替代方案进行动态内存分配，其余模块均静态分配内存

* srcsl_chassis、srcsl_motor、srcsl_encoder、srcsl_pid、srcsl_key模块仿真测试显著难于实机测试，故暂不进行测试，其余模块经过简单测试，可以使用。