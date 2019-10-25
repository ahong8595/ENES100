#include "Enes100.h"
#include "Tank.h"

int a = 2;
int b = 2;
int c = 2;
int d = 0;
int e = 2;
int f = 2;
int g = 2, h = 2, k = 2;
double y1;
double y2;

void setup() {
	int eight;
	int six;
	Enes100.begin("Team Name Here", BLACK_BOX, 3, 8, 9);
	Tank.begin();
}

void loop() {
	a = 2;
	b = 2;
	c = 2;
	Enes100.updateLocation();
	Enes100.println(Tank.readDistanceSensor(0));
	Enes100.println(Tank.readDistanceSensor(2));
	
	Enes100.updateLocation();
	Enes100.println(Enes100.location.x);
	
	//turns right it in wrong direction
	Tank.setLeftMotorPWM(100);
	Tank.setRightMotorPWM(100);
		Enes100.updateLocation();
		if (Enes100.location.theta > 1.57 && Enes100.location.theta <=3.14 || Enes100.location.theta <-1.57 && 				Enes100.location.theta >=-3.14) {
			Tank.setLeftMotorPWM(100);
			Tank.setRightMotorPWM(-100);
			while (a == 2) {
			Enes100.updateLocation();
			if (Enes100.location.theta <= 0.032853) {
				Tank.setLeftMotorPWM(100);
				Tank.setRightMotorPWM(100);
				a = 3;
			}
			}
		} 
		
	
	//turns up if it hits an obstacle
	
		if (Tank.readDistanceSensor(0) < 0.15){
			Tank.setLeftMotorPWM(-50);
			Tank.setRightMotorPWM(50);
			Enes100.updateLocation();
				while (b == 2) {
					Enes100.updateLocation();
					if (Enes100.location.theta >= 1.50) {
						b = 3;
					}
				}
		   } else if (Tank.readDistanceSensor(2) < 0.15) {
				Tank.setLeftMotorPWM(-50);
				Tank.setRightMotorPWM(50);
				Enes100.updateLocation();
				while (b == 2) {
					Enes100.updateLocation();
					if (Enes100.location.theta >= 1.50) {
						b = 3;
					}
				}

			}
		Enes100.println("");
	
	

	//turns down if it hits the upper wall
	Enes100.updateLocation();
	if (Enes100.location.y > 1.7) {
		Tank.setLeftMotorPWM(50);
		Tank.setRightMotorPWM(-50);
		Enes100.updateLocation();
		while (c == 2) {
			Enes100.updateLocation();
			if (Enes100.location.theta <= -1.537147) {
				c = 3;
				if (Enes100.updateLocation()){
					y1 = Enes100.location.y;
				}
				Tank.setLeftMotorPWM(100);
				Tank.setRightMotorPWM(100);
				while (d == 0){
					if (Enes100.updateLocation()){
						y2 = Enes100.location.y;
					}
					if (y2-y1 <= -0.15) {
						d = 1;
						Tank.setLeftMotorPWM(-50);
						Tank.setRightMotorPWM(50);
						Enes100.updateLocation();
						while (e == 2) {
							Enes100.updateLocation();
							if (Enes100.location.theta >= 0.032853) {
								e = 3;
								Tank.turnOffMotors();
							}
						}
					}
				}
			}
		}
	}
	
	//turns up when hits bottom wall
	/*Enes100.updateLocation();
	if (Enes100.location.y < 0.3) {
		Tank.setLeftMotorPWM(50);
		Tank.setRightMotorPWM(-50);
		Enes100.updateLocation();
		while (g == 2) {
			Enes100.updateLocation();
			if (Enes100.location.theta >= 1.537147) {
				g = 3;
				if (Enes100.updateLocation()){
					y1 = Enes100.location.y;
				}
				Tank.setLeftMotorPWM(100);
				Tank.setRightMotorPWM(100);
				while (h == 0){
					if (Enes100.updateLocation()){
						y2 = Enes100.location.y;
					}
					if (y2-y1 <= 0.15) {
						h = 1;
						Tank.setLeftMotorPWM(-50);
						Tank.setRightMotorPWM(50);
						Enes100.updateLocation();
						while (k == 2) {
							Enes100.updateLocation();
							if (Enes100.location.theta <= 0.032853) {
								k = 3;
								Tank.turnOffMotors();
							}
						}
					}
				}
			}
		}
	}
	*/
	
	
	
	
	
	
	
	
	//enter the landing zone
	//code here is wonky
	/*Enes100.updateLocation();
	Enes100.println(Enes100.location.x);
	if (Enes100.location.x >= 3.22){
		Enes100.println(Enes100.location.x);
		Tank.setLeftMotorPWM(50);
		Tank.setRightMotorPWM(-50);
		Enes100.updateLocation();
		while (f == 2) {
			Enes100.updateLocation();
			if (Enes100.location.theta <= -1.537147) {
				f = 3;
				Tank.setLeftMotorPWM(100);
				Tank.setRightMotorPWM(100);
			}
		}
	}
	*/
	
		
		
}
