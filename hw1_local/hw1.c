// gcc anthony_simeonov_HW1.c -o anthony_simeonov_HW1.o -l:librobotcontrol.so.1        

#include <stdio.h>
#include <robotcontrol.h>

#define I2C_BUS 2
#define GPIO_INT_PIN_CHIP 3
#define GPIO_INT_PIN_PIN 21
#define GREEN 0
#define RED 1
#define PI 3.1415926
#define MAX_INTENSITY 100
#define ROLL_INDEX 1

static rc_mpu_data_t data;

void on_pause_press();
void on_pause_release();

int main(){
	printf("Anthony Simeonov \r\n");
	rc_mpu_config_t conf = rc_mpu_default_config();
	conf.i2c_bus = I2C_BUS;
	conf.gpio_interrupt_pin_chip = GPIO_INT_PIN_CHIP;
	conf.gpio_interrupt_pin = GPIO_INT_PIN_PIN;

	if (rc_enable_signal_handler() == -1){
		fprintf(stderr, "ERROR: failed to start signal handler\n");
		return -1;
	}

	if (rc_button_init(RC_BTN_PIN_PAUSE, RC_BTN_POLARITY_NORM_HIGH,
				RC_BTN_DEBOUNCE_DEFAULT_US)){
		fprintf(stderr, "ERROR: failed to initialize pause button\n");
		return -1;
	}

	if (rc_mpu_initialize_dmp(&data, conf)){
		printf("rc_mpu_initialize failed\n");
		return -1;
	}

	rc_button_set_callbacks(RC_BTN_PIN_PAUSE, on_pause_press, on_pause_release);

	rc_set_state(RUNNING);
	int counter = 0;
	float angle = 0;
	int intensity = 0; //unit is sqrt(microseconds)
	int red_intensity = 0;
	int green_intensity = 0;
	while (rc_get_state() == RUNNING){
		// get angles
		angle = data.dmp_TaitBryan[ROLL_INDEX]; 

		// map angles to intensity and color
		intensity = (int) (angle * MAX_INTENSITY * 2 / PI);
		if (intensity > MAX_INTENSITY){
			intensity = MAX_INTENSITY;
		}

		// blink at mapped intensity and color
		if (angle < 0){
			green_intensity = intensity * intensity;
			red_intensity = 0;
			rc_led_set(RC_LED_GREEN, 1);
			rc_usleep(green_intensity);
			rc_led_set(RC_LED_GREEN, 0);
			rc_usleep(10000 - green_intensity);
		}
		else {
			red_intensity = intensity * intensity;
			green_intensity = 0;
			rc_led_set(RC_LED_RED, 1);
			rc_usleep(red_intensity);
			rc_led_set(RC_LED_RED, 0);
			rc_usleep(10000 - red_intensity);
		}
		printf("Red intensity: %1.3f,   Green intensity: %1.3f \r\n", (red_intensity/10000.0), (green_intensity/10000.0));
		//printf("Angle:  %f \r\n", angle);		
		counter ++;
	}

	rc_led_set(RC_LED_GREEN, 0);
	rc_led_set(RC_LED_RED, 0);
	return 0;
}

void on_pause_press(){
	rc_set_state(PAUSED);
}

void on_pause_release(){

}


