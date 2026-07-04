#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

// Pin Definitions
const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;

void setup() {
  Serial.begin(115200);
  
  // Try to initialize MPU6050
  if (!mpu.begin()) {
    while (1) {
      delay(10);
    }
  }
  
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Map the accelerometer values (-10 to 10 m/s^2) to PWM range (0-255)
  int redVal = map(constrain(a.acceleration.x, -10, 10), -10, 10, 0, 255);
  int greenVal = map(constrain(a.acceleration.y, -10, 10), -10, 10, 0, 255);
  int blueVal = map(constrain(a.acceleration.z, -10, 10), -10, 10, 0, 255);

  // Write values to RGB LED
  analogWrite(redPin, redVal);
  analogWrite(greenPin, greenVal);
  analogWrite(bluePin, blueVal);

  delay(20);
}
