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
    USART_ITConfig(USART1,USART_IT_IDLE,ENABLE);   // �������ڿ����ж�
//    USART_ITConfig(USART1,USART_IT_TXE,ENABLE);    // �������ڽ����ж�

}

void usart_nvic_config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    //Usart1 NVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//�����ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
}


void usart_param_config(void)
{
    USART_InitTypeDef USART_InitStructure;
    // ���ô���������ز���
    USART_InitStructure.USART_BaudRate = 19200;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
    USART_Init(USART1, &USART_InitStructure); //��ʼ������1

}

void usart_gpio_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    //USART1_TX   GPIOA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
    GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9

    //USART1_RX	  GPIOA.10��ʼ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  
}

void usart_rcc_init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
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


