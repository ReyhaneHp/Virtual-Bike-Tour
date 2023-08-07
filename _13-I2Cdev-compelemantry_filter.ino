#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
MPU6050 sensor;

int16_t ax, ay, az;
int16_t gx, gy, gz;

long tiempo_prev;
float dt;
float ang_x, ang_y;
float ang_x_prev, ang_y_prev;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  sensor.initialize();

  if (sensor.testConnection()) Serial.println("Sensor started correctly");
  else Serial.println("Error starting sensor");
}

void loop() {
  sensor.getAcceleration(&ax, &ay, &az);
  sensor.getRotation(&gx, &gy, &gz);

  dt = (millis() - tiempo_prev) / 1000.0;
  tiempo_prev = millis();

  float accel_ang_x = atan(ay / sqrt(pow(ax, 2) + pow(az, 2))) * (180.0 / 3.14);
  float accel_ang_y = atan(-ax / sqrt(pow(ay, 2) + pow(az, 2))) * (180.0 / 3.14);


  ang_x = 0.50 * (ang_x_prev + ((gx ) / 131) * 0.001) + 0.50 * accel_ang_x;
  ang_y = 0.98 * (ang_y_prev + (gy / 131) * dt) + 0.02 * accel_ang_y;

  ang_x_prev = ang_x;
  ang_y_prev = ang_y;

  Serial.print("X Angle:");
  Serial.print(accel_ang_x);
  Serial.print("Filtered X Angle :");
  Serial.println(ang_x);

  delay(10);
}
