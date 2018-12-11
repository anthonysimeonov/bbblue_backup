/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: test_blink.h
 *
 * Code generated for Simulink model 'test_blink'.
 *
 * Model version                  : 1.1
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Tue Dec 11 05:58:54 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_test_blink_h_
#define RTW_HEADER_test_blink_h_
#include <math.h>
#include <stddef.h>
#include <string.h>
#ifndef test_blink_COMMON_INCLUDES_
# define test_blink_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "MW_bbblue_driver.h"
#endif                                 /* test_blink_COMMON_INCLUDES_ */

#include "test_blink_types.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block states (default storage) for system '<Root>' */
typedef struct {
  beagleboneblue_bbblueLED_test_T obj; /* '<Root>/LED' */
  int32_T clockTickCounter;            /* '<Root>/Pulse Generator' */
} DW_test_blink_T;

/* Parameters (default storage) */
struct P_test_blink_T_ {
  real_T PulseGenerator_Amp;           /* Expression: 1
                                        * Referenced by: '<Root>/Pulse Generator'
                                        */
  real_T PulseGenerator_Period;        /* Expression: 10
                                        * Referenced by: '<Root>/Pulse Generator'
                                        */
  real_T PulseGenerator_Duty;          /* Expression: 5
                                        * Referenced by: '<Root>/Pulse Generator'
                                        */
  real_T PulseGenerator_PhaseDelay;    /* Expression: 0
                                        * Referenced by: '<Root>/Pulse Generator'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_test_blink_T {
  const char_T *errorStatus;
};

/* Block parameters (default storage) */
extern P_test_blink_T test_blink_P;

/* Block states (default storage) */
extern DW_test_blink_T test_blink_DW;

/* Model entry point functions */
extern void test_blink_initialize(void);
extern void test_blink_step(void);
extern void test_blink_terminate(void);

/* Real-time Model object */
extern RT_MODEL_test_blink_T *const test_blink_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'test_blink'
 */
#endif                                 /* RTW_HEADER_test_blink_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
