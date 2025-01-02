#define LED 6
#define Buzzer 26
#define ENA 9     // Enable of Motor A
#define ENB 10    // Enable of Motor B
#define IN1 2     // Input 1 of Motor A
#define IN2 3     // Input 2 of Motor A
#define IN3 4     // Input 1 of Motor B
#define IN4 5     // Input 2 of Motor B


#define Sensor A0 // Define the gas sensor input pin

void setup() {
  Serial.begin(9600);        // Set the baud rate for serial monitor


  // Set pin modes
  pinMode(LED, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Initially stop the motors
  stopMotors();
}

void loop() {
  // Read gas sensor value
  int value = analogRead(Sensor);
  Serial.print("Gas Sensor Value: ");
  Serial.println(value);

  // Gas detection condition
  if (value > 120) {
    digitalWrite(LED, HIGH);
    digitalWrite(Buzzer, HIGH);
    stopMotors();
    Serial.println("Gas Detected! Robot Stopped.");
    Serial.println("Emergency: Gas Detected! Robot Stopped.");
  } else {
    // Check for Bluetooth commands if no gas is detected
    if (Serial.available() > 0) {
      char command = Serial.read();

      // Forward command 'F'
      if (command == 'F') {
        Serial.println("Command: Move Forward");
        moveForward();
        Serial.println("Robot is moving forward.");
      }

      // Stop command 'S'
      if (command == 'S') {
        Serial.println("Command: Stop");
        stopMotors();
        Serial.println("Robot Stopped by User.");
      }
    }
  }

  delay(1000); // Add delay to reduce serial prints
}

// Function to move the robot forward
void moveForward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 200); // Adjust the PWM value for motor A speed
  analogWrite(ENB, 200); // Adjust the PWM value for motor B speed
}

// Function to stop the robot
void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);  // Stop motor A
  analogWrite(ENB, 0);  // Stop motor B
}
