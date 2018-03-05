/*
 * Title:3 Phase VSI Base Program
 * Author:Chuck Wang
 * Description:�ṩ�������������Ҫ�Ļ�������,��Ҫ����:
 * A���弶Ӳ����ʼ�����򣬰����弶Ӳ����ʼ��������������TPVSI_DSP28335_BSP.c��
 * B���жϳ��򣬰�����������Ҫ���жϺ�����������TPVSI_DSP28335_BSP.c��
 * main.c
 */


#include "DSP28x_Project.h"


/*ȫ�ֱ�������*/
int main(void)
{
	memcpy((Uint16 *)&RamfuncsRunStart,(Uint16 *)&RamfuncsLoadStart, (unsigned long)&RamfuncsLoadSize);
	InitSysCtrl();
	DINT;
	/*TODO:��������GPIO*/
	BSP_GPIO_Init();
	/*���治Ҫ�޸�*/
	/*Begin*/
	//�ж�����
	InitPieCtrl();
	//��������жϱ�־λ
	IER = 0x0000;
	IFR = 0x0000;
	InitPieVectTable();
	/*End*/
	/*TODO:����ָ���жϺ���*/
	EALLOW;
	PieVectTable.EPWM1_INT = &epwm1_isr;
	EDIS;
	/*TODO:�����ʼ������*/
	BSP_ADC_Init();
	BSP_ePWM_Init();
	BSP_DMA_Init();
	/*TODO:�����ʼ��һЩ�ṹ��֮��Ķ���*/
	EPWM_Structure_Init();
	CON_Sample_Init(&p_vol_sam);
	ABC_DQ0_POS_F_init(&p_vol_dq0);
	/*TODO:���������ж�Դ*/
	IER |= M_INT3;
	PieCtrlRegs.PIEIER3.bit.INTx1 = 1;
	/*���濪���жϣ���Ҫ�޸�*/
	/*Begin*/
	EINT;
	ERTM;
	/*End*/
	for(;;)
	{

	}
	return 0;
}
