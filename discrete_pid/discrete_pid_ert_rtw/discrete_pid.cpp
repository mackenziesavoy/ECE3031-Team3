//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: discrete_pid.cpp
//
// Code generated for Simulink model 'discrete_pid'.
//
// Model version                  : 1.22
// Simulink Coder version         : 9.0 (R2018b) 24-May-2018
// C/C++ source code generated on : Mon Mar 23 19:10:56 2020
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
  int16_T rtb_Saturation;
  int16_T rtb_ProportionalGain;
  int16_T rtb_IntegralGain;
  int16_T rtb_IntegralGain_j;
  int16_T rtb_TSamp;
  int16_T rtb_TSamp_g;
  int16_T Integrator;
  int16_T Integrator_f;

  // Sum: '<Root>/PositionSubtractor' incorporates:
  //   DiscreteIntegrator: '<Root>/VelocityIntegrator'
  //   Inport: '<Root>/measuredPosition'

  rtb_Saturation = (rtDW.VelocityIntegrator_DSTATE * 4295L < 0L ? -1 : 0) -
    rtU.measuredPosition;

  // Gain: '<S170>/Proportional Gain'
  rtb_ProportionalGain = 20 * rtb_Saturation;

  // Gain: '<S143>/Integral Gain'
  rtb_IntegralGain = 5 * rtb_Saturation;

  // DiscreteIntegrator: '<S153>/Integrator'
  Integrator = rtDW.Integrator_DSTATE + rtb_IntegralGain;

  // Gain: '<S130>/Derivative Gain'
  rtb_Saturation <<= 4;

  // SampleTimeMath: '<S132>/TSamp'
  //
  //  About '<S132>/TSamp':
  //   y = u * K where K = 1 / ( w * Ts )
  //   Multiplication by K = weightedTsampQuantized is being
  //   done implicitly by changing the scaling of the input signal.
  //   No work needs to be done here.  Downstream blocks may need
  //   to do work to handle the scaling of the output; this happens
  //   automatically.

  rtb_TSamp = rtb_Saturation;

  // Sum: '<S132>/Diff' incorporates:
  //   Delay: '<S132>/UD'
  //   SampleTimeMath: '<S132>/TSamp'
  //
  //  About '<S132>/TSamp':
  //   y = u * K where K = 1 / ( w * Ts )
  //   Multiplication by K = weightedTsampQuantized is being
  //   done implicitly by changing the scaling of the input signal.
  //   No work needs to be done here.  Downstream blocks may need
  //   to do work to handle the scaling of the output; this happens
  //   automatically.

  rtb_Saturation -= rtDW.UD_DSTATE;

  // Sum: '<S183>/Sum'
  rtb_Saturation = ((Integrator * 4295L < 0L ? -1 : 0) + rtb_ProportionalGain) +
    (int16_T)(rtb_Saturation * 2000000LL);

  // Saturate: '<S174>/Saturation'
  if (rtb_Saturation > 108) {
    rtb_Saturation = 108;
  } else {
    if (rtb_Saturation < -108) {
      rtb_Saturation = -108;
    }
  }

  // End of Saturate: '<S174>/Saturation'

  // Sum: '<Root>/CurrentSubtractor' incorporates:
  //   Inport: '<Root>/currentMeasurement'

  rtb_Saturation -= rtU.currentMeasurement;

  // Gain: '<S74>/Proportional Gain'
  rtb_ProportionalGain = 20 * rtb_Saturation;

  // Gain: '<S47>/Integral Gain'
  rtb_IntegralGain_j = 5 * rtb_Saturation;

  // DiscreteIntegrator: '<S57>/Integrator'
  Integrator_f = rtDW.Integrator_DSTATE_f + rtb_IntegralGain_j;

  // Gain: '<S34>/Derivative Gain'
  rtb_Saturation <<= 4;

  // SampleTimeMath: '<S36>/TSamp'
  //
  //  About '<S36>/TSamp':
  //   y = u * K where K = 1 / ( w * Ts )
  //   Multiplication by K = weightedTsampQuantized is being
  //   done implicitly by changing the scaling of the input signal.
  //   No work needs to be done here.  Downstream blocks may need
  //   to do work to handle the scaling of the output; this happens
  //   automatically.

  rtb_TSamp_g = rtb_Saturation;

  // Sum: '<S87>/Sum' incorporates:
  //   Delay: '<S36>/UD'
  //   SampleTimeMath: '<S36>/TSamp'
  //   Sum: '<S36>/Diff'
  //
  //  About '<S36>/TSamp':
  //   y = u * K where K = 1 / ( w * Ts )
  //   Multiplication by K = weightedTsampQuantized is being
  //   done implicitly by changing the scaling of the input signal.
  //   No work needs to be done here.  Downstream blocks may need
  //   to do work to handle the scaling of the output; this happens
  //   automatically.

  rtb_Saturation = ((Integrator_f * 4295L < 0L ? -1 : 0) + rtb_ProportionalGain)
    + (int16_T)((rtb_Saturation - rtDW.UD_DSTATE_p) * 2000000LL);

  // Saturate: '<S78>/Saturation'
  if (rtb_Saturation > 255) {
    rtb_Saturation = 255;
  } else {
    if (rtb_Saturation < 0) {
      rtb_Saturation = 0;
    }
  }

  // End of Saturate: '<S78>/Saturation'

  // Switch: '<Root>/Switch' incorporates:
  //   Constant: '<Root>/Constant'

  if (rtb_Saturation <= 0) {
    rtb_Saturation = 0;
  }

  // End of Switch: '<Root>/Switch'

  // Outport: '<Root>/motorDutyA' incorporates:
  //   Gain: '<Root>/Gain'

  rtY.motorDutyA = 0.00390625 * (real_T)rtb_Saturation;

  // Outport: '<Root>/motorDutyB' incorporates:
  //   Gain: '<Root>/Gain1'

  rtY.motorDutyB = 0.0;

  // Update for DiscreteIntegrator: '<Root>/VelocityIntegrator' incorporates:
  //   Inport: '<Root>/desiredVelocity'

  rtDW.VelocityIntegrator_DSTATE += rtU.desiredVelocity;

  // Update for DiscreteIntegrator: '<S153>/Integrator'
  rtDW.Integrator_DSTATE = Integrator + rtb_IntegralGain;

  // Update for Delay: '<S132>/UD'
  rtDW.UD_DSTATE = rtb_TSamp;

  // Update for DiscreteIntegrator: '<S57>/Integrator'
  rtDW.Integrator_DSTATE_f = Integrator_f + rtb_IntegralGain_j;

  // Update for Delay: '<S36>/UD'
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
