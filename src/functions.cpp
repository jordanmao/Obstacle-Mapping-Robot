#include "main.h"

//MOTORS========================================================================
void MoveForwards(){
    leftDrive.move_velocity(30);
    rightDrive.move_velocity(30);
}

void MoveBackwards(){
    leftDrive.move_velocity(-30);
    rightDrive.move_velocity(-30);
}

void TurnLeft(){
    leftDrive.move_velocity(-25);
    rightDrive.move_velocity(25);
}

void TurnRight(){
    leftDrive.move_velocity(25);
    rightDrive.move_velocity(-25);
}

void Brake(){
    leftDrive.move_velocity(0);
    rightDrive.move_velocity(0);
}

//MISCELLANEOUS=================================================================
float EncoderToDistance(int encoderDegrees){
    return encoderDegrees * (WHEEL_CIRCUMFERENCE/360);
}

float DegreesToRadians(float degrees){
    return degrees * (PI/180.0);
}

float ScaleGyroReading(float degrees){
    if(degrees >= 0){
        return 0.954 * degrees;
    }
    else{
        return 0.93 * degrees;
    }
}

void ResetEncoders(){
    leftEncoder.reset();
    rightEncoder.reset();
}

void UpdateRobotPosition(){
    robotYDelta = sinf(radians) * driveDistance;
    robotXDelta = cosf(radians) * driveDistance;
    robotX = robotXPrev + robotXDelta;
    robotY = robotYPrev + robotYDelta;
}

void UpdateObstaclePosition(){
    obstacleY = sinf(radians) * ultrasonicDistance;
    obstacleX = cosf(radians) * ultrasonicDistance;
    obstacleY += robotY;
    obstacleX += robotX;
}

void UpdateRobotPrevPosition(){
    robotXPrev = robotX;
    robotYPrev = robotY;
}
