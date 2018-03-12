/*
 * TPVSI_DSP28335_HAL.c
 *
 *  Created on: 2018��3��10��
 *      Author: wangchu
 */
#include "TPVSI_DSP28335_HAL.h"
#include "C28x_FPU_FastRTS.h"
EPWM_structure _p_epwm1;
EPWM_structure _p_epwm2;
EPWM_structure _p_epwm3;
Sin_structure _p_sin1;
Sample_structure p_vol_sam;

#pragma CODE_SECTION(HAL_Sample,"ramfuncs");

void HAL_Init(void)
{
	HAL_EPWM_Structure_Init();
	BSP_ADC_Init();
	BSP_ePWM_Init();
	BSP_DMA_Init();

}
void HAL_EPWM_Structure_Init(void)
{
	_p_epwm1.fre = 50000;
	_p_epwm1.bias = 1500;
	_p_epwm1.cmp_max = 3000;
	_p_epwm1.cmp_min = 0;
	_p_epwm1.cmpa_value = 1500;
	_p_epwm1.cmpb_value = 1500;
	_p_epwm2.fre = 50000;
	_p_epwm2.bias = 1500;
	_p_epwm2.cmp_max = 3000;
	_p_epwm2.cmp_min = 0;
	_p_epwm2.cmpa_value = 1500;
	_p_epwm2.cmpb_value = 1500;
	_p_epwm3.fre = 50000;
	_p_epwm3.bias = 1500;
	_p_epwm3.cmp_max = 3000;
	_p_epwm3.cmp_min = 0;
	_p_epwm3.cmpa_value = 1500;
	_p_epwm3.cmpb_value = 1500;
}


void HAL_PWM_DutyValue_Cal(EPWM_structure *ep,float duty,float duty_max,float duty_min)
{
	Uint16 temp;
	if(duty>duty_max) duty = duty_max;
	else if(duty<duty_min) duty = duty_min;
	temp = (Uint16)(duty*((ep->cmp_max) - (ep->cmp_min))/2.0 + (ep->bias));
	if(temp>(ep->cmp_max)) temp = ep->cmp_max;
	else if (temp<(ep->cmp_min)) temp = ep->cmp_min;
	ep->cmpa_value = temp;
}

/*
 * FunName:HAL_Sample_Init
 * Description:��ʼ�������ṹ�壬ϵ��k��������˲������ݵ���ʵ����ת����ϵ�����������ĳ�ʼ��Ӧ��������ݵĶ��ٶ���
 * Input:�����ṹ��ָ��p
 * Output:None
 * */
void HAL_Sample_Init(Sample_structure *p)
{
	Uint8 i;
	/*TODO:�����ﶨ�������ϵ��*/
	p->k[0] = 0.0362;
	p->k[1] = 0.0362;
	p->k[2] = 0.0362;
	p->k[3] = 0.014066;
	p->k[4] = 0.014066;
	p->k[5] = 0.014066;
	/*�����ʼ����������*/
	for(i=0;i<SAMPLE_NUM;i++)
	{
		p->data[i] = 0;
	}
}

/*
 * FunName:HAL_Sample
 * Description:�Բ������ݽ��д���Դ��������DMA����������DMA_Buf��
 * 			   DMA_Buf��һ��ȫ�ֱ�����������TPVSI_DSP28335_BSP.c��
 * Input:�����ṹ��ָ��p
 * Output:None
 * Others:None
 * */
void HAL_Sample(Sample_structure *p)
{
	static int zero[SAMPLE_NUM];
	Uint8 i = 0;
	/*TODO�������ﶨ��������ƫ����*/
	zero[0] = 1430;
	zero[1] = 1483;
	zero[2] = 1430;
	zero[3] = 1566;
	zero[4] = 1567;
	zero[5] = 1567;
	/*����������������*/
	for(;i<SAMPLE_NUM;i++)
	{
		p->data[i] = p->k[i]*(float)((int)DMA_Buf[i] - zero[i]);
	}
}
