#include "stm32f10x.h"

int main(void)
{
	uint8_t temp =0;
	
	NVIC_SetPriorityGrouping(3);
	
	while(1)
	{
	
		temp++;
	}
}


