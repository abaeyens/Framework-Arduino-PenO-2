#include <RuneMotor.h>

// A global variable.
int a;

void setup() {
  // Initiate the motor pins.
  // You can change the pin numbers in the library file if necessary.
  initMotors();

  // We'll use the serial port 
  Serial.begin(9600);
}

void loop() {
  // Let's set the speeds of motor 1 to a speed of choice.
  setSpeedMotor1(135);

  // We can now read the speed with the function getMotorSpeed1().
  a = getSpeedMotor1();

  // We can send it over the serial port to the computer.
  Serial.print("Speed of motor 1: ");
  Serial.println(a);

  delay(1000);
}
