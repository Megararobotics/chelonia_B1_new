#include <ControlMotor.h>//Use the motor control library.
// Set the pins to be used on the Arduino board.
ControlMotor control(4,5,2,3,10,9); // Right motor 1, right motor 2, left motor 1, left motor 2, right PWM, left PWM

#include <Ultrasonic.h>//Uses the HC-SR04 ultrasonic sensor library.
Ultrasonic sensor(14,15,30000); // (Trig pin, Echo pin, maximum distance unit is us) i.e. 30000us = about 5 meters

int measurement_speed = 5;//Adjust sensor measurement speed.
long int distance = 0; //Declare a variable to store the distance.
int random_value = 0;//Save the random value.

void setup() 
{ 
Serial.begin(9600);//Initialize the serial port.
 
} 
 
void loop() 
{
 
  
  control.Motor(150,1);//The car moves forward at a speed of 150.
  distance=sensor.Ranging(CM);//Measure the distance and store it in the distance variable.

  delay(measurement_speed);//Delay to control sensor measurement speed.
 
 //The following corresponds to the case where there are no obstacles.
 Serial.print("No obstacle ");//Prints to the serial monitor that there is no obstacle.
 Serial.println(distance);//Print the distance.
 Serial.print("Random ");//Prints "Random".
 Serial.println(random_value);//Prints a random value.

 random_value = random (2);//Create a random value to prevent the car from turning in only one direction.
  
  
  while(distance<30){//Applies when the distance to the obstacle is less than 30cm.
        
  
  delay(measurement_speed);//Delay to control sensor measurement speed.
  control.Motor(0,1);//Stop the motor.
  distance = sensor.Ranging(CM);
  delay(1000);

  if(random_value==0){// Applies when the random value is 0.
 Serial.print("Distance ");//Prints "Distance " on the serial monitor.
 Serial.println(distance);//Print the distance.
 Serial.print("Random ");//Prints "Random".
 Serial.println(random_value);//Prints a random value.
 
  control.Motor(170,100);//The car turns to the right for 0.4 seconds.
  delay(400);}
  
  else if (random_value==1){//Applies when the random value is 1.
 Serial.print("Distance ");//Prints "Distance " on the serial monitor.
 Serial.println(distance);//Print the distance.
 Serial.print("Random ");//Prints "Random".
 Serial.println(random_value);//Prints a random value.
 
  control.Motor(170,-100);//The car turns left for 0.4 seconds.
  delay(400);}
  }
}
