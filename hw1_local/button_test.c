#include <stdio.h>
#include <robotcontrol.h>

void on_pause_press();
void on_pause_release();

int main(){
	//make sure another instance is not running
	if (rc_kill_existing_process(2.0)<-2) return -1;

	//clean exiting with signal handler
	if (rc_enable_signal_handler()==-1){
		fprintf(stderr, "ERROR: failed to start signal handler\n");
		return -1;
	}

	//init button
	if (rc_button_init(RC_BTN_PIN_PAUSE, RC_BTN_POLARITY_NORM_HIGH,
				RC_BTN_DEBOUNCE_DEFAULT_US)){
		fprintf(stderr, "ERROR: failed to initialize pause button\n");
		return -1;
	}

	//assign button callback functions
	rc_button_set_callbacks(RC_BTN_PIN_PAUSE, on_pause_press, on_pause_release);

	//make process ID file
	rc_make_pid_file();

	//log until state changes to EXITING
	rc_set_state(RUNNING);

	//count how many times we switch
	int switches = 0;
	bool state = 1;
	bool last_state = 1;
	while(rc_get_state()!=EXITING){
		//do stuff with the button
		state = (rc_get_state() == RUNNING);
		if (state != last_state){
			switches += 1;
			printf("switches:  %d\n", switches);
		}
		if (switches >= 5){
			printf("exiting after 5 switches\n");
			return 0;
		}
		last_state = state;		
	}
}

void on_pause_release(){
	if(rc_get_state()==RUNNING){
		printf("Pausing program\n");       
		rc_set_state(PAUSED);
	}
	else if(rc_get_state()==PAUSED) {
		printf("Running program\n");
		rc_set_state(RUNNING);
	}
	return;
}

void on_pause_press(){
	bool pressed = 1;
	while(pressed){
		printf("Pause button being held\n");
		rc_usleep(500000);

		//check if still being pressed
		pressed = !(rc_button_get_state(RC_BTN_PIN_PAUSE) == RC_BTN_STATE_RELEASED);
	}

	return;
}
