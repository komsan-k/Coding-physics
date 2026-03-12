#include <ESP32Servo.h>

// ---------------- Servo objects ----------------
Servo servoPan;
Servo servoTilt;

// ---------------- Servo pins ----------------
const int PAN_SERVO_PIN  = 18;
const int TILT_SERVO_PIN = 19;

// ---------------- Servo limits ----------------
const int PAN_MIN   = 0;
const int PAN_MAX   = 180;
const int TILT_MIN  = 30;
const int TILT_MAX  = 150;

// ---------------- Initial angles ----------------
int panAngle  = 90;
int tiltAngle = 90;

void setup() {
  Serial.begin(115200);

  // Set PWM frequency for servos
  servoPan.setPeriodHertz(50);
  servoTilt.setPeriodHertz(50);

  // Attach servos
  servoPan.attach(PAN_SERVO_PIN, 500, 2400);
  servoTilt.attach(TILT_SERVO_PIN, 500, 2400);

  // Move to center position
  servoPan.write(panAngle);
  servoTilt.write(tiltAngle);

  Serial.println("ESP32 Pan-Tilt Servo Control Ready");
}

void loop() {
  // Example test motion

  // Center
  servoPan.write(90);
  servoTilt.write(90);
  delay(1000);

  // Pan left
  servoPan.write(45);
  delay(1000);

  // Pan right
  servoPan.write(135);
  delay(1000);

  // Center pan
  servoPan.write(90);
  delay(1000);

  // Tilt up
  servoTilt.write(120);
  delay(1000);

  // Tilt down
  servoTilt.write(60);
  delay(1000);

  // Return center
  servoTilt.write(90);
  delay(1000);
}
