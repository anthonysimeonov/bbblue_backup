#include <stdio.h>
#include <robotcontrol.h>

#define I2C_BUS 2
#define GPIO_INT_PIN_CHIP 3
#define GPIO_INT_PIN_PIN 21

static rc_mpu_data_t data;

void on_pause_press();
void on_pause_release();

int main(){
	rc_mpu_config_t conf = rc_mpu_default_config();
	conf.i2c_bus = I2C_BUS;
	conf.gpio_interrupt_pin_chip = GPIO_INT_PIN_CHIP;
	conf.gpio_interrupt_pin = GPIO_INT_PIN_PIN;

	if (rc_mpu_initialize_dmp(&data, conf)){
		printf("rc_mpu_initialize_failed\n");
		return -1;
	}

	if (rc_enable_signal_handler() == -1){
		fprintf(stderr, "ERROR: failed to start signal handler\n");
		return -1;
	}

	//init pause
	if (rc_button_init(RC_BTN_PIN_PAUSE, RC_BTN_POLARITY_NORM_HIGH, 
				RC_BTN_DEBOUNCE_DEFAULT_US)){
		fprintf(stderr, "ERROR: failed to initialize pause button\n");
		return -1;
	}

	rc_button_set_callbacks(RC_BTN_PIN_PAUSE, on_pause_press, on_pause_release);


	bool running = 1;
	rc_set_state(RUNNING);
	while (rc_get_state() == RUNNING){
		printf("%6.1f %6.1f %6.1f \n", 
				data.dmp_TaitBryan[0],
				data.dmp_TaitBryan[1],
				data.dmp_TaitBryan[2]
		      );
	}

	rc_mpu_power_off();
	fflush(stdout);
	return 0;
}

void on_pause_press(){
	rc_set_state(PAUSED);
}

void on_pause_release(){

}
