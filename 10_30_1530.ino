#include "Enes100.h"
#include "Tank.h"

double x, y, theta, distZero, distTwo, y1, y2;
double xTemp, yTemp, thetaTemp;
int pinZero, pinTwo;
//bool angleWrong = true;

void setup() {
	pinZero = 0;
	pinTwo = 2;
	Enes100.begin("Team Name Here", BLACK_BOX, 3, 8, 9);
	Tank.begin();
	
}

void loop() {
	Tank.setLeftMotorPWM(150);
	Tank.setRightMotorPWM(150);
	updateLocation();
	if (y >= 1.7){
		upperWall();
	}
	if (y <= 0.3){
		lowerWall();
	}
	if (theta >= 1.55 && theta <=3.14 || theta <= -1.57 && theta >= -3.14) {
		turnWrong();
	}
	if (distZero <= 0.35 && distTwo <= 0.35){
		turnLeft();
	}
	if (distZero >= 0.35 && distTwo <= 0.35){
		turnLeft();
	}
	if (distZero <= 0.35 && distTwo >= 0.35){
		turnRight();
	}
	
}

void updateLocation() {
	Enes100.updateLocation();
	x = Enes100.location.x;
	y = Enes100.location.y;
	theta = Enes100.location.theta;
	distZero = Tank.readDistanceSensor(pinZero);
	distTwo = Tank.readDistanceSensor(pinTwo);
}
void turnWrong() {
	Tank.setLeftMotorPWM(150);
	Tank.setRightMotorPWM(-150);
	while (true){
		Enes100.updateLocation();
		if (Enes100.location.theta >=-0.01 && Enes100.location.theta <=0.01){
			break;
		}
	}
}

void turnLeft() {
	Tank.setLeftMotorPWM(-150);
	Tank.setRightMotorPWM(150);
	while (true){
		Enes100.updateLocation();
		if (Enes100.location.theta >=0.89 && Enes100.location.theta <=0.90){
			Tank.setLeftMotorPWM(150);
			Tank.setRightMotorPWM(150);	
			delay(1500);
			Tank.setLeftMotorPWM(150);
			Tank.setRightMotorPWM(-150);
			while (true) {
				Enes100.updateLocation();
				if (Enes100.location.theta >=-0.01 && Enes100.location.theta <=0.01){
					Tank.turnOffMotors();
					break;
				}
			}
			break;
		}
	}
}

void turnRight() {
	Tank.setLeftMotorPWM(150);
	Tank.setRightMotorPWM(-150);
	while (true){
		Enes100.updateLocation();
		if (Enes100.location.theta <=-0.78 && Enes100.location.theta >=-0.79){
			Tank.setLeftMotorPWM(150);
			Tank.setRightMotorPWM(150);	
			delay(1500);
			Tank.setLeftMotorPWM(150);
			Tank.setRightMotorPWM(-150);
			while (true) {
				Enes100.updateLocation();
				if (Enes100.location.theta >=-0.01 && Enes100.location.theta <=0.01){
					Tank.turnOffMotors();
					break;
				}
			}
			break;
		}
	}
}

void lowerWall() {
	Tank.setLeftMotorPWM(-150);
	Tank.setRightMotorPWM(150);
	while (true) {
		Enes100.updateLocation();
		if (theta >= 1.56 && theta <= 1.58) {
			y1 = Enes100.location.y;
			while (true){
				Enes100.updateLocation();
				y2 = Enes100.location.y;
				if (y2 - y1 >= 0.15) {
					Tank.setLeftMotorPWM(150);
					Tank.setRightMotorPWM(-150);
					while (true) {
						Enes100.updateLocation();
						if (Enes100.location.theta >= -0.01 && Enes100.location.theta <=0.01) {
							Tank.turnOffMotors();
							break;
						}
					}
					break;
				}
				
			}
			break;
		}
	}
}

void upperWall() {
	Tank.setLeftMotorPWM(150);
	Tank.setRightMotorPWM(-150);
	while (true) {
		Enes100.updateLocation();
		if (theta <= -1.56 && theta >= -1.58) {
			y1 = Enes100.location.y;
			while (true){
				Enes100.updateLocation();
				y2 = Enes100.location.y;
				if (y2 - y1 >= -0.15) {
					Tank.setLeftMotorPWM(-150);
					Tank.setRightMotorPWM(150);
					while (true) {
						Enes100.updateLocation();
						if (Enes100.location.theta >= -0.01 && Enes100.location.theta <=0.01) {
							Tank.turnOffMotors();
							break;
						}
					}
					break;
				}
				
			}
			break;
		}
	}
}


//fix error code
void error(){
	delay(5000);
	Enes100.updateLocation();
	if (x = Enes100.location.x){
		if (y = Enes100.location.y){
			if (theta = Enes100.location.theta) {
				Tank.setLeftMotorPWM(-150);
				Tank.setRightMotorPWM(-150);
				delay(2000);
				
			}
		}
	}
}
