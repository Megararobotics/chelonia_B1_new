// Motor A
const int motorAPin1 = 2;
const int motorAPin2 = 3;
#define ENA 9
// Motor B
const int motorBPin1 = 4;
const int motorBPin2 = 5;
#define ENB 10

// Ultrasonic sensor pins
const int trigPin = 16;
const int echoPin = 17;

// Buzzer pin
const int buzzerPin = 26;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  pinMode(motorAPin1, OUTPUT);
  pinMode(motorAPin2, OUTPUT);
  pinMode(motorBPin1, OUTPUT);
  pinMode(motorBPin2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // Trigger the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the echo time to determine distance
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;

  // Print distance for debugging
  Serial.print("Distance: ");
  Serial.println(distance);

  // If obstacle detected closer than 20 units
  if (distance < 20) {
    // Activate the buzzer
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
    delay(100);
  } else {
    // Deactivate the buzzer
    digitalWrite(buzzerPin, LOW);
  }

  // Control motor based on distance
  if (distance >= 20) {
    // Move forward if no obstacle
    digitalWrite(motorAPin1, HIGH);
    digitalWrite(motorAPin2, LOW);
    digitalWrite(motorBPin1, HIGH);
    digitalWrite(motorBPin2, LOW);
    analogWrite(ENA, 100);
    analogWrite(ENB, 100);
  } else {
    // Stop if obstacle detected
    digitalWrite(motorAPin1, LOW);
    digitalWrite(motorAPin2, LOW);
    digitalWrite(motorBPin1, LOW);
    digitalWrite(motorBPin2, LOW);
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);
  }
}
