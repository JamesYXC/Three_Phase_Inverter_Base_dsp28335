/*
 * TPVSI_DSP28335_Control.h
 *
 *  Created on: 2018��3��4��
 *      Author: chen318
 */

#ifndef TPVSI_DSP28335_CONTROL_H_
#define TPVSI_DSP28335_CONTROL_H_

#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "TPVSI_DSP28335_BSP.h"
#include "Solar_F.h"

#define SAMPLE_NUM 3
typedef struct{
	float data[SAMPLE_NUM];//����
	float k[SAMPLE_NUM];//ADCת���ı���ϵ��
}Sample_Stru;

typedef struct{
	float kp;
	float ki;
	float Ts;
	float output;
	float err;
	float err_last;
	float output_last;
}PID_Stru;


#endif /* TPVSI_DSP28335_CONTROL_H_ */
