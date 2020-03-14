//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: discrete_pid.cpp
//
// Code generated for Simulink model 'discrete_pid'.
//
// Model version                  : 1.16
// Simulink Coder version         : 9.0 (R2018b) 24-May-2018
// C/C++ source code generated on : Sat Mar 14 15:23:36 2020
//
// Target selection: ert.tlc
// Embedded hardware selection: Atmel->AVR (8-bit)
// Code generation objectives:
//    1. Execution efficiency
//    2. RAM efficiency
// Validation result: Not run
//
#include "discrete_pid.h"
#ifndef UCHAR_MAX
#include <limits.h>
#endif

#if ( UCHAR_MAX != (0xFFU) ) || ( SCHAR_MAX != (0x7F) )
#error Code was generated for compiler with different sized uchar/char. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( USHRT_MAX != (0xFFFFU) ) || ( SHRT_MAX != (0x7FFF) )
#error Code was generated for compiler with different sized ushort/short. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( UINT_MAX != (0xFFFFU) ) || ( INT_MAX != (0x7FFF) )
#error Code was generated for compiler with different sized uint/int. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( ULONG_MAX != (0xFFFFFFFFUL) ) || ( LONG_MAX != (0x7FFFFFFFL) )
#error Code was generated for compiler with different sized ulong/long. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

// Skipping ulong_long/long_long check: insufficient preprocessor integer range. 

// Model step function
void discrete_pid_coderino_simuModelClass::step()
{
  int16_T rtb_Sum;
  int16_T rtb_ProportionalGain;
  int16_T rtb_IntegralGain;
  int16_T rtb_IntegralGain_j;
  int16_T rtb_TSamp;
  int16_T rtb_TSamp_g;
  int16_T Integrator;
  int16_T Integrator_f;

  // Sum: '<Root>/Add' incorporates:
  //   Inport: '<Root>/ENC_Pos'
  //   Inport: '<Root>/Set_Point '

  rtb_Sum = rtU.Set_Point - rtU.ENC_Pos;

  // Gain: '<S74>/Proportional Gain'
  rtb_ProportionalGain = 20 * rtb_Sum;

  // Gain: '<S47>/Integral Gain'
  rtb_IntegralGain = 5 * rtb_Sum;

  // DiscreteIntegrator: '<S57>/Integrator'
  Integrator = rtDW.Integrator_DSTATE + rtb_IntegralGain;

  // Gain: '<S34>/Derivative Gain'
  rtb_Sum <<= 4;

  // SampleTimeMath: '<S36>/TSamp'
  //
  //  About '<S36>/TSamp':
  //   y = u * K where K = 1 / ( w * Ts )
  //   Multiplication by K = weightedTsampQuantized is being
  //   done implicitly by changing the scaling of the input signal.
  //   No work needs to be done here.  Downstream blocks may need
  //   to do work to handle the scaling of the output; this happens
  //   automatically.

  rtb_TSamp = rtb_Sum;

  // Sum: '<S36>/Diff' incorporates:
  //   Delay: '<S36>/UD'
  //   SampleTimeMath: '<S36>/TSamp'
  //
  //  About '<S36>/TSamp':
  //   y = u * K where K = 1 / ( w * Ts )
  //   Multiplication by K = weightedTsampQuantized is being
  //   done implicitly by changing the scaling of the input signal.
  //   No work needs to be done here.  Downstream blocks may need
  //   to do work to handle the scaling of the output; this happens
  //   automatically.

  rtb_Sum -= rtDW.UD_DSTATE;

  // Sum: '<S87>/Sum'
  rtb_Sum = ((int16_T)((Integrator * 13107L) >> 17) + rtb_ProportionalGain) +
    (int16_T)(rtb_Sum * 5L);

  // Saturate: '<S78>/Saturation'
  if (rtb_Sum > 108) {
    rtb_Sum = 108;
  } else {
    if (rtb_Sum < -108) {
      rtb_Sum = -108;
    }
  }

  // End of Saturate: '<S78>/Saturation'

  // Sum: '<Root>/Add1' incorporates:
  //   Inport: '<Root>/ADC_VAL'

  rtb_Sum -= rtU.ADC_VAL;

  // Gain: '<S170>/Proportional Gain'
  rtb_ProportionalGain = 20 * rtb_Sum;

  // Gain: '<S143>/Integral Gain'
  rtb_IntegralGain_j = 5 * rtb_Sum;

  // DiscreteIntegrator: '<S153>/Integrator'
  Integrator_f = rtDW.Integrator_DSTATE_f + rtb_IntegralGain_j;

  // Gain: '<S130>/Derivative Gain'
  rtb_Sum <<= 4;

  // SampleTimeMath: '<S132>/TSamp'
  //
  //  About '<S132>/TSamp':
  //   y = u * K where K = 1 / ( w * Ts )
  //   Multiplication by K = weightedTsampQuantized is being
  //   done implicitly by changing the scaling of the input signal.
  //   No work needs to be done here.  Downstream blocks may need
  //   to do work to handle the scaling of the output; this happens
  //   automatically.

  rtb_TSamp_g = rtb_Sum;

  // Sum: '<S183>/Sum' incorporates:
  //   Delay: '<S132>/UD'
  //   SampleTimeMath: '<S132>/TSamp'
  //   Sum: '<S132>/Diff'
  //
  //  About '<S132>/TSamp':
  //   y = u * K where K = 1 / ( w * Ts )
  //   Multiplication by K = weightedTsampQuantized is being
  //   done implicitly by changing the scaling of the input signal.
  //   No work needs to be done here.  Downstream blocks may need
  //   to do work to handle the scaling of the output; this happens
  //   automatically.

  rtb_Sum = ((int16_T)((Integrator_f * 13107L) >> 17) + rtb_ProportionalGain) +
    (int16_T)((rtb_Sum - rtDW.UD_DSTATE_p) * 5L);

  // Saturate: '<S174>/Saturation'
  if (rtb_Sum > 255) {
    // Outport: '<Root>/PID_OUT'
    rtY.PID_OUT = 255;
  } else if (rtb_Sum < 0) {
    // Outport: '<Root>/PID_OUT'
    rtY.PID_OUT = 0;
  } else {
    // Outport: '<Root>/PID_OUT'
    rtY.PID_OUT = rtb_Sum;
  }

  // End of Saturate: '<S174>/Saturation'

  // Update for DiscreteIntegrator: '<S57>/Integrator'
  rtDW.Integrator_DSTATE = Integrator + rtb_IntegralGain;

  // Update for Delay: '<S36>/UD'
  rtDW.UD_DSTATE = rtb_TSamp;

  // Update for DiscreteIntegrator: '<S153>/Integrator'
  rtDW.Integrator_DSTATE_f = Integrator_f + rtb_IntegralGain_j;

  // Update for Delay: '<S132>/UD'
  rtDW.UD_DSTATE_p = rtb_TSamp_g;
}

// Model initialize function
void discrete_pid_coderino_simuModelClass::initialize()
{
  // (no initialization code required)
}

// Constructor
discrete_pid_coderino_simuModelClass::discrete_pid_coderino_simuModelClass()
{
  // Currently there is no constructor body generated.
}

// Destructor
discrete_pid_coderino_simuModelClass::~discrete_pid_coderino_simuModelClass()
{
  // Currently there is no destructor body generated.
}

//
// File trailer for generated code.
//
// [EOF]
//
