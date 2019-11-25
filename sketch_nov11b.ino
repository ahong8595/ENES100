#include <Servo.h>
#include "Enes100.h"
Servo myservo;

//wifi variables
int markerid = 14;
int wifitx = 10, wifirx = 11; 

//motor stuff
int rightDir1 = 7;
int rightDir2 = 8;
int rightSpeed = 5;

int leftDir1 = 12;
int leftDir2 = 13;
int leftSpeed = 6;

//pump stuff
int pumpDir1 = 2;
int pumpDir2 = 4;//might not be needed
int pumpSpeed = 3;

//servo stuff


//sensor stuff
int leftDistanceSensor = 14;//A0
int rightDistanceSensor = 15;//A1
int salinitySensor = 16;//A2
int photoresistor = 17;//A3  LED is powered with 5V (always on)
int depthSensor = 18;//A4

int salinity;
int pollution;
int depth;

//only GPIO pins not used is A5 (lol)

//wifi stuff
//uses pins 0 and 1 (I think??)

void setup(){

  //motor stuff
  pinMode(rightDir1,OUTPUT);
  pinMode(rightDir2,OUTPUT);
  pinMode(rightSpeed,OUTPUT);

  pinMode(leftDir1,OUTPUT);
  pinMode(leftDir2,OUTPUT);
  pinMode(leftSpeed,OUTPUT);

  //pump stuff
  pinMode(pumpDir1,OUTPUT);
  pinMode(pumpDir2,OUTPUT); //might not be needed
  pinMode(pumpSpeed,OUTPUT);
 
  //servo stuff
  myservo.attach(9);
 
  //sensor stuff
  pinMode(leftDistanceSensor,INPUT);
  pinMode(rightDistanceSensor,INPUT);
  pinMode(salinitySensor,INPUT);
  pinMode(photoresistor,INPUT);
  pinMode(depthSensor,INPUT);
 
  //wifi stuff?
 
  double xPos;
  double yPos;
  double theta;

  double xPoolPos;
  double yPoolPos;
 
  Serial.begin(9600);

  //make sure everything's stopped
  Enes100.begin("Water Those", WATER, markerid, wifitx, wifirx);
  
  servoStop();
  pumpOff();
  stopMoving();
}



void loop(){
  //forward(200);
  //delay(1000);
  //stopMoving();
  //pumpOn(100);
  //delay(30000);
  //pumpOff();
  /*
  pollution=analogRead(photoresistor);
  salinity=analogRead(salinitySensor);
  Enes100.println("pollution: "+ (String) pollution);
  Enes100.println("salinity: "+ (String) salinity);
  if(salinity>150){
    Enes100.println("Theres is saltwater");
  }else{
    Enes100.println("There is freshwater");
  }
  if(pollution<400){
    Enes100.println("The water is polluted");
  }else{
    Enes100.println("The water is not polluted");
  }
  delay(2000);
  */





  /*
  //while not in front of pool
  while(xPos!=xPoolPos && yPos!=yPoolPos && theta!=0){
    //update position
    xPos=;
    yPos=;
    theta=;

    //Algorithm to realign robot to pool (use trig, see if need to turn left or right, see if need to go back/forward (should always be forward)
    calculatedTheta=arctan((yPoolPos-yPos)/(xPoolPos-xPos));
    while(theta!=calculatedTheta){
      if(calculatedTheta>theta){
        turnLeft(25);
        delay(100);
      }else{
        turnRight(25);
        delay(100);
      }
      //update theta (and maybe x and y and recalculate)
    }
   
 
    //while object in front of robot (needs to be adjusted to not count pool as an obstacle
    //will have to handle walls
    while(analogRead(leftDistanceSensor)<100 || analogRead(rightDistanceSensor)<100){
      //if both sensors blocked turn in a random direction
      if(analogRead(leftDistanceSensor)<100 && analogRead(rightDistanceSensor)<100){
        backward(210);
        delay(3000);
        if(random(0,1){
          turnLeft(210);
        }else{
          turnRight(210);
        }
        delay(1000);
        stopMoving();
      }else{
        //if ONLY left sensor blocked right right
        if(analogRead(leftDistanceSensor)<100){
          backward(210);
          delay(3000);
          turnRight(210);
          delay(1000);
          stopMoving();
          }else{
            //if ONLY right sensor blocked turn left
            backward(210);
            delay(3000);
            turnLeft(210);
            delay(1000);
            stopMoving();
          }
      }
    }
 
  }

  //Arrived at pool
  stopMoving();
  //Arm down
  servoForward(210);
  delay(2000);
  //Arm stop
  servoStop();
  //Collect water
  pumpOn(210);
  delay(5000);
  pumpOff();
  //Collect sensor values
  salinity = analogRead(salinitySensor);
  pollution = analogRead(photoresistor);
  depth = analogRead(depthSensor);
  //Interpret and transmit values
  /*
  //interpret salinity
  if(salinity>100){
    transmit("Salt Water");
  }else{
    transmit("Fresh Water");
  }
 
  //interpret pollution
  if(pollution>100){
    transmit("Polluted");
  }else{
    transmit("Clean");
  }

  transmit(double(depth*.01)+"cm");
  //
  //Arm up
  servoBackward(210);
  delay(2000);
  //Arm stop
  servoStop();
  //Mission Complete
  break
*/
}

//rate goes from 0 (stopped) to 255 (full speed)
//Dir1 = 1 and Dir2 = 0 is forward, reverse is backward

void pumpOn(int rate){
  digitalWrite(pumpDir1,1);
  digitalWrite(pumpDir2,0);
  digitalWrite(pumpSpeed,rate);
}

void pumpOff(){
  digitalWrite(pumpDir1,1);
  digitalWrite(pumpDir2,0);
  digitalWrite(pumpSpeed,0);
}
//rate goes from 0 (stopped) to 90 (full speed)
void servoForward(int rate){
  myservo.write(90+rate);
}

void servoBackward(int rate){
  myservo.write(90-rate);
}

void servoStop(){
  myservo.write(90);
}

void turnLeft(int rate){
digitalWrite(rightDir1,1);
digitalWrite(rightDir2,0);

digitalWrite(leftDir1,0);
digitalWrite(leftDir2,1);

analogWrite(rightSpeed,rate);
analogWrite(leftSpeed,rate);
}

void turnRight(int rate){
digitalWrite(rightDir1,0);
digitalWrite(rightDir2,1);

digitalWrite(leftDir1,1);
digitalWrite(leftDir2,0);

analogWrite(rightSpeed,rate);
analogWrite(leftSpeed,rate);
}

void forward(int rate){
digitalWrite(rightDir1,1);
digitalWrite(rightDir2,0);

digitalWrite(leftDir1,1);
digitalWrite(leftDir2,0);

analogWrite(rightSpeed,rate);
analogWrite(leftSpeed,rate);
}

void backward(int rate){
digitalWrite(rightDir1,0);
digitalWrite(rightDir2,1);

digitalWrite(leftDir1,0);
digitalWrite(leftDir2,1);

analogWrite(rightSpeed,rate);
analogWrite(leftSpeed,rate);
}

void stopMoving(){
  analogWrite(rightSpeed,0);
  analogWrite(leftSpeed,0);
}
