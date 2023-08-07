#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

MPU6050 sensor;

int16_t ax, ay, az;
int16_t gx, gy, gz;

void setup() {
  Serial.begin(57600);    
  Wire.begin();           
  sensor.initialize();    
  if (sensor.testConnection()) Serial.println("Sensor started correctly");
  else Serial.println("Error starting sensor");
}

void loop() {

  sensor.getAcceleration(&ax, &ay, &az);

  float accel_ang_x=atan(ax/sqrt(pow(ay,2) + pow(az,2)))*(180.0/3.14);
  float accel_ang_y=atan(ay/sqrt(pow(ax,2) + pow(az,2)))*(180.0/3.14);

  Serial.print("X Angle: ");
  Serial.print(accel_ang_x); 
  Serial.print("  Y Angle:");
  Serial.println(accel_ang_y);
  delay(2000);
}
