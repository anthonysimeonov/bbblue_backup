#include <stdio.h>
#include <robotcontrol.h>

#define FREQ 100 //Hz
#define MS_PER_SEC 1000
#define US_PER_SEC 1000000
#define GREEN 0
#define RED 1
#define ARR_SIZE 11

int duty_main = 20;
int duty_green = 0; //percent
int duty_red = 0;

int16_t total_time = 0;
int16_t onTimeMicros = 0;
int16_t offTimeMicros = 0;

int duties[ARR_SIZE] = {0, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100};

void pwm_led(int duty, int color);
void on_pause_press();
void on_pause_release();

int main(){       
	//signal handler, initialize PID, etc.
	if (rc_kill_existing_process(2.0)<-2) return -1;

	if (rc_button_init(RC_BTN_PIN_PAUSE, RC_BTN_POLARITY_NORM_HIGH,
				RC_BTN_DEBOUNCE_DEFAULT_US)){
		fprintf(stderr, "ERROR: failed to initialize pause button\n");
		return -1;
	}

	rc_button_set_callbacks(RC_BTN_PIN_PAUSE, on_pause_press, on_pause_release);
	rc_make_pid_file();

	int16_t total_time = (US_PER_SEC/FREQ);
	int j = 0;
	rc_set_state(RUNNING);

	while (rc_get_state() == RUNNING){
		rc_led_set(RC_LED_GREEN, 1);
		rc_usleep(total_time - j*j);
		rc_led_set(RC_LED_GREEN, 0);
		rc_usleep(j*j);
		j++;
		if (j%50 == 0){
			printf("blinking! \n", j);
		}
		if (j >= 100) j = 0;
	}
	
	/*
	int8_t i = 0;
	while (i < 10){
		pwm_led(duty_main, RED);
		i++;
		if (i%5 == 0){
			printf("blinking at %d  duty \n", duty_main);
			printf("i = %d\n", i);
		}
	}
	*/
	rc_led_set(RC_LED_GREEN, 0);
	rc_led_set(RC_LED_RED, 0);
	return 0;

}

void on_pause_press(){
	rc_set_state(PAUSED);
}

void on_pause_release(){
}

void pwm_led(int duty, int color){
	onTimeMicros = total_time - (US_PER_SEC * duty)/(FREQ * 100);
	offTimeMicros = total_time - onTimeMicros;

	if (color == GREEN){
		rc_led_set(RC_LED_GREEN, 1);
		rc_usleep(onTimeMicros);
		rc_led_set(RC_LED_GREEN, 0);
		rc_usleep(offTimeMicros);
	}
	else if (color == RED){
		rc_led_set(RC_LED_RED, 1);
		rc_usleep(onTimeMicros);
		rc_led_set(RC_LED_RED, 0);
		rc_usleep(offTimeMicros);
	}
}	
