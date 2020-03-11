//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: discrete_pid_coderino_simu.cpp
//
// Code generated for Simulink model 'discrete_pid_coderino_simu'.
//
// Model version                  : 1.15
// Simulink Coder version         : 9.0 (R2018b) 24-May-2018
// C/C++ source code generated on : Wed Mar 11 17:19:49 2020
//
// Target selection: ert.tlc
// Embedded hardware selection: Atmel->AVR (8-bit)
// Code generation objectives:
//    1. Execution efficiency
//    2. RAM efficiency
// Validation result: Not run
//
#include "discrete_pid_coderino_simu.h"
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
  int16_T rtb_Diff;
  int16_T rtb_ProportionalGain;
  int16_T rtb_IntegralGain;
  int16_T rtb_TSamp;
  int16_T Integrator;

  // Sum: '<Root>/Add' incorporates:
  //   Inport: '<Root>/ADC_VAL'
  //   Inport: '<Root>/Set_Point '

  rtb_Diff = rtU.Set_Point - rtU.ADC_VAL;

  // Gain: '<S73>/Proportional Gain'
  rtb_ProportionalGain = 20 * rtb_Diff;

  // Gain: '<S46>/Integral Gain'
  rtb_IntegralGain = 5 * rtb_Diff;

  // DiscreteIntegrator: '<S56>/Integrator'
  Integrator = rtDW.Integrator_DSTATE + rtb_IntegralGain;

  // Gain: '<S33>/Derivative Gain'
  rtb_Diff *= 17;

  // SampleTimeMath: '<S35>/TSamp'
  //
  //  About '<S35>/TSamp':
  //   y = u * K where K = 1 / ( w * Ts )
  //   Multiplication by K = weightedTsampQuantized is being
  //   done implicitly by changing the scaling of the input signal.
  //   No work needs to be done here.  Downstream blocks may need
  //   to do work to handle the scaling of the output; this happens
  //   automatically.

  rtb_TSamp = rtb_Diff;

  // Sum: '<S35>/Diff' incorporates:
  //   Delay: '<S35>/UD'
  //   SampleTimeMath: '<S35>/TSamp'
  //
  //  About '<S35>/TSamp':
  //   y = u * K where K = 1 / ( w * Ts )
  //   Multiplication by K = weightedTsampQuantized is being
  //   done implicitly by changing the scaling of the input signal.
  //   No work needs to be done here.  Downstream blocks may need
  //   to do work to handle the scaling of the output; this happens
  //   automatically.

  rtb_Diff -= rtDW.UD_DSTATE;

  // Sum: '<S86>/Sum'
  rtb_Diff = ((int16_T)((Integrator * 13107L) >> 17) + rtb_ProportionalGain) +
    (int16_T)(rtb_Diff * 5L);

  // Saturate: '<S77>/Saturation'
  if (rtb_Diff > 255) {
    // Outport: '<Root>/PID_OUT'
    rtY.PID_OUT = 255;
  } else if (rtb_Diff < 0) {
    // Outport: '<Root>/PID_OUT'
    rtY.PID_OUT = 0;
  } else {
    // Outport: '<Root>/PID_OUT'
    rtY.PID_OUT = rtb_Diff;
  }

  // End of Saturate: '<S77>/Saturation'

  // Update for DiscreteIntegrator: '<S56>/Integrator'
  rtDW.Integrator_DSTATE = Integrator + rtb_IntegralGain;

  // Update for Delay: '<S35>/UD'
  rtDW.UD_DSTATE = rtb_TSamp;
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
