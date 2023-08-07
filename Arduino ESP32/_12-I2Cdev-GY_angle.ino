#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

MPU6050 sensor;

int gx, gy, gz;

long tiempo_prev, dt;
float girosc_ang_x, girosc_ang_y;
float girosc_ang_x_prev, girosc_ang_y_prev;

void setup() {
  Serial.begin(57600);    
  Wire.begin();           
  sensor.initialize();    
  if (sensor.testConnection()) Serial.println("Sensor started correctly");
  else Serial.println("Error starting sensor");
tiempo_prev=millis();
}

void loop() {
  sensor.getRotation(&gx, &gy, &gz);
  
  dt = millis()-tiempo_prev;
  tiempo_prev=millis();
  
  girosc_ang_x = (gx/131)*dt/1000.0 + girosc_ang_x_prev;
  girosc_ang_y = (gy/131)*dt/1000.0 + girosc_ang_y_prev;

  girosc_ang_x_prev=girosc_ang_x;
  girosc_ang_y_prev=girosc_ang_y;

  Serial.print("Rotation on X:  ");
  Serial.print(girosc_ang_x); 
  Serial.print("    Rotation on Y: ");
  Serial.println(girosc_ang_y);

  delay(100);
}
