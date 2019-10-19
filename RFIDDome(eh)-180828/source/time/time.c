/*********************************************************************************************
* �ļ���time.c
* ���ߣ�
* ˵���� 
* �޸ģ�
* ע�ͣ�
*********************************************************************************************/

/*********************************************************************************************
* ͷ�ļ�
*********************************************************************************************/
#include "time.h"
#include "led.h"
#include "eh.h"


/*********************************************************************************************
* ���ƣ�time1Int_init
* ���ܣ���ʱ��1�жϳ�ʼ��
* ������
* ���أ���
* �޸ģ�
* ע�ͣ�
*********************************************************************************************/
void time1Int_init(void)
{
    u16 t1Arr = 50000;
    
    T1CTL |= (1<<1);                                            //ģ������0--T1CC0
    T1CTL |= (1<<3);                                            //32��Ƶ
    
    T1CC0L = t1Arr&0xff;
    T1CC0H = (t1Arr>>8)&0xff;
    T1CCTL0 |= (1<<2);                                          //��ʱ����Ϊ�Ƚ�ģʽ

    //�����ж����ȼ����
    IP0 &= ~(1<<1);
    IP1 &= ~(1<<1);
    
    IEN1 |= 0X02;                                               //��ʱ��1�ж�ʹ��
    EA=1;                                                       //�����ж� 
}




#define INT_TIME 5

u8 t1Update=0;

/*********************************************************************************************
* ���ƣ�T1_ISR
* ���ܣ���ʱ��1�жϷ������
* ��������
* ���أ���
* �޸ģ�
* ע�ͣ�
*********************************************************************************************/
#pragma vector = T1_VECTOR      
__interrupt void T1_ISR(void)            
{  
    static u8 t1_count=0;
    
    if(t1_count>(INT_TIME-1))
    {
        t1_count = 0;
        t1Update = 1;
        LED1 = !LED1;
    }
    t1_count++;
    ledFlicker(2);
    
    T1IF=0; 
}