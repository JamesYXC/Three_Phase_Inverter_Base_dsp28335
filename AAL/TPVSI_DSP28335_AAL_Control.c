/*
 * TPVSI_DSP28335_AAL_Control.c
 *
 *  Created on: 2018��3��12��
 *      Author: Chuck
 */

#include "TPVSI_DSP28335_AAL_Control.h"


/*
 * FunName:AAL_Control_PID_DeInit
 * Description:��PID�ṹ���ʼ��Ϊȱʡֵ
 * Input:PID�ṹ��ָ��p
 * Output:None
 * Others:None
 * */
void AAL_Control_PID_DeInit(PID_Structure *p)
{
	p->Ts = 0;
	p->err = 0;
	p->err_last = 0;
	p->ki = 0;
	p->kp = 0;
	p->output = 0;
	p->output_last = 0;
}

/*
 * FunName:AAL_Control_PID_Init
 * Description:��PID�ṹ�尴�ո���������ʼ��
 * Input:PID�ṹ��ָ��p,����ʱ��Ts,����ϵ��kp,����ϵ��ki
 * Output:None
 * Others:None
 * */
void AAL_Control_PID_Init(PID_Structure *p,float Ts,float kp,float ki)
{
	CON_PID_DeInit(p);
	p->Ts = Ts;
	p->kp = kp;
	p->ki = ki;
}


/*
 * FunName:AAL_Control_PID
 * Description:��ѹ�ջ�pid����
 * Input:PID�ṹ��ָ��p,�������err
 * Output:None
 * Others:None
 * */
void AAL_Control_PID(PID_Structure *p,float err)
{
	//��������
	p->err_last = p->err;
	p->err = err;
	p->output_last = p->output;
	//����PID��ŷ������
	p->output = p->output_last + p->kp*(p->err - p->err_last) + p->ki*p->Ts*p->err;
	if(p->output>1)
		p->output = 0.99;
	else if(p->output<-1)
		p->output = -0.99;
}
