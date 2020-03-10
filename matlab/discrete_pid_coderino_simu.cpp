//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: discrete_pid_coderino_simu.cpp
//
// Code generated for Simulink model 'discrete_pid_coderino_simu'.
//
// Model version                  : 1.14
// Simulink Coder version         : 9.0 (R2018b) 24-May-2018
// C/C++ source code generated on : Tue Mar 10 20:11:50 2020
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
  int16_T rtb_Add;
  int16_T Integrator;
  int16_T u0;

  // Sum: '<Root>/Add' incorporates:
  //   Inport: '<Root>/ADC_VAL'
  //   Inport: '<Root>/Set_Point '

  rtb_Add = rtU.Set_Point - rtU.ADC_VAL;

  // DiscreteIntegrator: '<S56>/Integrator'
  Integrator = rtDW.Integrator_DSTATE + rtb_Add;

  // Sum: '<S86>/Sum' incorporates:
  //   Delay: '<S35>/UD'
  //   Sum: '<S35>/Diff'

  u0 = ((int16_T)((Integrator * 13107L) >> 17) + rtb_Add) + (int16_T)
    (-rtDW.UD_DSTATE * 5L);

  // Saturate: '<S77>/Saturation'
  if (u0 > 255) {
    // Outport: '<Root>/PID_OUT'
    rtY.PID_OUT = 255;
  } else if (u0 < 0) {
    // Outport: '<Root>/PID_OUT'
    rtY.PID_OUT = 0;
  } else {
    // Outport: '<Root>/PID_OUT'
    rtY.PID_OUT = u0;
  }

  // End of Saturate: '<S77>/Saturation'

  // Update for DiscreteIntegrator: '<S56>/Integrator'
  rtDW.Integrator_DSTATE = Integrator + rtb_Add;

  // Update for Delay: '<S35>/UD'
  rtDW.UD_DSTATE = 0;
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
