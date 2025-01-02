

// defines ultrasonic sensor pins
const int trigPin = 16;
const int echoPin = 17;

// Defines variables
long duration, distance;
String status = "";

// defines motorpins
const int motor1A = 2;
const int motor1B = 3;
#define ENA 9
const int motor2A = 4;
const int motor2B = 5;
#define ENB 10


// defines variables
String A, B, C, D;

void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor2B, OUTPUT);
  pinMode(ENB, OUTPUT);
  Serial.begin(9600); // Starts the serial communication


}

void loop()
{

  // Clears the trigPin

  digitalWrite(trigPin, LOW);

  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds

  digitalWrite(trigPin, HIGH);

  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds

  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance

  distance = (duration / 2) / 28.5;

  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  Serial.println(" cm");

  // Send ultrasonic sensor data to mobile app via Bluetooth
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Simulate monitor status
  //status = "Normal"; // Change status as per your monitoring conditions
  // Send monitor status to mobile app via Bluetooth
  /*BTSerial.print("Status: ");
    BTSerial.println(status);*/

  delay(1000); // Adjust delay based on your requirements


  if (distance >= 80)            //check wheather the distance >= 80
  { //If the above condition is 'true' then the statement below will execute
    //Moves Forward with high speed
    digitalWrite(motor1A, HIGH);
    digitalWrite(motor1B, LOW);
    digitalWrite(motor2A, HIGH);
    digitalWrite(motor2B, LOW);
    analogWrite(ENA, 255);
    analogWrite(ENB, 255);
    Serial.print("Moving Forward with full speed");           //Print A
    Serial.println();
    Serial.print("Moving Forward with full speed");
  }
  else if (distance >= 50 )      //check wheather the distance >= 50
  { //If above the condition is 'true' then the statement below will execute
    //Move Forward with less speed than above
    digitalWrite(motor1A, HIGH);
    digitalWrite(motor1B, LOW);
    digitalWrite(motor2A, HIGH);
    digitalWrite(motor2B, LOW);
    analogWrite(ENA, 175);
    analogWrite(ENB, 175);
    Serial.print("Moving Forward with speed:175");           //Print B
    Serial.println();
    Serial.print("Moving Forward with speed:175");
  }
  else if (distance >= 10)       //check wheather the distance >= 10
  { //If above the condition is 'true' then the statement below will execute
    //Move Forward with less speed than above
    digitalWrite(motor1A, HIGH);
    digitalWrite(motor1B, LOW);
    digitalWrite(motor2A, HIGH);
    digitalWrite(motor2B, LOW);
    analogWrite(ENA, 100);
    analogWrite(ENB, 100);
    Serial.print("Moving Forward with speed:100");
    Serial.println();
    Serial.print("Moving Forward with speed:100");
  }
  else                           //If obstacle detects with distance <10, then the robot turns right direction and moves forward
  {
    digitalWrite(motor1A, LOW);
    digitalWrite(motor1B, LOW);
    digitalWrite(motor2A, LOW);
    digitalWrite(motor2B, LOW);
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);
    Serial.print("Stopped");           //Print D
    Serial.println();
    Serial.print("Stopped");
    //delay(900);
  }
}
