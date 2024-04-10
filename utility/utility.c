/************************************Copyright (c)**************************************
                                          

--------------文件信息------------------------------------------------------------------
文 件 名: utility.c
创 建 人: Zhoucongwen
email:	  mcuast@qq.com
创建日期: 2019年04月15日
描    述: 各种工具函数
---------- 版本信息---------------------------------------------------------------------
 版    本: V1.0
 说    明: 
----------------------------------------------------------------------------------------
Copyright(C) C.C. 2019/04/15
All rights reserved
****************************************************************************************/ 
#include "utility.h"
#include "string.h"


//------------------------------------------------------------------------------
//两个字节合成一个整数
unsigned short char_hl_short(unsigned char hi,unsigned lo)
{
	union{
	unsigned char ch[2];
	unsigned short s;
	}u;
	u.ch[0]=lo;
	u.ch[1]=hi;
	return(u.s);
}
//------------------------------------------------------------------------------
//交换一个字的高、低字节
/*
unsigned short short_xch_hl(unsigned short i)
{
	union{
	unsigned char ch[2];
	unsigned short s;
	}u;
	u.ch[0]=(i>>8) & 0xff;
	u.ch[1]=i & 0xff;
	return(u.s);
}
*/
//------------------------------------------------------------------------------
//从源缓冲区拷贝n个short到目的缓冲区，b_xch=1,交换高低字节
void short_copy_xch(void *t,void *s,int n,unsigned char b_xch)
{
	int i;
	unsigned char *pt,*ps0;
	unsigned char ch;
	
	pt=(unsigned char *)t;
	ps0=(unsigned char *)s;
		
	if(b_xch)
	{
		for(i=0;i<n;i++)
		{
			ch=*ps0++;
			*pt++=*ps0++;
			*pt++=ch;
		}
	}
	else
	{
		n*=2;
		for(i=0;i<n;i++)
		{
			*pt++=*ps0++;
		}
	}
	
}
//------------------------------------------------------------------------------
//short写入缓冲区
unsigned char * short_wr_buf(unsigned char *buf,unsigned short s)
{
	*buf++ = s;
	*buf++ = s>>8;
	return(buf);
}
//缓冲区读入short
unsigned short short_rd_buf(unsigned char *buf)
{
	return((unsigned short)(*buf) + ((unsigned short)*(buf+1)<<8));
}
//------------------------------------------------------------------------------
//short交换高低字节后写入缓冲区
unsigned char * short_wr_buf_xch(unsigned char *buf,unsigned short s)
{
	*buf++ = s>>8;
	*buf++ = s;
	return(buf);
}
//缓冲区交换高低字节读入short
unsigned short short_rd_buf_xch(unsigned char *buf)
{
	return(((unsigned short)(*buf)<<8) + (unsigned short)*(buf+1));
}
//------------------------------------------------------------------------------

void jump_to_app(unsigned int ApplicationAddress)
{
	Function_T Jump_To_Application;
	
	Jump_To_Application = (Function_T)(*(volatile unsigned int*)(ApplicationAddress + 4));
	__asm("MSR MSP, *(volatile unsigned int*) ApplicationAddress");		//ARM堆栈在复位地址
	
	Jump_To_Application();
}

//------------------------------------------------------------------------------


//计算位地址
unsigned long * calc_bitadr(void *x,unsigned char b)
{
	unsigned long y;

	y=((unsigned long)x) & 0xf0000000;
	y |= 0x02000000;
	y |= ((unsigned long)x & 0x000FFFFF) << 5;
	y |= b <<2;
	return((unsigned long *)y);
}

//位地址置位
void bitband_set(void *p,unsigned char b)
{
	unsigned long *bitband;
	bitband=calc_bitadr(p,b);
	*bitband=1;
}
//位地址复位
void bitband_clr(void *p,unsigned char b)
{
	unsigned long *bitband;
	bitband=calc_bitadr(p,b);
	*bitband=0;
}
//位地址翻转
void bitband_toggle(void *p,unsigned char b)
{
	unsigned long *bitband;
	bitband=calc_bitadr(p,b);
	if(*bitband)
	{
		*bitband=0;
	}
	else
	{
		*bitband=1;
	}
}

//测试并清零位
unsigned char bitband_tsc(void *p,unsigned char b)
{
	unsigned long *bitband;
	bitband=calc_bitadr(p,b);
	if(*bitband)
	{
		*bitband=0;
		return(1);
	}
	else
	{
		return(0);
	}
}
//---------------------------------------------------------

//void delay_us_set_k(unsigned long us)
//{
//	uint32_t i;
//	
//	i=SYS_FREQ;
//	delay_k=i/3000000;
//	delay_us(us);
//}

//void delay_us(unsigned long us)
//{
//	unsigned long i;
//	us=us*delay_k;

//	if(us>3)
//	{
//		us-=3;
//	}
//	for(i=0;i<us;i++)	//每个循环3个周期
//	{
//		;
//	}
//}
//---------------------------------------------------------
//设定延时后的时间参考点
//void left_ms_set(time_ms_T *p,time_ms_T val)
//{
//	*p = (cnt_1ms+val) | TIMS_MS_RUN;		//设置时间轴上的比较点，并且设置运行标志
//}

//long left_ms_sta(time_ms_T *p)
//{
//	long r=0;
//	
//	if(*p & TIMS_MS_RUN)
//	{										//处于运行阶段
//		r=(*p-cnt_1ms) & (~TIMS_MS_RUN);			//获取比较点与当前时间计时的差
//		
//		if(r & 0x40000000)					//如果为负，说明已经超过比较点，延时结束
//		{
//			*p=0;							//清零运行标志
//			r=0;							//清零返回值
//		}
//		//时间没到，返回剩下的ms数
//	}
//	else
//	{
//		r=-1;
//	}
//	return(r);								
//}

//long left_ms(time_ms_T *p)
//{
//	long r=0;
//	
//	if(*p & TIMS_MS_RUN)
//	{										//处于运行阶段
//		r=(*p-cnt_1ms) & (~TIMS_MS_RUN);			//获取比较点与当前时间计时的差
//		
//		if(r & 0x40000000)					//如果为负，说明已经超过比较点，延时结束
//		{
//			*p=0;							//清零运行标志
//			r=0;							//清零返回值
//		}
//		//时间没到，返回剩下的ms数
//	}
//	
//	return(r);	
//}

//-----------------------------------------------------------------------------------
//在json格式字符串里面查找格式为"name":str2，或"str1":"str2"并把str2拷贝到buf
//返会：>0成功,=0不成功
int get_json_1fs(char *buf,int buf_size,char *s,char *name)
{
	char *p0,*p1,*pe;
	int n;
	//-----------------------------------------------------------
	//判断字符串的前后是不是{}
	n=strlen(s);				//求字符串长度
	if(n<7)return(GET_JSON_1FS_FAIL);			//{"A":1} 一个json最少7个字符
	if(*s != '{')return(GET_JSON_1FS_FAIL);	//第一个字符不是'{'
	pe=s+n-1;					//指向最后一个字符
	if(*pe!='}')return(GET_JSON_1FS_FAIL);		//最后一个字符不是'}'
	//-----------------------------------------------------------
	p0=strstr(s,name);			//在字符串里查字段名
	if(p0==NULL)return(GET_JSON_1FS_FAIL);		//没找到name
	if(*(p0-1)!='"')return(GET_JSON_1FS_FAIL);	//没找到name前面的'"'
	
	n=strlen(name);		//name的长度
	
	p0+=n;				//指向name的"
	
	if(*p0 != '"')return(GET_JSON_1FS_FAIL);	//没找到"
	
	p0++;				//指向':'
	if(*p0 != ':')return(GET_JSON_1FS_FAIL);	//没找到':'
	
	p0++;	//跳过':'
	
	while(*p0==' ')
	{
		if(*p0==0)
		{
			return(GET_JSON_1FS_FAIL);
		}
		p0++;			//跳过':'之后的空格
	}
	
	if(*p0=='"')
	{				//字符串内容
		p0++;		//跳过'"'
		p1=strstr(p0,"\"");	//找下一个'"'
		if(p1==NULL)return(GET_JSON_1FS_FAIL);	//找不到
		n=p1-p0;		//记录字符串长度
		
		p1++;		//指向字段分隔符或结束符
		if((*p1 !=',') && (*p1 != '}'))return(GET_JSON_1FS_FAIL);	//没找到分隔符与结束符
	}
	else
	{				//数字内容
		p1=strstr(p0,",");
		if(p1==NULL)	//没有找到字段分隔符
		{
			p1=strstr(p0,"}");
			if(p1==NULL)return(GET_JSON_1FS_FAIL);	//没有找到终止符
			if(*p1=='}')				//找到终止符
			{
				if(p1!=pe)return(GET_JSON_1FS_FAIL);	//终止符位置不正确
			}
		}
		n=p1-p0;
	}
	
	
	if(n>=buf_size)
	{
		return(GET_JSON_1FS_FAIL);	//字符串太长
	}
	
	strncpy(buf,p0,n);
	buf[n]=0;
	return(n);
}
//-----------------------------------------------------------------------------------
int hexchar_btye(unsigned char ch)
{
	if(ch >='0' && ch<='9')
	{
		ch-='0';
	}
	else if(ch >= 'a' && ch <= 'f') 
	{
		ch-=('a'-10);
	}
	else if(ch >= 'A' && ch <= 'F')
	{
		ch-=('A'-10);
	}
	else
	{
		return(-1);
	}
	return(ch);
}
//--------------------------------------------------------------
//字符串转换为16进制数组
//buf:十六进制数组指针
//buf_size:数组大小
//s：字符串指针
int str_to_hex(unsigned char *buf,unsigned int buf_size,char *s)
{
	int i,n,j;
	unsigned char ch;
	
	n=strlen(s);
	if(n & 0x01)
	{
		return(STR_TO_HEX_FAIL);
	}
	
	n/=2;
	
	if(n>buf_size)
	{
		return(STR_TO_HEX_FAIL);
	}
	
	for(i=0;i<n;i++)
	{
		j=hexchar_btye(*s++);
		if(j<0)
		{
			return(STR_TO_HEX_FAIL);
		}
		ch=j << 4;
		j=hexchar_btye(*s++);
		if(j<0)
		{
			return(STR_TO_HEX_FAIL);
		}
		ch |= j;
		*buf++ = ch;
	}
		
	return(n);
}
//--------------------------------------------------------------
//固定字符串个数转换为16进制数组
//buf:十六进制数组指针
//s：字符串指针
//n:字符串长度，必须为偶数
int nstr_to_hex(unsigned char *buf,char *s,unsigned int n)
{
	int i,j;
	unsigned char ch;
	
	if(n & 0x01)
	{
		return(STR_TO_HEX_FAIL);
	}
	
	n/=2;
	
	
	for(i=0;i<n;i++)
	{
		j=hexchar_btye(*s++);
		if(j<0)
		{
			return(STR_TO_HEX_FAIL);
		}
		ch=j << 4;
		j=hexchar_btye(*s++);
		if(j<0)
		{
			return(STR_TO_HEX_FAIL);
		}
		ch |= j;
		*buf++ = ch;
	}
		
	return(n);
}
//----------------------------------------------------------------------
//HEX数组转换为字符串
//str_buf：字符串指针
//hex_buf:十六进制数组指针
//hex_n：十六进制数组大小
void hex_to_str(char *str_buf,unsigned char *hex_buf,unsigned int hex_n)
{
	int i;
	unsigned char ch,ch1;
	for(i=0;i<hex_n;i++)
	{
		ch1=*hex_buf++;
		ch =ch1>>4;
		if(ch<10)
		{
			ch+='0';
		}
		else
		{
			ch+=('A'-10);
		}
			
		*str_buf++ = ch;
		
		ch = ch1 & 0x0f;
		if(ch<10)
		{
			ch+='0';
		}
		else
		{
			ch+=('A'-10);
		}
			
		*str_buf++ = ch;
	}
}
//-------------------------------------------------------------------------
const unsigned char tb_month_days[]={
	0,
	31,		//1
	28,		//2
	31,		//3
	30,		//4
	31,		//5
	30,		//6
	31,		//7
	31,		//8
	30,		//9
	31,		//10
	30,		//11
	31};	//12
#define TIME_DATA_YEAR_ORG 1970
#define SECONDS_DAY (3600*24)
#define SECONDS_YEAR (3600*24*365)
#define DAYS_YEAR 365

int calendar_int(CALENDAR_T *p)
{
	unsigned int i,j,k;
	unsigned char b_leap;
	unsigned int days;
	
	
	i=p->year;
	if(i < TIME_DATA_YEAR_ORG)
	{
		return(CALENDAR_FAIL);
	}
	
	b_leap=(((i%400)==0) || ((i%4==0) && (i%100!=0)));	//求出今年是否闰年
	
	j=(i-TIME_DATA_YEAR_ORG);	//已经过去的年数
	days=DAYS_YEAR*j;			//已经过去的天数
	j/=4;	  					//已经过去的闰年数，2000年刚好是闰年
	days += j;					//已经过去的天数
	
	i=p->month;
	
	if(i<1 || i>12)
	{
		return(CALENDAR_FAIL);
	}
	
	k=0;
	for(j=1;j<i;j++)
	{
		k += (unsigned int)tb_month_days[j];
	}
	
	if(i >= 3 )
	{
		k+=b_leap;		//大于等于3月
	}
	days += k;			//已经过去的天数
	
	
	i=p->day;
	if(i<1 || i>((unsigned int)tb_month_days[p->month]+b_leap))
	{
		return(CALENDAR_FAIL);
	}
	
	days += (i-1);		//已经过去的天数
	k = days * 24;		//已经过去的小时
	
	i = p->hour;
	if(i>23)
	{
		return(CALENDAR_FAIL);
	}
	
	k += i;
	k *= 60;			//已经过去的分钟
	
	i = p->min;
	if(i>59)
	{
		return(CALENDAR_FAIL);
	}
	
	k += i;
	k *= 60;			//已经过去的秒
	
	i = p->sec;
	if(i>59)
	{
		return(CALENDAR_FAIL);
	}
	
	k += i;				//已经过去的秒
	
	p->sec1970 = k;

	return(CALENDAR_SUCCESS);
}

void int_calendar(CALENDAR_T *p)
{
	unsigned int i,j,k;
	unsigned int days;
	unsigned char b_leap;
	
	i=p->sec1970;
	
	days = i/SECONDS_DAY;		//离1970.1.1一共多少天
	
	p->week=((days+3) % 7)+1;
	
	j=days/365;					//j=离1970年
	
	if((365*j + j/4) > days)	//年数*365+中间的闰年
	{
		j--;					//比天数多，减1年
	}
	k=1970+j;
	p->year=k;					//确定年份
	
	b_leap=(((k%400)==0) || ((k%4==0) && (k%100!=0)));	//求出今年是否闰年
	
	days -= (j*365 + j/4);		//剩下的天数
	
	k=0;
	for(i=1;i<=12;i++)
	{
		j= k + (unsigned int)tb_month_days[i];
		if(b_leap && i==2)
		{
			j++;
		}
		if(j > days)
		{
			break;
		}
		k=j;
	}
	p->month = i;		//确定月份

	p->day=days-k+1;	//确定日
	
	i=(p->sec1970) % SECONDS_DAY;
	
	p->hour = i / 3600;
	
	i %=3600;
	
	p->min = i/60;
	
	p->sec = i%60;
}
//-------------------------------------------------------------------------
//ch:字符串指针，dada：数据，i_nb：整数位数，dec_nb:小数位数，b_sign：有符号数,b_inv0:显示无效零
int Dword2Str(char *s,unsigned long data,unsigned char i_nb,unsigned char dec_nb,unsigned char b_sign,unsigned char b_inv0)
{
	int i,j,char_nb;
	//char ch[16];
	char *p;
	unsigned char b_s;

	if(!i_nb)i_nb++;	
	char_nb=i_nb;	//整数位数
	if(dec_nb)
	{
		char_nb += 1+dec_nb;	//小数位数+小数点位
	}

	if(b_sign)
	{
		if((long)data<0)
		{
			data=0-data;
			b_s=1;
		}
		else
		{
			b_s=0;
		}
	}

	p=s+char_nb+b_sign;	//（符号位）
	//p=s+char_nb;	//指向结束符
	*p--=0;				//结束符

	for(i=0;i<char_nb;i++)
	{
		if(i!=0 && i==dec_nb)
		{
			*p--='.';
		}
		else
		{
			j=data%10;
			data/=10;
			*p--=j+'0';
		}
	}
	if(b_sign)
	{
		*p = ' ';	//符号位置占空格
	}
	
	
	p++;
	if(!b_inv0 && i_nb)
	{		   	//无效零不显示
		for(i=0;i<i_nb-1;i++)
		{
			if(*p=='0')
			{
				*p=' ';
			}
			else
			{
				break;
			}
			p++;
		}
	}
	
	
	if(b_sign)
	{
		p--;
		if(b_s)
		{
			*p='-';
		}
		else
		{
			*p=' ';
		}
	}

	//strcpy(s,p);

	return(char_nb+b_sign);
}


//=========================================================================================
//16位数按照二进制排序转换成字符串
void Short_BinStr(char *buf,unsigned short us)
{
	int i,j;
	
	j=0x8000;
	for(i=0;i<16;i++)
	{
		if(us & j)
		{
			*buf='1';
		}
		else
		{
			*buf='0';
		}
		buf++;
		j>>=1;
	}
	*buf=0;		//字符串结尾
}
//=========================================================================================
void str2lwr(char *p)
{
	while(1)
	{
		if(*p==0)
		{
			break;
		}
		if(*p>='A' && *p<='Z')
		{
			*p-=('A'-'a');
		}
		p++;
	}
}

void str2upr(char *p)
{
	while(1)
	{
		if(*p==0)
		{
			break;
		}
		if(*p>='a' && *p<='z')
		{
			*p+=('A'-'a');
		}
		p++;
	}
}
//=========================================================================================
////从数据池里申请空间，成功返回指针
//unsigned char * DataPool_Get(unsigned int size)
//{
//	unsigned char *r=NULL;
//	
//	if(size > (g_p_data_pool->size-g_p_data_pool->used_size))
//	{
//		//g_p_data_pool->used_size=0xffffffff;
//		while(1);
//	}
//	r=g_p_data_pool->buf + g_p_data_pool->used_size;
//	g_p_data_pool->used_size += size;
//	return(r);
//}
//=========================================================================================
//从函数传递表里面搜索名字匹配的函数指针
unsigned int Get_Func(FUNC_TB_T *func_tb,const char *func_name)
{
	while(func_tb->func_adr !=0)
	{
		if(strcmp(func_tb->func_name,func_name)==0)
		{
			return(func_tb->func_adr);
		}
		func_tb++;
	}
	return(0);
}
//=========================================================================================
int digchar_btye(unsigned char ch)
{
	if(ch >='0' && ch<='9')
	{
		ch-='0';
	}
	else
	{
		return(-1);
	}
	return(ch);
}

int asc2int_dft(char *p,int dft)
{
	unsigned char ch,b_neg=0;
	int i,j;
	unsigned int r;
	r=0;
	
	if(*p=='-')
	{
		p++;
		b_neg=1;
	}
	for(i=0;i<10;i++)
	{
		ch=*p++;
		if(ch==0)
		{
			break;
		}
		j=digchar_btye(ch);
		if(j<0)
		{
			return(dft);	//非法字符返回失败
		}
		r=r*10+j;		//合法字符
	}
	if(r>=0x80000000)
	{
		return(0);		//超出整型表达范围
	}
	if(b_neg)
	{
		r=-r;		//负数
	}
	
	return(r);
}

int64_t asc2s64_dft(char *p,int64_t dft)
{
	unsigned char ch,b_neg=0;
	int i,j;
	uint64_t r;
	r=0;
	
	if(*p=='-')
	{
		p++;
		b_neg=1;
	}
	for(i=0;i<19;i++)
	{
		ch=*p++;
		if(ch==0)
		{
			break;
		}
		j=digchar_btye(ch);
		if(j<0)
		{
			return(dft);	//非法字符返回失败
		}
		r=r*10+j;		//合法字符
	}
	if(r>=0x8000000000000000)
	{
		return(0);		//超出整型表达范围
	}
	if(b_neg)
	{
		r=-r;		//负数
	}
	
	return(r);
}
//==============================================================================
//ASC码转换成int型，成功返回1，失败返回0
int asc2int(char *p,int *resault)
{
	unsigned char ch,b_neg=0;
	int i,j;
	unsigned int r=0;
	
	if(*p=='-')
	{
		p++;
		b_neg=1;
	}
	for(i=0;i<10;i++)
	{
		ch=*p++;
		if(ch==0)
		{
			break;	//遇到字符串结束符
		}
		j=digchar_btye(ch);	//数字字符转换为数值
		if(j<0)				//转换失败
		{
			*resault=ASC2INT_FAIL;
			return(r);	//非法字符返回失败
		}
		r=r*10+j;		//合法字符
	}
	if(r>=0x80000000)
	{
		*resault=ASC2INT_FAIL;
		return(0);		//超出整型表达范围
	}
	if(b_neg)
	{
		r=-r;		//负数
	}
	*resault=ASC2INT_SUCCESS;		//转换成功
	return(r);
}
//-----------------------------------------------------------------------------
//字符串转换64位整型
int asc2s64(int64_t *resault,char *p)
{
	unsigned char ch,b_neg=0;
	int i,j;
	uint64_t r;
	r=0;
	
	if(*p=='-')
	{
		p++;
		b_neg=1;
	}
	for(i=0;i<19;i++)
	{
		ch=*p++;
		if(ch==0)
		{
			break;		//遇到字符串结束符
		}
		j=digchar_btye(ch);		//字符转换数值
		if(j<0)
		{
			*resault=0;		//非法字符
			return(ASC2INT_FAIL);	//非法字符返回失败
		}
		r=r*10+j;		//合法字符
	}
	if(r>=0x8000000000000000)
	{
		*resault=0;
		return(ASC2INT_FAIL);		//超出整型表达范围
	}
	if(b_neg)
	{
		r=-r;		//负数
	}
	*resault=r;
	return(ASC2INT_SUCCESS);
}


int comm_buf_del_n(COMM_BUF_T *p,unsigned short n)
{
	int i;
	
	if(n>=p->n)
	{
		p->n=0;
	}
	else
	{
		i=p->n-n;
		memcpy(p->buf,p->buf+n,i);
		p->n=i;
	}
	return(p->n);
}

void comm_buf_del_all(COMM_BUF_T *p)
{
	p->n=0;
}

//unsigned int MyRnd(void)
//{
//	g_rnd0 = (g_rnd0 + cnt_1ms) * 1103515245 + 12345;
//	return(g_rnd0);
//}
