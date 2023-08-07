#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

MPU6050 sensor;

int ax, ay, az;
int gx, gy, gz;

void setup() {
  Serial.begin(57600);  
  Wire.begin();        
  sensor.initialize(); 

  if (sensor.testConnection()) Serial.println("Sensor started correctly");
  else Serial.println("Error starting sensor");
}

void loop() {

  sensor.getAcceleration(&ax, &ay, &az);
  sensor.getRotation(&gx, &gy, &gz);

  Serial.print("a[x y z] g[x y z]:");
  Serial.print(ax); Serial.print("   ");
  Serial.print(ay); Serial.print("   ");
  Serial.print(az); Serial.print("   ");
  Serial.print(gx); Serial.print("   ");
  Serial.print(gy); Serial.print("   ");
  Serial.println(gz);

  delay(2000);
}
