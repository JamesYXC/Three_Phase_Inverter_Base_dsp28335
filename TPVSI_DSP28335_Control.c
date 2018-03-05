/*
 * TPVSI_DSP28335_Control.c
 *
 *  Created on: 2018��3��4��
 *      Author: chen318
 */
#include "TPVSI_DSP28335_Control.h"

/*ȫ�ֱ�������*/
ABC_DQ0_POS_F p_vol_dq0;
Sample_Stru p_vol_sam;

/*
 * FunName:CON_Sample_Init
 * Description:��ʼ�������ṹ�壬ϵ��k��������˲������ݵ���ʵ����ת����ϵ�����������ĳ�ʼ��Ӧ��������ݵĶ��ٶ���
 * Input:�����ṹ��ָ��p
 * Output:None
 * */
void CON_Sample_Init(Sample_Stru *p)
{
	Uint8 i;
	/*TODO:�����ﶨ�������ϵ��*/
	p->k[0] = 0.10355509;
	p->k[1] = 0.10355509;
	p->k[2] = 0.10355509;
	/*�����ʼ����������*/
	for(i=0;i<SAMPLE_NUM;i++)
	{
		p->data[i] = 0;
	}
}


/*
 * FunName:CON_Sample
 * Description:�Բ������ݽ��д���Դ��������DMA����������DMA_Buf��
 * 			   DMA_Buf��һ��ȫ�ֱ�����������TPVSI_DSP28335_BSP.c��
 * Input:�����ṹ��ָ��p
 * Output:None
 * Others:None
 * */
void CON_Sample(Sample_Stru *p)
{
	static int zero[SAMPLE_NUM];
	Uint8 i = 0;
	/*TODO�������ﶨ��������ƫ����*/
	zero[0] = 1430;
	zero[1] = 1483;
	zero[2] = 1430;
	/*����������������*/
	for(;i<SAMPLE_NUM;i++)
	{
		p->data[i] = p->k[i]*(float)((int)DMA_Buf[i] - zero[i]);
	}
}
//�������֮��ɾ����
void ABC_DQ0_POS_Init(ABC_DQ0_POS_F *abc_dq0_pos1)
{
	ABC_DQ0_POS_F_init(abc_dq0_pos1);
}


/*
 * FunName:CON_ABC_DQ0_CAL
 * Description:abc->dq0��ת����TI ControlSuite��
 * Input:a,b,c�������,������н�theta,abc_dq0�ṹ��ָ��abc_dq0_pos
 * Output:None
 * Others:None
 * */
void CON_ABC_DQ0_CAL(float32 a,float32 b,float32 c,float32 theta,ABC_DQ0_POS_F *abc_dq0_pos1)
{
	abc_dq0_pos1->a = a;
	abc_dq0_pos1->b = b;
	abc_dq0_pos1->c = c;
	abc_dq0_pos1->sin = sin(theta);
	abc_dq0_pos1->cos = cos(theta);
	ABC_DQ0_POS_F_FUNC(abc_dq0_pos1);
}


/*
 * FunName:CON_PID_DeInit
 * Description:��PID�ṹ���ʼ��Ϊȱʡֵ
 * Input:PID�ṹ��ָ��p
 * Output:None
 * Others:None
 * */
void CON_PID_DeInit(PID_Stru *p)
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
 * FunName:CON_PID_Init
 * Description:��PID�ṹ�尴�ո���������ʼ��
 * Input:PID�ṹ��ָ��p,����ʱ��Ts,����ϵ��kp,����ϵ��ki
 * Output:None
 * Others:None
 * */
void CON_PID_Init(PID_Stru *p,float Ts,float kp,float ki)
{
	CON_PID_DeInit(p);
	p->Ts = Ts;
	p->kp = kp;
	p->ki = ki;
}


/*
 * FunName:CON_VOL_CL_PID
 * Description:��ѹ�ջ�pid����
 * Input:PID�ṹ��ָ��p
 * Output:None
 * Others:None
 * */
void CON_VOL_CL_PID(PID_Stru *dpid,PID_Stru *qpid,ABC_DQ0_POS_F *abc_dq0_pos1)
{
	//Ŀ��ֵ�趨
	float d_target = 0;
	float q_target = 0;
	//��������
	dpid->err_last = dpid->err;
	qpid->err_last = qpid->err;
	dpid->err = d_target - abc_dq0_pos1->d;
	qpid->err = q_target - abc_dq0_pos1->q;
	dpid->output_last = dpid->output;
	qpid->output_last = qpid->output;
	dpid->output = dpid->output_last + dpid->kp*(dpid->err - dpid->err_last) + dpid->ki*dpid->Ts*dpid->err;
	qpid->output = qpid->output_last + qpid->kp*(qpid->err - qpid->err_last) + qpid->ki*qpid->Ts*qpid->err;
	if(dpid->output>1)
		dpid->output = 1;
		else if(dpid->output<0)
			dpid->output = 0;
	if(qpid->output>1)
			qpid->output = 1;
		else if(qpid->output<0)
			qpid->output = 0;
}






