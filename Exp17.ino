#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 53   // RFID SS pin
#define RST_PIN 27  // RFID reset pin


// Define motor pins
#define ENA 9       // Enable Motor A (PWM)
#define IN1 2      // Input 1 of Motor A
#define IN2 3       // Input 2 of Motor A
#define ENB 10      // Enable Motor B (PWM)
#define IN3 4       // Input 1 of Motor B
#define IN4 5      // Input 2 of Motor B

boolean rfidDetected = false;  // Flag to check RFID detection

MFRC522 rfid(SS_PIN, RST_PIN);   // Create MFRC522 instance for RFID

void setup() {
  Serial.begin(9600);

  SPI.begin();  // Initialize SPI bus for RFID
  rfid.PCD_Init();  // Initialize MFRC522 for RFID

  Serial.println("Tap RFID/NFC Tag on reader");

  // Motor pins as output
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Initially stop the motors
  stopMotors();
}

void loop() {
  if (rfid.PICC_IsNewCardPresent()) {  // new RFID tag detected
    if (rfid.PICC_ReadCardSerial()) {  // NUID has been read
      rfidDetected = true;
      MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
      Serial.print("UID:");
      for (int i = 0; i < rfid.uid.size; i++) {
        Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(rfid.uid.uidByte[i], HEX);
      }
      Serial.println();

      // Send stop command to Bluetooth app as an alert
      Serial.println("Robo stopped due to RFID detection");

      // Stop the robot
      stopMotors();
      rfid.PICC_HaltA();  // halt PICC
      rfid.PCD_StopCrypto1();  // stop encryption on PCD
    }
  }

  // Check if a Bluetooth command is available
  if (Serial.available() > 0) {
    char command = Serial.read();

    // Check for forward command ('F') or stop after RFID ('S')
    if (command == 'F' && !rfidDetected) {
      moveForward();  // Move forward if RFID not detected
    } else if (command == 'S' || rfidDetected) {
      stopMotors();   // Stop the robot when commanded or RFID detected
    }
  }
}

// Function to move the robot forward
void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 150);  // Set the PWM speed for motor A
  analogWrite(ENB, 150);  // Set the PWM speed for motor B
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
