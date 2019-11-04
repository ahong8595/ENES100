#include "Enes100.h"
#include "Tank.h"

double x, y, theta, distZero, distTwo, y1, y2, msX, msY, difference;
double xTemp, yTemp, thetaTemp;
int pinZero, pinTwo;
//bool angleWrong = true;

void setup() {
	pinZero = 0;
	pinTwo = 2;
	Enes100.begin("Team Name Here", BLACK_BOX, 3, 8, 9);
	Enes100.println(Enes100.destination.x);
	Enes100.println(Enes100.destination.y);
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
		Enes100.println(theta);
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
	missionSite();
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
		if (Enes100.location.theta >=-0.03 && Enes100.location.theta <=0.03){
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
			Tank.setLeftMotorPWM(-150);
			Tank.setRightMotorPWM(150);
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
	Tank.setLeftMotorPWM(-100);
	Tank.setRightMotorPWM(100);
	while (true) {
		updateLocation();
		if (Enes100.location.theta >= 1.56 && Enes100.location.theta <= 1.58) {
			y1 = Enes100.location.y;
			Tank.setLeftMotorPWM(150);
			Tank.setRightMotorPWM(150);
			while (true){
				Enes100.updateLocation();
				y2 = Enes100.location.y;
				if (y2 - y1 >= 0.50) {
					Tank.setLeftMotorPWM(150);
					Tank.setRightMotorPWM(-150);
					while (true) {
						Enes100.updateLocation();
						if (Enes100.location.theta >= -0.01 && Enes100.location.theta <=0.01) {
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
		if (Enes100.location.theta <= -1.56 && Enes100.location.theta >= -1.58) {
			y1 = Enes100.location.y;
			Tank.setLeftMotorPWM(150);
			Tank.setRightMotorPWM(150);
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

void missionSite(){
	msY = Enes100.destination.y;
	msX = Enes100.destination.x;
	difference = absoluteValue(msX, Enes100.location.x);
	if (difference < 0.05) {
		if (msY > y) {
			Tank.setLeftMotorPWM(-150);
			Tank.setRightMotorPWM(150);
			while (true) {
				Enes100.updateLocation();
				if (Enes100.location.theta > 1.56 && Enes100.location.theta < 1.58){
					Tank.setLeftMotorPWM(150);
					Tank.setRightMotorPWM(150);
					while (true) {
						Enes100.updateLocation();
						if (absoluteValue(msX,Enes100.location.x) < 0.05) {
							if (absoluteValue(msY,Enes100.location.y) < 0.05){
								Tank.turnOffMotors();
								break;
							}
						}
					}
				}
			}
		}
		if (msY < y) {
			Tank.setLeftMotorPWM(150);
			Tank.setRightMotorPWM(-150);
			while (true) {
				Enes100.updateLocation();
				if (Enes100.location.theta < -1.56 && Enes100.location.theta > -1.58){
					Tank.setLeftMotorPWM(150);
					Tank.setRightMotorPWM(150);
					while (true) {
						Enes100.updateLocation();
						if (absoluteValue(msX,Enes100.location.x) < 0.05) {
							if (absoluteValue(msY,Enes100.location.y) < 0.05){
								Tank.turnOffMotors();
								break;
							}
						}
					}
				}
			}
		}
		
	}
}

double absoluteValue(double a, double b){
	if (a > b){
		return a - b;
	}
	if (a < b) {
		return b - a;
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