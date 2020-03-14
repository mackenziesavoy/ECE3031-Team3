//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: discrete_pid.h
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
#ifndef RTW_HEADER_discrete_pid_h_
#define RTW_HEADER_discrete_pid_h_
#ifndef discrete_pid_COMMON_INCLUDES_
# define discrete_pid_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 // discrete_pid_COMMON_INCLUDES_

// Macros for accessing real-time model data structure

// Block signals and states (default storage) for system '<Root>'
typedef struct {
  int16_T UD_DSTATE;                   // '<S36>/UD'
  int16_T UD_DSTATE_p;                 // '<S132>/UD'
  int16_T Integrator_DSTATE;           // '<S57>/Integrator'
  int16_T Integrator_DSTATE_f;         // '<S153>/Integrator'
} DW;

// External inputs (root inport signals with default storage)
typedef struct {
  uint8_T Set_Point;                   // '<Root>/Set_Point '
  uint8_T ENC_Pos;                     // '<Root>/ENC_Pos'
  uint8_T ADC_VAL;                     // '<Root>/ADC_VAL'
} ExtU;

// External outputs (root outports fed by signals with default storage)
typedef struct {
  int16_T PID_OUT;                     // '<Root>/PID_OUT'
} ExtY;

// Class declaration for model discrete_pid
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
//  Block '<S36>/DTDup' : Unused code path elimination
//  Block '<S132>/DTDup' : Unused code path elimination


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
//  '<Root>' : 'discrete_pid'
//  '<S1>'   : 'discrete_pid/Discrete PID Controller'
//  '<S2>'   : 'discrete_pid/Discrete PID Controller1'
//  '<S3>'   : 'discrete_pid/Discrete PID Controller/Anti-windup'
//  '<S4>'   : 'discrete_pid/Discrete PID Controller/D Gain'
//  '<S5>'   : 'discrete_pid/Discrete PID Controller/Filter'
//  '<S6>'   : 'discrete_pid/Discrete PID Controller/Filter ICs'
//  '<S7>'   : 'discrete_pid/Discrete PID Controller/I Gain'
//  '<S8>'   : 'discrete_pid/Discrete PID Controller/Ideal P Gain'
//  '<S9>'   : 'discrete_pid/Discrete PID Controller/Ideal P Gain Fdbk'
//  '<S10>'  : 'discrete_pid/Discrete PID Controller/Integrator'
//  '<S11>'  : 'discrete_pid/Discrete PID Controller/Integrator ICs'
//  '<S12>'  : 'discrete_pid/Discrete PID Controller/N Copy'
//  '<S13>'  : 'discrete_pid/Discrete PID Controller/N Gain'
//  '<S14>'  : 'discrete_pid/Discrete PID Controller/P Copy'
//  '<S15>'  : 'discrete_pid/Discrete PID Controller/Parallel P Gain'
//  '<S16>'  : 'discrete_pid/Discrete PID Controller/Reset Signal'
//  '<S17>'  : 'discrete_pid/Discrete PID Controller/Saturation'
//  '<S18>'  : 'discrete_pid/Discrete PID Controller/Saturation Fdbk'
//  '<S19>'  : 'discrete_pid/Discrete PID Controller/Sum'
//  '<S20>'  : 'discrete_pid/Discrete PID Controller/Sum Fdbk'
//  '<S21>'  : 'discrete_pid/Discrete PID Controller/Tracking Mode'
//  '<S22>'  : 'discrete_pid/Discrete PID Controller/Tracking Mode Sum'
//  '<S23>'  : 'discrete_pid/Discrete PID Controller/postSat Signal'
//  '<S24>'  : 'discrete_pid/Discrete PID Controller/preSat Signal'
//  '<S25>'  : 'discrete_pid/Discrete PID Controller/Anti-windup/Back Calculation'
//  '<S26>'  : 'discrete_pid/Discrete PID Controller/Anti-windup/Cont. Clamping Ideal'
//  '<S27>'  : 'discrete_pid/Discrete PID Controller/Anti-windup/Cont. Clamping Parallel'
//  '<S28>'  : 'discrete_pid/Discrete PID Controller/Anti-windup/Disabled'
//  '<S29>'  : 'discrete_pid/Discrete PID Controller/Anti-windup/Disc. Clamping Ideal'
//  '<S30>'  : 'discrete_pid/Discrete PID Controller/Anti-windup/Disc. Clamping Parallel'
//  '<S31>'  : 'discrete_pid/Discrete PID Controller/Anti-windup/Passthrough'
//  '<S32>'  : 'discrete_pid/Discrete PID Controller/D Gain/Disabled'
//  '<S33>'  : 'discrete_pid/Discrete PID Controller/D Gain/External Parameters'
//  '<S34>'  : 'discrete_pid/Discrete PID Controller/D Gain/Internal Parameters'
//  '<S35>'  : 'discrete_pid/Discrete PID Controller/Filter/Cont. Filter'
//  '<S36>'  : 'discrete_pid/Discrete PID Controller/Filter/Differentiator'
//  '<S37>'  : 'discrete_pid/Discrete PID Controller/Filter/Disabled'
//  '<S38>'  : 'discrete_pid/Discrete PID Controller/Filter/Disc. Backward Euler Filter'
//  '<S39>'  : 'discrete_pid/Discrete PID Controller/Filter/Disc. Forward Euler Filter'
//  '<S40>'  : 'discrete_pid/Discrete PID Controller/Filter/Disc. Trapezoidal Filter'
//  '<S41>'  : 'discrete_pid/Discrete PID Controller/Filter ICs/Disabled'
//  '<S42>'  : 'discrete_pid/Discrete PID Controller/Filter ICs/External IC'
//  '<S43>'  : 'discrete_pid/Discrete PID Controller/Filter ICs/Internal IC - Differentiator'
//  '<S44>'  : 'discrete_pid/Discrete PID Controller/Filter ICs/Internal IC - Filter'
//  '<S45>'  : 'discrete_pid/Discrete PID Controller/I Gain/Disabled'
//  '<S46>'  : 'discrete_pid/Discrete PID Controller/I Gain/External Parameters'
//  '<S47>'  : 'discrete_pid/Discrete PID Controller/I Gain/Internal Parameters'
//  '<S48>'  : 'discrete_pid/Discrete PID Controller/Ideal P Gain/External Parameters'
//  '<S49>'  : 'discrete_pid/Discrete PID Controller/Ideal P Gain/Internal Parameters'
//  '<S50>'  : 'discrete_pid/Discrete PID Controller/Ideal P Gain/Passthrough'
//  '<S51>'  : 'discrete_pid/Discrete PID Controller/Ideal P Gain Fdbk/Disabled'
//  '<S52>'  : 'discrete_pid/Discrete PID Controller/Ideal P Gain Fdbk/External Parameters'
//  '<S53>'  : 'discrete_pid/Discrete PID Controller/Ideal P Gain Fdbk/Internal Parameters'
//  '<S54>'  : 'discrete_pid/Discrete PID Controller/Ideal P Gain Fdbk/Passthrough'
//  '<S55>'  : 'discrete_pid/Discrete PID Controller/Integrator/Continuous'
//  '<S56>'  : 'discrete_pid/Discrete PID Controller/Integrator/Disabled'
//  '<S57>'  : 'discrete_pid/Discrete PID Controller/Integrator/Discrete'
//  '<S58>'  : 'discrete_pid/Discrete PID Controller/Integrator ICs/Disabled'
//  '<S59>'  : 'discrete_pid/Discrete PID Controller/Integrator ICs/External IC'
//  '<S60>'  : 'discrete_pid/Discrete PID Controller/Integrator ICs/Internal IC'
//  '<S61>'  : 'discrete_pid/Discrete PID Controller/N Copy/Disabled'
//  '<S62>'  : 'discrete_pid/Discrete PID Controller/N Copy/Disabled wSignal Specification'
//  '<S63>'  : 'discrete_pid/Discrete PID Controller/N Copy/External Parameters'
//  '<S64>'  : 'discrete_pid/Discrete PID Controller/N Copy/Internal Parameters'
//  '<S65>'  : 'discrete_pid/Discrete PID Controller/N Gain/Disabled'
//  '<S66>'  : 'discrete_pid/Discrete PID Controller/N Gain/External Parameters'
//  '<S67>'  : 'discrete_pid/Discrete PID Controller/N Gain/Internal Parameters'
//  '<S68>'  : 'discrete_pid/Discrete PID Controller/N Gain/Passthrough'
//  '<S69>'  : 'discrete_pid/Discrete PID Controller/P Copy/Disabled'
//  '<S70>'  : 'discrete_pid/Discrete PID Controller/P Copy/External Parameters Ideal'
//  '<S71>'  : 'discrete_pid/Discrete PID Controller/P Copy/Internal Parameters Ideal'
//  '<S72>'  : 'discrete_pid/Discrete PID Controller/Parallel P Gain/Disabled'
//  '<S73>'  : 'discrete_pid/Discrete PID Controller/Parallel P Gain/External Parameters'
//  '<S74>'  : 'discrete_pid/Discrete PID Controller/Parallel P Gain/Internal Parameters'
//  '<S75>'  : 'discrete_pid/Discrete PID Controller/Parallel P Gain/Passthrough'
//  '<S76>'  : 'discrete_pid/Discrete PID Controller/Reset Signal/Disabled'
//  '<S77>'  : 'discrete_pid/Discrete PID Controller/Reset Signal/External Reset'
//  '<S78>'  : 'discrete_pid/Discrete PID Controller/Saturation/Enabled'
//  '<S79>'  : 'discrete_pid/Discrete PID Controller/Saturation/Passthrough'
//  '<S80>'  : 'discrete_pid/Discrete PID Controller/Saturation Fdbk/Disabled'
//  '<S81>'  : 'discrete_pid/Discrete PID Controller/Saturation Fdbk/Enabled'
//  '<S82>'  : 'discrete_pid/Discrete PID Controller/Saturation Fdbk/Passthrough'
//  '<S83>'  : 'discrete_pid/Discrete PID Controller/Sum/Passthrough_I'
//  '<S84>'  : 'discrete_pid/Discrete PID Controller/Sum/Passthrough_P'
//  '<S85>'  : 'discrete_pid/Discrete PID Controller/Sum/Sum_PD'
//  '<S86>'  : 'discrete_pid/Discrete PID Controller/Sum/Sum_PI'
//  '<S87>'  : 'discrete_pid/Discrete PID Controller/Sum/Sum_PID'
//  '<S88>'  : 'discrete_pid/Discrete PID Controller/Sum Fdbk/Disabled'
//  '<S89>'  : 'discrete_pid/Discrete PID Controller/Sum Fdbk/Enabled'
//  '<S90>'  : 'discrete_pid/Discrete PID Controller/Sum Fdbk/Passthrough'
//  '<S91>'  : 'discrete_pid/Discrete PID Controller/Tracking Mode/Disabled'
//  '<S92>'  : 'discrete_pid/Discrete PID Controller/Tracking Mode/Enabled'
//  '<S93>'  : 'discrete_pid/Discrete PID Controller/Tracking Mode Sum/Passthrough'
//  '<S94>'  : 'discrete_pid/Discrete PID Controller/Tracking Mode Sum/Tracking Mode'
//  '<S95>'  : 'discrete_pid/Discrete PID Controller/postSat Signal/Feedback_Path'
//  '<S96>'  : 'discrete_pid/Discrete PID Controller/postSat Signal/Forward_Path'
//  '<S97>'  : 'discrete_pid/Discrete PID Controller/preSat Signal/Feedback_Path'
//  '<S98>'  : 'discrete_pid/Discrete PID Controller/preSat Signal/Forward_Path'
//  '<S99>'  : 'discrete_pid/Discrete PID Controller1/Anti-windup'
//  '<S100>' : 'discrete_pid/Discrete PID Controller1/D Gain'
//  '<S101>' : 'discrete_pid/Discrete PID Controller1/Filter'
//  '<S102>' : 'discrete_pid/Discrete PID Controller1/Filter ICs'
//  '<S103>' : 'discrete_pid/Discrete PID Controller1/I Gain'
//  '<S104>' : 'discrete_pid/Discrete PID Controller1/Ideal P Gain'
//  '<S105>' : 'discrete_pid/Discrete PID Controller1/Ideal P Gain Fdbk'
//  '<S106>' : 'discrete_pid/Discrete PID Controller1/Integrator'
//  '<S107>' : 'discrete_pid/Discrete PID Controller1/Integrator ICs'
//  '<S108>' : 'discrete_pid/Discrete PID Controller1/N Copy'
//  '<S109>' : 'discrete_pid/Discrete PID Controller1/N Gain'
//  '<S110>' : 'discrete_pid/Discrete PID Controller1/P Copy'
//  '<S111>' : 'discrete_pid/Discrete PID Controller1/Parallel P Gain'
//  '<S112>' : 'discrete_pid/Discrete PID Controller1/Reset Signal'
//  '<S113>' : 'discrete_pid/Discrete PID Controller1/Saturation'
//  '<S114>' : 'discrete_pid/Discrete PID Controller1/Saturation Fdbk'
//  '<S115>' : 'discrete_pid/Discrete PID Controller1/Sum'
//  '<S116>' : 'discrete_pid/Discrete PID Controller1/Sum Fdbk'
//  '<S117>' : 'discrete_pid/Discrete PID Controller1/Tracking Mode'
//  '<S118>' : 'discrete_pid/Discrete PID Controller1/Tracking Mode Sum'
//  '<S119>' : 'discrete_pid/Discrete PID Controller1/postSat Signal'
//  '<S120>' : 'discrete_pid/Discrete PID Controller1/preSat Signal'
//  '<S121>' : 'discrete_pid/Discrete PID Controller1/Anti-windup/Back Calculation'
//  '<S122>' : 'discrete_pid/Discrete PID Controller1/Anti-windup/Cont. Clamping Ideal'
//  '<S123>' : 'discrete_pid/Discrete PID Controller1/Anti-windup/Cont. Clamping Parallel'
//  '<S124>' : 'discrete_pid/Discrete PID Controller1/Anti-windup/Disabled'
//  '<S125>' : 'discrete_pid/Discrete PID Controller1/Anti-windup/Disc. Clamping Ideal'
//  '<S126>' : 'discrete_pid/Discrete PID Controller1/Anti-windup/Disc. Clamping Parallel'
//  '<S127>' : 'discrete_pid/Discrete PID Controller1/Anti-windup/Passthrough'
//  '<S128>' : 'discrete_pid/Discrete PID Controller1/D Gain/Disabled'
//  '<S129>' : 'discrete_pid/Discrete PID Controller1/D Gain/External Parameters'
//  '<S130>' : 'discrete_pid/Discrete PID Controller1/D Gain/Internal Parameters'
//  '<S131>' : 'discrete_pid/Discrete PID Controller1/Filter/Cont. Filter'
//  '<S132>' : 'discrete_pid/Discrete PID Controller1/Filter/Differentiator'
//  '<S133>' : 'discrete_pid/Discrete PID Controller1/Filter/Disabled'
//  '<S134>' : 'discrete_pid/Discrete PID Controller1/Filter/Disc. Backward Euler Filter'
//  '<S135>' : 'discrete_pid/Discrete PID Controller1/Filter/Disc. Forward Euler Filter'
//  '<S136>' : 'discrete_pid/Discrete PID Controller1/Filter/Disc. Trapezoidal Filter'
//  '<S137>' : 'discrete_pid/Discrete PID Controller1/Filter ICs/Disabled'
//  '<S138>' : 'discrete_pid/Discrete PID Controller1/Filter ICs/External IC'
//  '<S139>' : 'discrete_pid/Discrete PID Controller1/Filter ICs/Internal IC - Differentiator'
//  '<S140>' : 'discrete_pid/Discrete PID Controller1/Filter ICs/Internal IC - Filter'
//  '<S141>' : 'discrete_pid/Discrete PID Controller1/I Gain/Disabled'
//  '<S142>' : 'discrete_pid/Discrete PID Controller1/I Gain/External Parameters'
//  '<S143>' : 'discrete_pid/Discrete PID Controller1/I Gain/Internal Parameters'
//  '<S144>' : 'discrete_pid/Discrete PID Controller1/Ideal P Gain/External Parameters'
//  '<S145>' : 'discrete_pid/Discrete PID Controller1/Ideal P Gain/Internal Parameters'
//  '<S146>' : 'discrete_pid/Discrete PID Controller1/Ideal P Gain/Passthrough'
//  '<S147>' : 'discrete_pid/Discrete PID Controller1/Ideal P Gain Fdbk/Disabled'
//  '<S148>' : 'discrete_pid/Discrete PID Controller1/Ideal P Gain Fdbk/External Parameters'
//  '<S149>' : 'discrete_pid/Discrete PID Controller1/Ideal P Gain Fdbk/Internal Parameters'
//  '<S150>' : 'discrete_pid/Discrete PID Controller1/Ideal P Gain Fdbk/Passthrough'
//  '<S151>' : 'discrete_pid/Discrete PID Controller1/Integrator/Continuous'
//  '<S152>' : 'discrete_pid/Discrete PID Controller1/Integrator/Disabled'
//  '<S153>' : 'discrete_pid/Discrete PID Controller1/Integrator/Discrete'
//  '<S154>' : 'discrete_pid/Discrete PID Controller1/Integrator ICs/Disabled'
//  '<S155>' : 'discrete_pid/Discrete PID Controller1/Integrator ICs/External IC'
//  '<S156>' : 'discrete_pid/Discrete PID Controller1/Integrator ICs/Internal IC'
//  '<S157>' : 'discrete_pid/Discrete PID Controller1/N Copy/Disabled'
//  '<S158>' : 'discrete_pid/Discrete PID Controller1/N Copy/Disabled wSignal Specification'
//  '<S159>' : 'discrete_pid/Discrete PID Controller1/N Copy/External Parameters'
//  '<S160>' : 'discrete_pid/Discrete PID Controller1/N Copy/Internal Parameters'
//  '<S161>' : 'discrete_pid/Discrete PID Controller1/N Gain/Disabled'
//  '<S162>' : 'discrete_pid/Discrete PID Controller1/N Gain/External Parameters'
//  '<S163>' : 'discrete_pid/Discrete PID Controller1/N Gain/Internal Parameters'
//  '<S164>' : 'discrete_pid/Discrete PID Controller1/N Gain/Passthrough'
//  '<S165>' : 'discrete_pid/Discrete PID Controller1/P Copy/Disabled'
//  '<S166>' : 'discrete_pid/Discrete PID Controller1/P Copy/External Parameters Ideal'
//  '<S167>' : 'discrete_pid/Discrete PID Controller1/P Copy/Internal Parameters Ideal'
//  '<S168>' : 'discrete_pid/Discrete PID Controller1/Parallel P Gain/Disabled'
//  '<S169>' : 'discrete_pid/Discrete PID Controller1/Parallel P Gain/External Parameters'
//  '<S170>' : 'discrete_pid/Discrete PID Controller1/Parallel P Gain/Internal Parameters'
//  '<S171>' : 'discrete_pid/Discrete PID Controller1/Parallel P Gain/Passthrough'
//  '<S172>' : 'discrete_pid/Discrete PID Controller1/Reset Signal/Disabled'
//  '<S173>' : 'discrete_pid/Discrete PID Controller1/Reset Signal/External Reset'
//  '<S174>' : 'discrete_pid/Discrete PID Controller1/Saturation/Enabled'
//  '<S175>' : 'discrete_pid/Discrete PID Controller1/Saturation/Passthrough'
//  '<S176>' : 'discrete_pid/Discrete PID Controller1/Saturation Fdbk/Disabled'
//  '<S177>' : 'discrete_pid/Discrete PID Controller1/Saturation Fdbk/Enabled'
//  '<S178>' : 'discrete_pid/Discrete PID Controller1/Saturation Fdbk/Passthrough'
//  '<S179>' : 'discrete_pid/Discrete PID Controller1/Sum/Passthrough_I'
//  '<S180>' : 'discrete_pid/Discrete PID Controller1/Sum/Passthrough_P'
//  '<S181>' : 'discrete_pid/Discrete PID Controller1/Sum/Sum_PD'
//  '<S182>' : 'discrete_pid/Discrete PID Controller1/Sum/Sum_PI'
//  '<S183>' : 'discrete_pid/Discrete PID Controller1/Sum/Sum_PID'
//  '<S184>' : 'discrete_pid/Discrete PID Controller1/Sum Fdbk/Disabled'
//  '<S185>' : 'discrete_pid/Discrete PID Controller1/Sum Fdbk/Enabled'
//  '<S186>' : 'discrete_pid/Discrete PID Controller1/Sum Fdbk/Passthrough'
//  '<S187>' : 'discrete_pid/Discrete PID Controller1/Tracking Mode/Disabled'
//  '<S188>' : 'discrete_pid/Discrete PID Controller1/Tracking Mode/Enabled'
//  '<S189>' : 'discrete_pid/Discrete PID Controller1/Tracking Mode Sum/Passthrough'
//  '<S190>' : 'discrete_pid/Discrete PID Controller1/Tracking Mode Sum/Tracking Mode'
//  '<S191>' : 'discrete_pid/Discrete PID Controller1/postSat Signal/Feedback_Path'
//  '<S192>' : 'discrete_pid/Discrete PID Controller1/postSat Signal/Forward_Path'
//  '<S193>' : 'discrete_pid/Discrete PID Controller1/preSat Signal/Feedback_Path'
//  '<S194>' : 'discrete_pid/Discrete PID Controller1/preSat Signal/Forward_Path'

#endif                                 // RTW_HEADER_discrete_pid_h_

//
// File trailer for generated code.
//
// [EOF]
//
