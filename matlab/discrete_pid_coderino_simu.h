//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: discrete_pid_coderino_simu.h
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
#ifndef RTW_HEADER_discrete_pid_coderino_simu_h_
#define RTW_HEADER_discrete_pid_coderino_simu_h_
#ifndef discrete_pid_coderino_simu_COMMON_INCLUDES_
# define discrete_pid_coderino_simu_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 // discrete_pid_coderino_simu_COMMON_INCLUDES_ 

// Macros for accessing real-time model data structure

// Block signals and states (default storage) for system '<Root>'
typedef struct {
  int16_T UD_DSTATE;                   // '<S35>/UD'
  int16_T Integrator_DSTATE;           // '<S56>/Integrator'
} DW;

// External inputs (root inport signals with default storage)
typedef struct {
  uint8_T Set_Point;                   // '<Root>/Set_Point '
  uint8_T ADC_VAL;                     // '<Root>/ADC_VAL'
} ExtU;

// External outputs (root outports fed by signals with default storage)
typedef struct {
  int16_T PID_OUT;                     // '<Root>/PID_OUT'
} ExtY;

// Class declaration for model discrete_pid_coderino_simu
class discrete_pid_coderino_simuModelClass {
  // public data and function members
 public:
  // External inputs
  ExtU rtU;

  // External outputs
  ExtY rtY;

  // model initialize function
  void initialize();

  // model step function
  void step();

  // Constructor
  discrete_pid_coderino_simuModelClass();

  // Destructor
  ~discrete_pid_coderino_simuModelClass();

  // private data and function members
 private:
  // Block signals and states
  DW rtDW;
};

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S35>/DTDup' : Unused code path elimination
//  Block '<S46>/Integral Gain' : Eliminated nontunable gain of 1
//  Block '<S73>/Proportional Gain' : Eliminated nontunable gain of 1


//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'discrete_pid_coderino_simu'
//  '<S1>'   : 'discrete_pid_coderino_simu/Discrete PID Controller'
//  '<S2>'   : 'discrete_pid_coderino_simu/Discrete PID Controller/Anti-windup'
//  '<S3>'   : 'discrete_pid_coderino_simu/Discrete PID Controller/D Gain'
//  '<S4>'   : 'discrete_pid_coderino_simu/Discrete PID Controller/Filter'
//  '<S5>'   : 'discrete_pid_coderino_simu/Discrete PID Controller/Filter ICs'
//  '<S6>'   : 'discrete_pid_coderino_simu/Discrete PID Controller/I Gain'
//  '<S7>'   : 'discrete_pid_coderino_simu/Discrete PID Controller/Ideal P Gain'
//  '<S8>'   : 'discrete_pid_coderino_simu/Discrete PID Controller/Ideal P Gain Fdbk'
//  '<S9>'   : 'discrete_pid_coderino_simu/Discrete PID Controller/Integrator'
//  '<S10>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Integrator ICs'
//  '<S11>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/N Copy'
//  '<S12>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/N Gain'
//  '<S13>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/P Copy'
//  '<S14>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Parallel P Gain'
//  '<S15>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Reset Signal'
//  '<S16>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Saturation'
//  '<S17>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Saturation Fdbk'
//  '<S18>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Sum'
//  '<S19>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Sum Fdbk'
//  '<S20>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Tracking Mode'
//  '<S21>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Tracking Mode Sum'
//  '<S22>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/postSat Signal'
//  '<S23>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/preSat Signal'
//  '<S24>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Anti-windup/Back Calculation'
//  '<S25>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Anti-windup/Cont. Clamping Ideal'
//  '<S26>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Anti-windup/Cont. Clamping Parallel'
//  '<S27>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Anti-windup/Disabled'
//  '<S28>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Anti-windup/Disc. Clamping Ideal'
//  '<S29>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Anti-windup/Disc. Clamping Parallel'
//  '<S30>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Anti-windup/Passthrough'
//  '<S31>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/D Gain/Disabled'
//  '<S32>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/D Gain/External Parameters'
//  '<S33>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/D Gain/Internal Parameters'
//  '<S34>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Filter/Cont. Filter'
//  '<S35>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Filter/Differentiator'
//  '<S36>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Filter/Disabled'
//  '<S37>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Filter/Disc. Backward Euler Filter'
//  '<S38>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Filter/Disc. Forward Euler Filter'
//  '<S39>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Filter/Disc. Trapezoidal Filter'
//  '<S40>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Filter ICs/Disabled'
//  '<S41>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Filter ICs/External IC'
//  '<S42>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Filter ICs/Internal IC - Differentiator'
//  '<S43>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Filter ICs/Internal IC - Filter'
//  '<S44>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/I Gain/Disabled'
//  '<S45>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/I Gain/External Parameters'
//  '<S46>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/I Gain/Internal Parameters'
//  '<S47>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Ideal P Gain/External Parameters'
//  '<S48>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Ideal P Gain/Internal Parameters'
//  '<S49>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Ideal P Gain/Passthrough'
//  '<S50>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Ideal P Gain Fdbk/Disabled'
//  '<S51>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Ideal P Gain Fdbk/External Parameters'
//  '<S52>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Ideal P Gain Fdbk/Internal Parameters'
//  '<S53>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Ideal P Gain Fdbk/Passthrough'
//  '<S54>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Integrator/Continuous'
//  '<S55>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Integrator/Disabled'
//  '<S56>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Integrator/Discrete'
//  '<S57>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Integrator ICs/Disabled'
//  '<S58>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Integrator ICs/External IC'
//  '<S59>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Integrator ICs/Internal IC'
//  '<S60>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/N Copy/Disabled'
//  '<S61>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/N Copy/Disabled wSignal Specification'
//  '<S62>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/N Copy/External Parameters'
//  '<S63>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/N Copy/Internal Parameters'
//  '<S64>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/N Gain/Disabled'
//  '<S65>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/N Gain/External Parameters'
//  '<S66>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/N Gain/Internal Parameters'
//  '<S67>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/N Gain/Passthrough'
//  '<S68>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/P Copy/Disabled'
//  '<S69>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/P Copy/External Parameters Ideal'
//  '<S70>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/P Copy/Internal Parameters Ideal'
//  '<S71>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Parallel P Gain/Disabled'
//  '<S72>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Parallel P Gain/External Parameters'
//  '<S73>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Parallel P Gain/Internal Parameters'
//  '<S74>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Parallel P Gain/Passthrough'
//  '<S75>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Reset Signal/Disabled'
//  '<S76>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Reset Signal/External Reset'
//  '<S77>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Saturation/Enabled'
//  '<S78>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Saturation/Passthrough'
//  '<S79>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Saturation Fdbk/Disabled'
//  '<S80>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Saturation Fdbk/Enabled'
//  '<S81>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Saturation Fdbk/Passthrough'
//  '<S82>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Sum/Passthrough_I'
//  '<S83>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Sum/Passthrough_P'
//  '<S84>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Sum/Sum_PD'
//  '<S85>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Sum/Sum_PI'
//  '<S86>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Sum/Sum_PID'
//  '<S87>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Sum Fdbk/Disabled'
//  '<S88>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Sum Fdbk/Enabled'
//  '<S89>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Sum Fdbk/Passthrough'
//  '<S90>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Tracking Mode/Disabled'
//  '<S91>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Tracking Mode/Enabled'
//  '<S92>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Tracking Mode Sum/Passthrough'
//  '<S93>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/Tracking Mode Sum/Tracking Mode'
//  '<S94>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/postSat Signal/Feedback_Path'
//  '<S95>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/postSat Signal/Forward_Path'
//  '<S96>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/preSat Signal/Feedback_Path'
//  '<S97>'  : 'discrete_pid_coderino_simu/Discrete PID Controller/preSat Signal/Forward_Path'

#endif                                 // RTW_HEADER_discrete_pid_coderino_simu_h_ 

//
// File trailer for generated code.
//
// [EOF]
//
