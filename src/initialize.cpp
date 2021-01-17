#include "main.h"
#include "DisplayTest/lv_tutorial_hello_world.h"
void initialize() {
    //LCD DISPLAY===============================================================
    lcd::initialize();
	//MOTORS====================================================================
	leftDrive.set_brake_mode(MOTOR_BRAKE_HOLD);
	rightDrive.set_brake_mode(MOTOR_BRAKE_HOLD);
}
