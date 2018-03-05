/*
 * TPVSI_DSP28335_INT.c
 *
 *  Created on: 2018��1��12��
 *      Author: Chuck Wang
 */
#include "TPVSI_DSP28335_INT.h"
#include "TPVSI_DSP28335_SPWM.h"
#include "TPVSI_DSP28335_Control.h"



__interrupt void epwm1_isr(void)
{
	/*TODO:�����д�жϺ���*/
	SPWM_Sin_Cal(&_p_sin1);
	SPWM_DutyValue_Cal(&_p_epwm1,0.9*(_p_sin1.sin_value),0.9,-0.9);
	EPwm1Regs.CMPA.half.CMPA = _p_epwm1.cmpa_value;
	EPwm2Regs.CMPA.half.CMPA = _p_epwm1.cmpa_value;
	EPwm3Regs.CMPA.half.CMPA = _p_epwm1.cmpa_value;
	CON_Sample(&p_vol_sam);
	/*����������жϱ�־λ����Ҫ�޸�*/
	/* Begin*/
	EPwm1Regs.ETCLR.bit.INT = 1;
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
	/*End*/
}



