#include <Wire.h>
#include <MPU6050.h>
#include <KalmanFilter.h>
#include <BluetoothSerial.h>

MPU6050 mpu;

KalmanFilter kalmanX(1, 1, 0.02);
KalmanFilter kalmanY(0.001, 1, 0.03);


BluetoothSerial SerialBT;

int cal = 0;

float gyroX = 0;

float accPitch = 0;
float accRoll = 0;

float kalPitch = 0;
float kalRoll = 0;

void setup()
{
  Serial.begin(115200);

  //Serial.println("Initialization MPU6050");
  while (!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    //Serial.println("Not found MPU6050!");
    delay(500);
  }

  mpu.calibrateGyro();
}

void loop()  {

  Vector acc = mpu.readNormalizeAccel();
  Vector gyr = mpu.readNormalizeGyro();
  
  gyroX = gyr.XAxis;


  if (!(gyroX < -1000))
  {
    accRoll  = (atan2(acc.YAxis, acc.ZAxis) * 180.0) / M_PI;
    kalRoll = kalmanX.update(accRoll, accRoll);

    Serial.print("Roll:");
    Serial.print(accRoll);
    Serial.print(",");
    Serial.print("(K)Roll:");
    Serial.println(kalRoll);
  }

  // accPitch = -(atan2(acc.XAxis, sqrt(acc.YAxis * acc.YAxis + acc.ZAxis * acc.ZAxis)) * 180.0) / M_PI;
  // kalPitch = kalmanY.update(accPitch, gyr.YAxis);

  //  for (cal = 0; cal < 2000; cal++)
  //  {
  //    Vector acc = mpu.readNormalizeAccel();
  //    accRoll  = (atan2(acc.YAxis, acc.ZAxis) * 180.0) / M_PI;
  //    accRoll += accRoll;
  //
  //  }
  //  accRoll = accRoll / 2000;


  //  Serial.print("acc.XAxis: ");
  //  Serial.print(acc.YAxis);
  //  Serial.print(" ");
  //  Serial.print("acc.YAxis: ");
  //  Serial.print(acc.YAxis);
  //  Serial.print(" ");
  //  Serial.print("acc.ZAxis ");
  //  Serial.print(acc.ZAxis);

  //  Serial.print("Pitch = ");
  //  Serial.print(accPitch);

  //
  //  Serial.print("gyroX:");
  //  Serial.println(gyroX);


  //  Serial.print(" (K)Pitch = ");
  //  Serial.print(kalPitch);
  // Serial.print(accRoll);

  delay(1000);
  // Serial.println();
}
