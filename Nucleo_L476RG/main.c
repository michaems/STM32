#include "stm32L476xx.h"
#include "stm32L4xx_hal.h"
#include "stm32L4xx_hal_gpio.h"

#include <cmsis_os.h>
#include "Board_led.h"



osThreadId main_ID;
osThreadId led_ID1, led_ID2;

void led_thread1(void const *arg);
void led_thread2(void const *arg);

void led_switcher(void const *arg);


osThreadDef(led_switcher, osPriorityNormal, 2, 0);

int main(void)
{	
	LED_Initialize();
	
	led_ID1 = osThreadCreate(osThread(led_switcher), (void*) 0ul);
  led_ID2 = osThreadCreate(osThread(led_switcher), (void*) 2ul);
	os_idle_demon();
	
	while(1);
}


void led_switcher(void const *arg)
{
	for(;;){
		LED_On((uint32_t)arg);
		osDelay(500);
		LED_Off((uint32_t)arg);
		osDelay(500);
	}
}

