//Wall Follow Robo:
// Libraries
#include <PIDController.h>

// Objects
PIDController pid; // Create an instance of the PID controller class, called "pid"

//defines ultrasonic frontside sensor pins
const int trigPin1 = 16;//Trigger pin of frontside ultrasonic sensor connected to pin no:13
const int echoPin1 = 17;//Echo pin of frontside ultrasonic sensor connected to pin no:12
//defines ultrasonic leftside sensor pins
const int trigPin2 = 18;//Trigger pin of leftside ultrasonic sensor connected to pin no:3
const int echoPin2 = 19;//Echo pin of leftside ultrasonic sensor connected to pin no:2

//Left Motor connected to 10,9 digitalPins
int enA = 9;//Enable Pin of left motor
int LMP = 2;
int LMN = 3;
//Right Motor connected to 5,6 digitalPins
int enB = 10;//Enable Pin of right motor
int RMP = 4;
int RMN = 5;

//Declaring variables
int duration1 , distance1 , duration2 , distance2 , duration3 , distance3 , s1 = 10 , s2 = 10 , s3 = 15;

void setup()
{
  //Motor pins are OUTPUT
  //Leftside Motor
  pinMode(enA, OUTPUT);
  pinMode(LMP, OUTPUT);
  pinMode(LMN, OUTPUT);
  //Rightside Motor
  pinMode(enB, OUTPUT);
  pinMode(RMP, OUTPUT);
  pinMode(RMN, OUTPUT);

  //Frontside ultrasonic sensor pinmodes >> Trigger pin as output & Echo pin as input
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  //Leftside ultrasonic sensor pinmodes >> Trigger pin as output & Echo pin as input
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  pid.begin();//Initialize the PID instance
  pid.setpoint(10);// The "goal" the PID controller tries to "reach"
  pid.tune(100, 0, 1); //Tune the PID, arguments: kP, kI, kD
  pid.limit(0, 100); //Limit the PID output between 0 and 255, this is important to get rid of integral windup!
  Serial.begin(9600);//setting serial monitor at a default baund rate of 9600
}

void loop()
{
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = (duration1 / 29) / 2;
  Serial.print("Distance of FS: ");
  Serial.println(distance1);

  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = (duration2 / 29) / 2;
  Serial.print("Distance of LS: ");
  Serial.println(distance2);

  int output1 = pid.compute(-distance1);
  int output2 = pid.compute(-distance2);
  Serial.println("Distance 1 : " + String(distance1));
  Serial.println("Distance 2 : " + String(distance2));

  if (distance1 >= s1 && distance2 > s2) //If distance of front sensor >= setpoint & distance of side sensor > setpoint, the robot will turn left direction
  {
    //Turns Left
    digitalWrite(LMP, LOW);
    digitalWrite(LMN, LOW);
    digitalWrite(RMP, HIGH);
    digitalWrite(RMN, LOW);
    analogWrite(enA, output2);
    analogWrite(enB, output2);
    Serial.println("Left");//Print Left
  }
  else if (distance1 >= s1 && distance2 >= s2) //If distance of front sensor >= setpoint & distance of side sensor >= setpoint, the robot will move forward direction
  {
    //Moves Forward
    digitalWrite(LMP, HIGH);
    digitalWrite(LMN, LOW);
    digitalWrite(RMP, HIGH);
    digitalWrite(RMN, LOW);
    analogWrite(enA, output1);
    analogWrite(enB, output1);
    Serial.println("Forward");//Print Forward
  }
  else if (distance1 > s1 && distance2 < s2) //If distance of front sensor > setpoint & distance of side sensor < setpoint, the robot will turn right direction
  {
    //Turns Right
    digitalWrite(LMP, HIGH);
    digitalWrite(LMN, LOW);
    digitalWrite(RMP, LOW);
    digitalWrite(RMN, LOW);
    analogWrite(enA, output2);
    analogWrite(enB, output2);
    Serial.println("Right");//Print Right
    delay(100);
    //Moves Forward
    digitalWrite(LMP, HIGH);
    digitalWrite(LMN, LOW);
    digitalWrite(RMP, HIGH);
    digitalWrite(RMN, LOW);
    analogWrite(enA, output1);
    analogWrite(enB, output1);
    Serial.println("Forward");//Print Forward*/
  }
  else if (distance1 < s1 && distance2 < s2) //If distance of front sensor < setpoint & distance of side sensor > setpoint, the robot will turn left direction
  {
    //Turns Left
    digitalWrite(LMP, HIGH);
    digitalWrite(LMN, LOW);
    digitalWrite(RMP, LOW);
    digitalWrite(RMN, HIGH);
    analogWrite(enA, output2);
    analogWrite(enB, output2);
    //delay(500);
    Serial.println("Left");//Print Left
  }
  else if (distance1 < s1 && distance2 > s2) //If distance of front sensor < setpoint & distance of side sensor < setpoint, the robot will turn right direction
  {
    //Turns Right
    digitalWrite(LMP, LOW);
    digitalWrite(LMN, HIGH);
    digitalWrite(RMP, HIGH);
    digitalWrite(RMN, LOW);
    analogWrite(enA, output2);
    analogWrite(enB, output2);
    delay(500);
    Serial.println("Right");//Print Right
    //Moves Forward
    digitalWrite(LMP, HIGH);
    digitalWrite(LMN, LOW);
    digitalWrite(RMP, HIGH);
    digitalWrite(RMN, LOW);
    analogWrite(enA, output1);
    analogWrite(enB, output1);
    Serial.println("Forward");//Print Forward
  }
}
