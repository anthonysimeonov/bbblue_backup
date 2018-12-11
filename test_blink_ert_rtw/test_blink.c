/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: test_blink.c
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

#include "test_blink.h"
#include "test_blink_private.h"

/* Block states (default storage) */
DW_test_blink_T test_blink_DW;

/* Real-time model */
RT_MODEL_test_blink_T test_blink_M_;
RT_MODEL_test_blink_T *const test_blink_M = &test_blink_M_;

/* Forward declaration for local functions */
static void test_blink_SystemCore_release(const beagleboneblue_bbblueLED_test_T *
  obj);
static void test_blink_SystemCore_delete(const beagleboneblue_bbblueLED_test_T
  *obj);
static void matlabCodegenHandle_matlabCodeg(beagleboneblue_bbblueLED_test_T *obj);
static void test_blink_SystemCore_release(const beagleboneblue_bbblueLED_test_T *
  obj)
{
  if ((obj->isInitialized == 1) && obj->isSetupComplete) {
    rc_led_cleanup();
  }
}

static void test_blink_SystemCore_delete(const beagleboneblue_bbblueLED_test_T
  *obj)
{
  test_blink_SystemCore_release(obj);
}

static void matlabCodegenHandle_matlabCodeg(beagleboneblue_bbblueLED_test_T *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
    test_blink_SystemCore_delete(obj);
  }
}

/* Model step function */
void test_blink_step(void)
{
  real_T rtb_PulseGenerator;

  /* DiscretePulseGenerator: '<Root>/Pulse Generator' */
  rtb_PulseGenerator = (test_blink_DW.clockTickCounter <
                        test_blink_P.PulseGenerator_Duty) &&
    (test_blink_DW.clockTickCounter >= 0) ? test_blink_P.PulseGenerator_Amp :
    0.0;
  if (test_blink_DW.clockTickCounter >= test_blink_P.PulseGenerator_Period - 1.0)
  {
    test_blink_DW.clockTickCounter = 0;
  } else {
    test_blink_DW.clockTickCounter++;
  }

  /* End of DiscretePulseGenerator: '<Root>/Pulse Generator' */

  /* DataTypeConversion: '<Root>/Data Type Conversion' */
  rtb_PulseGenerator = floor(rtb_PulseGenerator);
  if (rtIsNaN(rtb_PulseGenerator) || rtIsInf(rtb_PulseGenerator)) {
    rtb_PulseGenerator = 0.0;
  } else {
    rtb_PulseGenerator = fmod(rtb_PulseGenerator, 256.0);
  }

  /* MATLABSystem: '<Root>/LED' incorporates:
   *  DataTypeConversion: '<Root>/Data Type Conversion'
   */
  rc_led_set(0, (uint8_T)(rtb_PulseGenerator < 0.0 ? (int32_T)(uint8_T)-(int8_T)
              (uint8_T)-rtb_PulseGenerator : (int32_T)(uint8_T)
              rtb_PulseGenerator));
}

/* Model initialize function */
void test_blink_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize error status */
  rtmSetErrorStatus(test_blink_M, (NULL));

  /* states (dwork) */
  (void) memset((void *)&test_blink_DW, 0,
                sizeof(DW_test_blink_T));

  /* Start for MATLABSystem: '<Root>/LED' */
  test_blink_DW.obj.matlabCodegenIsDeleted = true;
  test_blink_DW.obj.isInitialized = 0;
  test_blink_DW.obj.matlabCodegenIsDeleted = false;
  test_blink_DW.obj.isSetupComplete = false;
  test_blink_DW.obj.isInitialized = 1;
  test_blink_DW.obj.isSetupComplete = true;

  /* InitializeConditions for DiscretePulseGenerator: '<Root>/Pulse Generator' */
  test_blink_DW.clockTickCounter = 0;
}

/* Model terminate function */
void test_blink_terminate(void)
{
  /* Terminate for MATLABSystem: '<Root>/LED' */
  matlabCodegenHandle_matlabCodeg(&test_blink_DW.obj);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
