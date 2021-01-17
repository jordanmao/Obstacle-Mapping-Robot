#include "main.h"

float radians = 0;
float angle = 0;
int ultrasonicDistance = 0;
int leftDriveDegrees = 0;
int rightDriveDegrees = 0;
float averageDriveDegrees = 0;
float driveDistance;
float robotX = 0;
float robotY = 0;
float robotXPrev = 0;
float robotYPrev = 0;
float robotXDelta = 0;
float robotYDelta = 0;
float obstacleX = 0;
float obstacleY = 0;

void opcontrol() {
    tuple <int,int> coordinate; //(x,y)
    coordinate = make_tuple(0,0); //Assigns values to the tuple
    map < tuple<int,int> , bool > robotPath; //Make a map that contains coordinates of the robot's path
    map < tuple<int,int> , bool > obstacles; //map for obstacles
    ResetEncoders();
    while(true){
        //SENSORS===============================================================
        //Gyro Sensor:
        angle = gyro.get_value();
        angle = ScaleGyroReading(angle);
        if (angle != 0){
            angle = -angle; //If it was -0 at the beginning, it would mess up the position calculations at the start
        }
        radians = DegreesToRadians(angle);
        //Ultrasonic Sensor:
        ultrasonicDistance = ultrasonic.get_value()/10 + 14; //distance in cm (+14 because sensor is 14 cm from center of robot)
        //Quadrature Encoders:
        leftDriveDegrees = leftEncoder.get_value();
        rightDriveDegrees = rightEncoder.get_value();
        averageDriveDegrees = (leftDriveDegrees + rightDriveDegrees)/2;
        driveDistance = EncoderToDistance(averageDriveDegrees);

        //CONTROLLING THE DRIVE=================================================
        if(controller.get_digital(E_CONTROLLER_DIGITAL_LEFT)){ //LEFT button pressed -> turn lef
            TurnLeft();
            ResetEncoders();
            UpdateRobotPrevPosition();
            if(ultrasonicDistance > ULTRASONIC_MIN && ultrasonicDistance < ULTRASONIC_MAX){
                UpdateObstaclePosition();
                get<0>(coordinate) = obstacleX; //Use get() to change alues of tuple
                get<1>(coordinate) = -obstacleY;
                obstacles[coordinate] = true;
            }
        }
        else if(controller.get_digital(E_CONTROLLER_DIGITAL_RIGHT)){ //RIGHT button pressed -> turn right
            TurnRight();
            ResetEncoders();
            UpdateRobotPrevPosition();
            if(ultrasonicDistance > ULTRASONIC_MIN && ultrasonicDistance < ULTRASONIC_MAX){
                UpdateObstaclePosition();
                get<0>(coordinate) = obstacleX;
                get<1>(coordinate) = -obstacleY;
                obstacles[coordinate] = true;
            }
        }
        else if(controller.get_digital(E_CONTROLLER_DIGITAL_UP)){ //UP button pressed -> move forwards
            MoveForwards();
            UpdateRobotPosition();
            if(ultrasonicDistance > ULTRASONIC_MIN && ultrasonicDistance < ULTRASONIC_MAX){
                UpdateObstaclePosition();
                get<0>(coordinate) = obstacleX;
                get<1>(coordinate) = -obstacleY;
                obstacles[coordinate] = true;
            }
        }
        else if(controller.get_digital(E_CONTROLLER_DIGITAL_DOWN)){ //DOWN button pressed -> move backwards
            MoveBackwards();
            UpdateRobotPosition();
            if(ultrasonicDistance > ULTRASONIC_MIN && ultrasonicDistance < ULTRASONIC_MAX){
                UpdateObstaclePosition();
                get<0>(coordinate) = obstacleX;
                get<1>(coordinate) = -obstacleY;
                obstacles[coordinate] = true;
            }
        }
        else{
            Brake();
            ResetEncoders();
            UpdateRobotPrevPosition();
            if(ultrasonicDistance > ULTRASONIC_MIN && ultrasonicDistance < ULTRASONIC_MAX){
                UpdateObstaclePosition();
                get<0>(coordinate) = obstacleX; //Use get() to change alues of tuple
                get<1>(coordinate) = -obstacleY;
                obstacles[coordinate] = true;
            }
            robotXDelta = 0;
            robotYDelta = 0;
        }

        //RECORDING ROBOT PATH==================================================
        get<0>(coordinate) = robotX;
        get<1>(coordinate) = robotY;
        robotPath[coordinate] = true;

        //LCD DISPLAY===========================================================
        lcd::print(1,"Gyro Sensor: %.2f",angle);
        lcd::print(2,"Ultrasonic Sensor: %d",ultrasonicDistance);
        lcd::print(3,"Drive Distance: %.2f",driveDistance);
        lcd::print(4,"obstacle-x: %.2f",obstacleX);
        lcd::print(5,"obstacle-y: %.2f",obstacleY);
        lcd::print(6,"robot-x: %.2f",robotX);
        lcd::print(7,"robot-y: %.2f",robotY);

        //SERIAL OUTPUT=========================================================
        if (controller.get_digital(E_CONTROLLER_DIGITAL_B)){
            while (controller.get_digital(E_CONTROLLER_DIGITAL_B)){}
            /*
            for (map < tuple<int,int> , bool >::iterator i = obstacles.begin(); i != obstacles.end(); i++){
                cout << "coordinate-x: " << get<0>(i -> first) << "   ";
                cout << "coordinate-y: " << get<1>(i -> first) << endl;
            }
            */
            for (map < tuple<int,int> , bool >::iterator i = robotPath.begin(); i != robotPath.end(); i++){
                cout << "coordinate-x: " << get<0>(i -> first) << "   ";
                cout << "coordinate-y: " << get<1>(i -> first) << endl;
            }
        }

        //SAVING DATA TO FILES==================================================
        else if (controller.get_digital(E_CONTROLLER_DIGITAL_X)){
            while (controller.get_digital(E_CONTROLLER_DIGITAL_X)){}
            ofstream outf1;
            ofstream outf2;
            //Opening files for writing
            outf1.open("/usd/RobotPath.txt",ios::out);
            outf2.open("/usd/Obstacles.txt",ios::out);
            //Iterating through the maps and writing the coordinates to the files
            for (map < tuple<int,int> , bool >::iterator i = robotPath.begin(); i != robotPath.end(); i++){
                outf1 << get<0>(i -> first) << "," << get<1>(i -> first) << " ";
            }
            for (map < tuple<int,int> , bool >::iterator i = obstacles.begin(); i != obstacles.end(); i++){
                outf2 << get<0>(i -> first) << "," << get<1>(i -> first) << " ";
            }
            //Closing the files
            outf1.close();
            outf2.close();
        }
        delay(10);
    }
}
