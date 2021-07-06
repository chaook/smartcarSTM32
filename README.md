# smartcar
一个手机遥控小车，两个驱动轮，一个万向轮。可以前进后退，左转右转，所有操作均可以自由控制速度。
使用STM32单片机驱动两个驱动轮，通过输出PWM波给驱动电机，调整两个轮子的速度差实现转向。
控制器用的是自己编写的Android APP，两个控制条分别控制小车前进后退、左右转向。
STM32与Android手机通过蓝牙进行通信。

技术栈：C语言、Android、PWM调速、蓝牙通信

小车效果图，因为小车自带的电池电压不够，所以暂时用充电宝代替。（很丑）
![d07e152fddce93a6664d2ec9f970702](https://user-images.githubusercontent.com/58350918/124575488-0705d380-de7e-11eb-9652-b1dbd7e36084.png)
控制APP效果图，左边控制前后，右边控制左右。
![Screenshot_20210706-170816_smartcar](https://user-images.githubusercontent.com/58350918/124575506-0a995a80-de7e-11eb-8395-e83687bd2e13.jpg)
