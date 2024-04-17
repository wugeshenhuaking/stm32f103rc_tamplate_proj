#include "drv_usart.h"

uint8_t rx_buf[USART_BUF_SIZE]={0};
uint8_t tx_buf[USART_BUF_SIZE]={0};


void usart_enable(void)
{


}

void usart_disable(void)
{


}

void user_usart_irq(void)
{


}

void usart_IT_config(void)
{
    USART_ITConfig(USART1,USART_IT_IDLE,ENABLE);   // 开启串口空闲中断
//    USART_ITConfig(USART1,USART_IT_TXE,ENABLE);    // 开启串口接受中断

}

void usart_nvic_config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    //Usart1 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//子优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
}


void usart_param_config(void)
{
    USART_InitTypeDef USART_InitStructure;
    // 配置串口外设相关参数
    USART_InitStructure.USART_BaudRate = 19200;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
    USART_Init(USART1, &USART_InitStructure); //初始化串口1

}

void usart_gpio_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    //USART1_TX   GPIOA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9

    //USART1_RX	  GPIOA.10初始化
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  
}

void usart_rcc_init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
}

void usart_msp_init(void)
{
    usart_rcc_init();
    usart_gpio_init();
    usart_param_config();
    usart_nvic_config();
    usart_IT_config();
}

void USART1_IRQHandler(void)
{
    user_usart_irq();
}


