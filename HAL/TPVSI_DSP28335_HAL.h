/*
 * TPVSI_DSP28335_HAL.h
 *
 *  Created on: 2018��3��10��
 *      Author: wangchu
 */

#ifndef HAL_TPVSI_DSP28335_HAL_H_
#define HAL_TPVSI_DSP28335_HAL_H_
#include "TPVSI_DSP28335_BSP.h"


/*
 * StructureName:EPWM_structure
 * Description:EPWMģ��ĳ���ṹ�塣
 * Elements:
 * 	cmp_max->�ȽϼĴ�����������ֵ
 * 	cmp_min->�ȽϼĴ����������Сֵ
 * 	fre->EPWMģ��Ĺ���Ƶ��
 * 	bias->���ȽϼĴ�����ֵʱ��ƫ����
 * 	cmpa_value->�ȽϼĴ���a��ֵ
 * 	cmpb_value->�ȽϼĴ���b��ֵ
 * */
typedef struct{
	Uint16 cmp_max;
	Uint16 cmp_min;
	Uint16 fre;
	Uint16 bias;
	Uint16 cmpa_value;
	Uint16 cmpb_value;
} EPWM_structure;

/*
 * StructureName:Sin_structure
 * Description:Sine����ֵ�ṹ�塣
 * Elements:
 * 	Angle->��ǰ�Ƕ�
 * 	sin_value->��ǰ�Ƕȵ�����ֵ
 * */
typedef struct{
  float Angle;
  float sin_value;
} Sin_structure;

extern Sin_structure _p_sin1;
extern EPWM_structure _p_epwm1;
extern EPWM_structure _p_epwm2;
extern EPWM_structure _p_epwm3;
void HAL_EPWM_Structure_Init(void);
void HAL_PWM_DutyValue_Cal(EPWM_structure *ep,float duty,float duty_max,float duty_min);
void HAL_Init(void);
#endif /* HAL_TPVSI_DSP28335_HAL_H_ */
