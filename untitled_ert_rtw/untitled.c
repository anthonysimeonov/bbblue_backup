/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: untitled.c
 *
 * Code generated for Simulink model 'untitled'.
 *
 * Model version                  : 1.0
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Tue Dec 11 05:56:31 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "untitled.h"
#include "untitled_private.h"

/* Block states (default storage) */
DW_untitled_T untitled_DW;

/* Real-time model */
RT_MODEL_untitled_T untitled_M_;
RT_MODEL_untitled_T *const untitled_M = &untitled_M_;

/* Forward declaration for local functions */
static void untitled_SystemCore_release(const beagleboneblue_bbblueLED_unti_T
  *obj);
static void untitled_SystemCore_delete(const beagleboneblue_bbblueLED_unti_T
  *obj);
static void matlabCodegenHandle_matlabCodeg(beagleboneblue_bbblueLED_unti_T *obj);
static void untitled_SystemCore_release(const beagleboneblue_bbblueLED_unti_T
  *obj)
{
  if ((obj->isInitialized == 1) && obj->isSetupComplete) {
    rc_led_cleanup();
  }
}

static void untitled_SystemCore_delete(const beagleboneblue_bbblueLED_unti_T
  *obj)
{
  untitled_SystemCore_release(obj);
}

static void matlabCodegenHandle_matlabCodeg(beagleboneblue_bbblueLED_unti_T *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
    untitled_SystemCore_delete(obj);
  }
}

/* Model step function */
void untitled_step(void)
{
  real_T rtb_PulseGenerator;

  /* DiscretePulseGenerator: '<Root>/Pulse Generator' */
  rtb_PulseGenerator = (untitled_DW.clockTickCounter <
                        untitled_P.PulseGenerator_Duty) &&
    (untitled_DW.clockTickCounter >= 0) ? untitled_P.PulseGenerator_Amp : 0.0;
  if (untitled_DW.clockTickCounter >= untitled_P.PulseGenerator_Period - 1.0) {
    untitled_DW.clockTickCounter = 0;
  } else {
    untitled_DW.clockTickCounter++;
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
void untitled_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize error status */
  rtmSetErrorStatus(untitled_M, (NULL));

  /* states (dwork) */
  (void) memset((void *)&untitled_DW, 0,
                sizeof(DW_untitled_T));

  /* Start for MATLABSystem: '<Root>/LED' */
  untitled_DW.obj.matlabCodegenIsDeleted = true;
  untitled_DW.obj.isInitialized = 0;
  untitled_DW.obj.matlabCodegenIsDeleted = false;
  untitled_DW.obj.isSetupComplete = false;
  untitled_DW.obj.isInitialized = 1;
  untitled_DW.obj.isSetupComplete = true;

  /* InitializeConditions for DiscretePulseGenerator: '<Root>/Pulse Generator' */
  untitled_DW.clockTickCounter = 0;
}

/* Model terminate function */
void untitled_terminate(void)
{
  /* Terminate for MATLABSystem: '<Root>/LED' */
  matlabCodegenHandle_matlabCodeg(&untitled_DW.obj);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
