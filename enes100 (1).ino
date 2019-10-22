#include "Enes100.h"
#include "Tank.h"

void setup() {
	int eight;
	int six;
	Enes100.begin("Team Name Here", BLACK_BOX, 3, 8, 9);
	Tank.begin();
	Tank.setLeftMotorPWM(-100);
	Tank.setRightMotorPWM(-100);
}

void loop() {
	if (Enes100.updateLocation()) {
    Enes100.println(Enes100.location.x); // x Coordinate
    Enes100.println(Enes100.location.y); // y Coordinate
    Enes100.println(Enes100.location.theta); // Theta
	delay(500);
	if (Tank.readDistanceSensor(8) < 0.2){
		Tank.turnOffMotors();
	}
		
	if (Tank.readDistanceSensor(6) < 0.2){
		Tank.turnOffMotors();
	}
	Enes100.println("");
	}
	
		
		
}
