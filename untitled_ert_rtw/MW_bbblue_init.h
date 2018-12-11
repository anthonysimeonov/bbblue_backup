/* Copyright 2017 The MathWorks, Inc. */

#ifndef _MW_BBBLUE_INIT_H_
#define _MW_BBBLUE_INIT_H_

#if ( defined(MATLAB_MEX_FILE) || defined(RSIM_PARAMETER_LOADING) ||  defined(RSIM_WITH_SL_SOLVER) )
#define MW_bbblue_init() (0)
#define MW_bbblue_terminate() (0)
#else
#ifdef __cplusplus
extern "C"
{
#endif
    void MW_bbblue_init();
    void MW_bbblue_terminate(); 
#ifdef __cplusplus
}
#endif
#endif
#endif