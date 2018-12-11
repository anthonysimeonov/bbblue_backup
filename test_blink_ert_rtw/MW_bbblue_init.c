/* Copyright 2018 The MathWorks, Inc. */

/**************************************
 *  BeagleBone Blue Init Sequence  *
 **************************************/

#include "MW_bbblue_init.h"
#include "rc/motor.h"
#include "rc/servo.h"

void MW_bbblue_init()
{
#ifdef _RTT_DCMOTOR_INUSE_
    rc_motor_init();
#endif
    
#ifdef _RTT_SERVOMOTOR_INUSE_
    rc_servo_init();
    rc_servo_power_rail_en(1);
#endif
    
#ifdef _RTT_ENCODER_INUSE_
    rc_encoder_init();
#endif    
}

void MW_bbblue_terminate()
{    
#ifdef _RTT_DCMOTOR_INUSE_
    rc_motor_cleanup();
#endif
    
#ifdef _RTT_SERVOMOTOR_INUSE_
    rc_servo_power_rail_en(0);
    rc_servo_cleanup();
#endif
    
#ifdef _RTT_ENCODER_INUSE_
    rc_encoder_cleanup();
#endif  
}