/*
 * TPVSI_DSP28335_INT.c
 *
 *  Created on: 2018��1��12��
 *      Author: Chuck Wang
 */
#include "TPVSI_DSP28335_INT.h"
#include "TPVSI_DSP28335_HAL.h"
//#include "TPVSI_DSP28335_Control.h"

#pragma CODE_SECTION(epwm1_isr,"ramfuncs");

__interrupt void epwm1_isr(void)
{
	/*TODO:�����д�жϺ���*/
	GpioDataRegs.GPBSET.bit.GPIO60 = 1;
	_p_sin1.Angle += 0.0251327;
	if(_p_sin1.Angle>6.2831853)
		_p_sin1.Angle = 0;
/*	CON_DQ0_ABC_CAL(0.9,0,0,_p_sin1.Angle,&p_dq0_abc);
	CON_VOL_CL_ABC_REG(&p_dq0_abc,&_p_epwm1,&_p_epwm2,&_p_epwm3);*/
	AAL_Trans_SetDQ0Value(&Control_Data,0.9,0,0);
	AAL_Trans_DQ0ABC(&Control_Data,_p_sin1.Angle);
	HAL_DutySet(&Control_Data,&_p_epwm1,&_p_epwm2,&_p_epwm3);
	HAL_Sample(&p_sam);
	AAL_Trans_Update(&p_sam);
//	CON_ABC_DQ0_CAL(p_sam.data[CurrentA],p_sam.data[CurrentB],p_sam.data[CurrentC],_p_sin1.Angle,&p_vol_dq0);
	AAL_Trans_ABCDQ0(&Inverter_Voltage_Data,_p_sin1.Angle);
#if _GRAPH_DISPLAY_
	CON_PUSH_BUFFER(p_vol_sam.data[1]);
#endif
	GpioDataRegs.GPBCLEAR.bit.GPIO60 = 1;
	/*����������жϱ�־λ����Ҫ�޸�*/
	/* Begin*/
	EPwm1Regs.ETCLR.bit.INT = 1;
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
	/*End*/
}



