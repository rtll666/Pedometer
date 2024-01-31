#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "string.h"		
#include "led.h"
#include "TIME.h"
#include "mpu6050.h"
#include "OLED.h"

float Pitch,Roll,Yaw,Step,AX,AY,AZ;
unsigned long step; 
int main(void)
 {	
	u8 string[10] = {0};	
	delay_init();
	uart_init(115200);

	OLED_Init();
	OLED_Refresh();
	
	IIC_Init();
	MPU6050_initialize();     //=====MPU6050初始化	
	DMP_Init();
		
	TIM2_Getsample_Int(1999,719);		//50ms任务定时中断

	while(1)
	{	
		delay_ms(999);
		AX = gyro[0]/2048;
		AY = gyro[1]/2048;
		AZ = gyro[2]/2048;
		if(AZ>3)
//	dmp_get_pedometer_step_count(&step);
		Step=Step+1;
		sprintf((char *)string,"Step  :%.2f",Step);//0300
		OLED_ShowString(16,0,string,16);
		sprintf((char *)string,"Pitch:%.2f",Pitch);//0300
		OLED_ShowString(16,16,string,16);
		sprintf((char *)string,"Roll :%.2f",Roll);//0300
		OLED_ShowString(16,32,string,16);
		sprintf((char *)string,"Yaw  :%.2f",Yaw);//0300
		OLED_ShowString(16,48,string,16);
		OLED_Refresh();

	}
}
