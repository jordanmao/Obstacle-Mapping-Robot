#include "main.h"

//MOTORS========================================================================
Motor leftDrive(LEFT_DRIVE_PORT,E_MOTOR_GEARSET_18,false,E_MOTOR_ENCODER_DEGREES);
Motor rightDrive(RIGHT_DRIVE_PORT,E_MOTOR_GEARSET_18,true,E_MOTOR_ENCODER_DEGREES);

//CONTROLLER====================================================================
Controller controller (E_CONTROLLER_MASTER);

//SENSORS=======================================================================
ADIGyro gyro(GYRO_PORT,0.1);
ADIUltrasonic ultrasonic(ULTRASONIC_PING,ULTRASONIC_ECHO);
ADIEncoder leftEncoder(LEFT_ENCODER_TOP,LEFT_ENCODER_BOTTOM,true);
ADIEncoder rightEncoder(RIGHT_ENCODER_TOP,RIGHT_ENCODER_BOTTOM,false);
//Ports-------------------------------------------------------------------------
#define LEFT_DRIVE_PORT 4
#define RIGHT_DRIVE_PORT 5
#define LEFT_ENCODER_TOP 'A'
#define LEFT_ENCODER_BOTTOM 'B'
#define ULTRASONIC_PING 'C'
#define ULTRASONIC_ECHO 'D'
#define GYRO_PORT 'E'
#define RIGHT_ENCODER_TOP 'G'
#define RIGHT_ENCODER_BOTTOM 'H'
