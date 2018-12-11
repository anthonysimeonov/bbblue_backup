/* Copyright 2017 The MathWorks, Inc. */

#ifndef MW_DRIVER_BBBLUE_H
#define MW_DRIVER_BBBLUE_H

#if ( defined(MATLAB_MEX_FILE) || defined(RSIM_PARAMETER_LOADING) ||  defined(RSIM_WITH_SL_SOLVER) )
/* This will be run in Rapid Accelerator Mode */

/* Button */
#define rc_button_init(a,b,c,d) (0)
#define rc_button_get_state(a,b) (0)
#define rc_button_cleanup() (0)

/*LED*/
#define rc_led_set(a,b)(0)
#define rc_led_cleanup() (0)

/* Encoder */
#define getEncoderValue(a,b,c) (0)

/*Motors*/
#define MW_set_motor(a,b,c) (0)
#define MW_terminate_motor(a) (0)

/* Servo */
#define rc_servo_send_pulse_normalized(a,b) (0)

/*ADC*/
#define rc_adc_init() (0)
#define rc_adc_read_raw(a) (0)
#define rc_adc_read_volt(a) (0)
#define rc_battery_voltage() (0)
#define rc_dc_jack_voltage() (0)
#define rc_adc_cleanup() (0)

#else

#include "rc/adc.h"
#include "rc/led.h"
#include "rc/button.h"
#include "rtwtypes.h"

/* Button*/
int rc_button_init(int chip, int pin, char polarity, int debounce_us);
int rc_button_get_state(int chip, int pin);
void rc_button_cleanup(void);

/*LED*/
extern int rc_led_set(rc_led_t led, int state);
extern void rc_led_cleanup();

/* Encoder */
int32_T getEncoderValue(uint8_T portNumber, uint8_T mode, int8_T in);

/*Motors*/
void MW_set_motor(uint8_T index, int8_T duty, uint8_T stopAction);
void MW_terminate_motor(uint8_T stopAction);

/*Servo*/
extern int rc_servo_send_pulse_normalized(int ch, double input);

/*ADC*/
extern int rc_adc_init();
extern int rc_adc_read_raw(int ch);
extern double rc_adc_read_volt(int ch);
extern double rc_adc_batt();
extern double rc_adc_dc_jack();
extern int rc_adc_cleanup();

#endif


#endif
