#include <Servo.h>

#define TURN_DELAY 522

Servo myServoL;
Servo myServoR;

const int maxSpeedL = 1700;
const int maxSpeedR = 1300;

int controlOne = 8;
int controlTwo = 9 ;
int controlThree = 10;
int controlFour = 11 ;

int controlOneValue = 0;
int controlTwoValue = 0;
int controlThreeValue = 0;
int controlFourValue = 0;

void stopServo()
{
    myServoL.writeMicroseconds(1500);  // Stopped
    myServoR.writeMicroseconds(1500);  // Stopped
}

void forward(){
    myServoR.writeMicroseconds(maxSpeedR);
    myServoL.writeMicroseconds(maxSpeedL);
}

void reverse(){
    myServoR.writeMicroseconds(maxSpeedL);
    myServoL.writeMicroseconds(maxSpeedR);
}

void advanceRight()
{
  stopServo();
  myServoR.writeMicroseconds(maxSpeedL); ///NEED TO WORK ON THIS
  myServoL.writeMicroseconds(maxSpeedL);
  delay(TURN_DELAY);
  stopServo();
  delay(250);
}


void advanceLeft()
{
  stopServo();
  myServoR.writeMicroseconds(maxSpeedR);
  myServoL.writeMicroseconds(maxSpeedR); ///NEED TO WORK ON THIS
  delay(TURN_DELAY);
  stopServo();
  delay(250);
}

void setup(void)
{
  Serial.begin(9600);
  pinMode(controlOne, INPUT_PULLUP);
  pinMode(controlTwo, INPUT_PULLUP);
  pinMode(controlThree, INPUT_PULLUP);
  pinMode(controlFour, INPUT_PULLUP);
  myServoL.attach(6);  // Servo is connected to digital pin 9 
  myServoR.attach(7);  // Servo is connected to digital pin 10 
  stopServo();
}

void readControlValues(){
  controlOneValue = digitalRead(controlOne);
  controlTwoValue = digitalRead(controlTwo);
  controlThreeValue = digitalRead(controlThree);
  controlFourValue = digitalRead(controlFour);
  
  Serial.print("one: ");
  Serial.println(controlOneValue);
  Serial.print("two: ");
  Serial.println(controlTwoValue);
  Serial.print("three: ");
  Serial.println(controlThreeValue);
  Serial.print("four: ");
  Serial.println(controlFourValue);
}

void loop()
{
  readControlValues();
  if(!controlOneValue && !controlTwoValue && !controlThreeValue && controlFourValue) //D0001
    forward(); 
  else if(!controlOneValue && !controlTwoValue && controlThreeValue && !controlFourValue) //D0010
    advanceLeft();
  else if(!controlOneValue && !controlTwoValue && controlThreeValue && controlFourValue) //D0011
    advanceRight();
  else if(!controlOneValue && controlTwoValue && !controlThreeValue && !controlFourValue) //D0100
    reverse();
  else if(controlOneValue && controlTwoValue && controlThreeValue && controlFourValue)//D1111
    stopServo();
    
  controlOneValue = controlTwoValue = controlThreeValue = controlFourValue = 0;

  delay(500);
}

