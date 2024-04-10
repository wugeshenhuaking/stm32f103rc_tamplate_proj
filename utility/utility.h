#ifndef __UTILITY_H__
#define __UTILITY_H__

#include "stdint.h"


//------------------------------------------------------------------------------
#define PI 3.1415926535
//------------------------------------------------------------------------------
//	typedef struct{
//		unsigned int size;
//		unsigned int used_size;
//		unsigned char buf[DATA_POOL_SIZE];
//	}DATA_POOL_T;

//#ifdef UTILITY_MAIN		
//	DATA_POOL_T g_data_pool={DATA_POOL_SIZE};
//	volatile unsigned long cnt_1ms __attribute__((section(".ARM.__at_0x20000000")));
//	volatile unsigned long cnt_1ms_H __attribute__((section(".ARM.__at_0x20000004")));
//	unsigned long delay_k __attribute__((section(".ARM.__at_0x20000008")));
//	DATA_POOL_T *g_p_data_pool __attribute__((section(".ARM.__at_0x2000000c")))=&g_data_pool;
//	unsigned long g_rnd0;
//	unsigned char reserved[12] __attribute__((section(".ARM.__at_0x20000014")));
//#else
//	extern DATA_POOL_T g_data_pool;
//	extern volatile unsigned long cnt_1ms;
//	extern volatile unsigned long cnt_1ms_H;
//	extern unsigned long delay_k;
//	extern DATA_POOL_T *g_p_data_pool;
//	extern unsigned long g_rnd0;
//	extern unsigned char reserved[];
//#endif

	

//------------------------------------------------------------------------------
#define HWREG(x)                                                              \
        (*((volatile unsigned long *)(x)))
#define HWREGH(x)                                                             \
        (*((volatile unsigned short *)(x)))
#define HWREGB(x)                                                             \
        (*((volatile unsigned char *)(x)))
#define HWREGBITW(x, b)                                                       \
        HWREG(((unsigned long)(x) & 0xF0000000) | 0x02000000 |                \
              (((unsigned long)(x) & 0x000FFFFF) << 5) | ((b) << 2))
#define HWREGBITH(x, b)                                                       \
        HWREGH(((unsigned long)(x) & 0xF0000000) | 0x02000000 |               \
               (((unsigned long)(x) & 0x000FFFFF) << 5) | ((b) << 2))
#define HWREGBITB(x, b)                                                       \
        HWREGB(((unsigned long)(x) & 0xF0000000) | 0x02000000 |               \
               (((unsigned long)(x) & 0x000FFFFF) << 5) | ((b) << 2))

#define REG_BIT(x,b)\
		(((unsigned long)(x) & 0xF0000000) | 0x02000000 |                \
        (((unsigned long)(x) & 0x000FFFFF) << 5) | ((b) << 2))

typedef volatile unsigned long  BITBAND_T;
//------------------------------------------------------------------------------
#define TstB(A,B)	((A & (1<<B))!=0)

#define SetGB(A) GPIO_SetBits(A)
#define ClrGB(A) GPIO_ResetBits(A)
#define TogGB(A) GPIO_WriteBit(A, (BitAction)(1 - GPIO_ReadInputDataBit(A)))
#define RdGB(A) GPIO_ReadInputDataBit(A)
#define WrGB(A,B) GPIO_WriteBit(A, B)
		
typedef void (*GpioOut_T)(unsigned char pinsta);
//------------------------------------------------------------------------------
//两个字节合成一个整数
extern unsigned short char_hl_short(unsigned char hi,unsigned lo);
//------------------------------------------------------------------------------
//交换一个字的高、低字节
//extern unsigned short short_xch_hl(unsigned short i);		//改汇编快速处理
//------------------------------------------------------------------------------

//从源缓冲区拷贝n个short到目的缓冲区,交换高低字节
void short_copy_xch(void *t,void *s,int n,unsigned char b_xch);
//------------------------------------------------------------------------------
//short写入缓冲区
extern unsigned char * short_wr_buf(unsigned char *buf,unsigned short s);
extern unsigned short short_rd_buf(unsigned char *buf);
//------------------------------------------------------------------------------
//short交换高低字节后写入缓冲区
extern unsigned char * short_wr_buf_xch(unsigned char *buf,unsigned short s);
//缓冲区交换高低字节读入short
extern unsigned short short_rd_buf_xch(unsigned char *buf);
//------------------------------------------------------------------------------
//IAP 跳转
typedef  void (*Function_T)(void);
extern void jump_to_app(unsigned int ApplicationAddress);
#define m_jump_to_app_disallint(A) {\
	__disable_irq();	\
	NVIC->ICER[0]=0xffffffff;	\
	NVIC->ICER[1]=0xffffffff;	\
	NVIC->ICER[2]=0xffffffff;	\
	jump_to_app(A);\
}
//------------------------------------------------------------------------------
extern unsigned long delay_k;									//延时系数
extern void delay_us_set_k(unsigned long us);								//计算延时系数delay_k，并且延时us数
extern void delay_us(unsigned long us);							//通过死循环办法延时us数
extern unsigned long * calc_bitadr(void *x,unsigned char b);	//计算位地址

extern void bitband_set(void *p,unsigned char b);	//位地址置位
extern void bitband_clr(void *p,unsigned char b);	//位地址复位
extern void bitband_toggle(void *p,unsigned char b);	//位地址翻转
extern unsigned char bitband_tsc(void *p,unsigned char b);	//测试并清零位

//------------------------------------------------------------------------------
//取HR的高，低字节
#define HRL(x) (x & 0xff)
#define HRH(x) (x >> 8)
//------------------------------------------------------------------------------
#define countof(A) (sizeof(A)/(sizeof(*A)))
#define LastMember(A)	A[countof(A)-1]
#define BufEnd(A)	A[sizeof(A)-1]
#define Bit2int(A)	(1 << A)
//==============================================================================
//-------------------- STM32F103_HW_ASM.S ----------------------
extern void _U32_SetB(unsigned long *x,unsigned char b);
extern void _U16_SetB(unsigned short *x,unsigned char b);
extern void _U8_SetB(unsigned char *x,unsigned char b);
extern void _U32_ClrB(unsigned long *x,unsigned char b);
extern void _U16_ClrB(unsigned short *x,unsigned char b);
extern void _U8_ClrB(unsigned char *x,unsigned char b);
extern void _U32_TogB(unsigned long *x,unsigned char b);
extern void _U16_TogB(unsigned short *x,unsigned char b);
extern void _U8_TogB(unsigned char *x,unsigned char b);
extern unsigned char _U32_TscB(unsigned long *x,unsigned char b);
extern unsigned char _U16_TscB(unsigned short *x,unsigned char b);
extern unsigned char _U8_TscB(unsigned char *x,unsigned char b);
//--------------------------------------------------------------
extern unsigned short _short_xch_hl(unsigned short i);
//extern unsigned char tst_bit(void *x,unsigned char b);
//==============================================================================

#ifdef MCU_CORE_M0
	#define u32_setb	_U32_SetB
	#define u16_setb	_U16_SetB
	#define u8_setb		_U8_SetB
	
	#define u32_clrb	_U32_ClrB
	#define u16_clrb	_U16_ClrB
	#define u8_clrb		_U8_ClrB
	
	#define u32_togb	_U32_TogB
	#define u16_togb	_U16_TogB
	#define u8_tog		_U8_TogB
	
	#define u32_tscb	_U32_TscB
	#define u16_tscb	_U16_TscB
	#define u8_tscb		_U8_TscB
#else
	#define u32_setb	bitband_set
	#define u16_setb	bitband_set
	#define u8_setb		bitband_set
	
	#define u32_clrb	bitband_clr
	#define u16_clrb	bitband_clr
	#define u8_clrb		bitband_clr
	
	#define u32_togb	bitband_toggle
	#define u16_togb	bitband_toggle
	#define u8_togb		bitband_toggle

	#define u32_tscb	bitband_tsc
	#define u16_tscb	bitband_tsc
	#define u8_tscb		bitband_tsc
#endif
//-----------------------------------------------------------------------------------
//时间轴计时器，BIT31=1表示正在有效运行，=0表示运行结束,有效比较位0-30
#define TIMS_MS_RUN	0x80000000
typedef unsigned long time_ms_T;
extern void left_ms_set(time_ms_T *p,time_ms_T val);	//设置延时比较点
extern long left_ms(time_ms_T *p);		//计算剩下的ms数，第一次到延时点，返回0，过延时点再次查询返回-1
long left_ms(time_ms_T *p);				//延时到返回0，不到返回剩下的ms数
long left_ms_sta(time_ms_T *p);			//延时刚到第一次调用返回0，以后返回-1，延时不到返回剩下的ms数
//-----------------------------------------------------------------------------------
#define GET_JSON_1FS_FAIL	0
extern int get_json_1fs(char *buf,int buf_size,char *s,char *name);
#define STR_TO_HEX_FAIL 0
#define STR_TO_HEX_SUCCESS 1
//-----------------------------------------------------------------------------------
//字符串转换为16进制数组
//buf:十六进制数组指针
//buf_size:数组大小
//s：字符串指针
extern int str_to_hex(unsigned char *buf,unsigned int buf_size,char *s);
//-----------------------------------------------------------------------------------
//固定字符串个数转换为16进制数组
//buf:十六进制数组指针
//s：字符串指针
//n:字符串长度，必须为偶数
int nstr_to_hex(unsigned char *buf,char *s,unsigned int n);
//-----------------------------------------------------------------------------------
extern int hexchar_btye(unsigned char ch);
//-----------------------------------------------------------------------------------
//HEX数组转换为字符串
//str_buf：字符串指针
//hex_buf:十六进制数组指针
//hex_n：十六进制数组大小
extern void hex_to_str(char *str_buf,unsigned char *hex_buf,unsigned int hex_n);
//-----------------------------------------------------------------------------------
extern void str2lwr(char *p);	//字符串转换为小写
extern void str2upr(char *p);	//字符串转换为大写
//-----------------------------------------------------------------------------------
	typedef struct {
		unsigned short year;	//1970-9999
		unsigned char month;	//1-12
		unsigned char day;		//1-31
		unsigned char hour;		//0-23
		unsigned char min;		//0-59
		unsigned char sec;		//0-59
		unsigned char week;		//1-7
		unsigned long sec1970;	//从1970年以来的秒数
	}CALENDAR_T;
	
	//#define TIME_DATE_CTRL_NEW 0x01
	//#define TIME_DATE_CTRL_SET 0x02
	
	#define CALENDAR_SUCCESS			0
	#define CALENDAR_FAIL				-1
extern int calendar_int(CALENDAR_T *p);
extern void int_calendar(CALENDAR_T *p);
//-----------------------------------------------------------------------------------
extern int Dword2Str(char *s,unsigned long data,unsigned char i_nb,unsigned char dec_nb,unsigned char b_sign,unsigned char b_inv0);
extern void Short_BinStr(char *buf,unsigned short us);	
//-----------------------------------------------------------------------------------
extern unsigned char * DataPool_Get(unsigned int size);		
//-----------------------------------------------------------------------------------
//ASC码转换成整型，转换失败，输出dft
extern int asc2int_dft(char *p,int dft);
extern int digchar_btye(unsigned char ch);

//ASC码转换成64位整型，转换失败，输出dft
extern int64_t asc2s64_dft(char *p,int64_t dft);

#define ASC2INT_SUCCESS 1
#define ASC2INT_FAIL 0
//ASC码转换成整型，转换成功，输出数值，resault=1;转换失败，输出0，resault=0
//extern int asc2int(int *resault,char *p);
extern int asc2int(char *p,int *resault);

//ASC码转换成64位整型，转换成功，输出数值，resault=1;转换失败，输出0，resault=0
extern  int asc2s64(int64_t *resault,char *p);

//-----------------------------------------------------------------------------------
//函数传递表格式
	typedef struct{
		char *func_name;
		unsigned int func_adr;
	}FUNC_TB_T;
//从函数传递表里面搜索名字匹配的函数指针
extern unsigned int Get_Func(FUNC_TB_T *func_tb,const char *func_name);
//-----------------------------------------------------------------------------------
#define TST_BIT(A,bit) ((A & (1<<bit)) != 0)
#define U8_TstB(A,bit) ((A & (1<<bit)) != 0)
//-----------------------------------------------------------------------------------


typedef struct{
	unsigned char *buf;
	unsigned short n;
	unsigned short size;
}COMM_BUF_T;
//从通讯缓冲区里面删除n的字节，并把后面的字节移到前面，返回剩下的字节数
int comm_buf_del_n(COMM_BUF_T *p,unsigned short n);
//从通讯缓冲区里面删除全部内容
void comm_buf_del_all(COMM_BUF_T *p);

//产生随机数
unsigned int MyRnd(void);

	
#endif
