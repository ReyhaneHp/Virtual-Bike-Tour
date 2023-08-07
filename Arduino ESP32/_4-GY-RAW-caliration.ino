#include<Wire.h>
const int MPU = 0x68; 
double GyX, GyY, GyZ;
double GyX_off, GyY_off, GyZ_off;
int int_cal;

void setup() {
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  
  Wire.write(0);     
  Wire.endTransmission(true);
  Serial.begin(115200);

  for (int_cal = 0; int_cal < 2000; int_cal++) {
    GY_raw_data();
    GyX_off += GyX;
    GyY_off += GyY;
    GyZ_off += GyZ;
  }
  GyX_off = GyX_off / 2000;
  GyY_off = GyY_off / 2000;
  GyZ_off = GyZ_off / 2000;

  Serial.print(GyX_off);
  Serial.print("    ");
  Serial.print(GyY_off);
  Serial.print("    ");
  Serial.println(GyZ_off);
  delay(1000);
}

void loop() {
  GY_raw_data();

  Serial.print("Gyroscope: ");
  Serial.print("X = "); Serial.print(GyX);
  Serial.print(" | Y = "); Serial.print(GyY);
  Serial.print(" | Z = "); Serial.println(GyZ);

  delay(2000);
}

void GY_raw_data() {
  Wire.beginTransmission(MPU);
  Wire.write(0x43);  
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true); 
  GyX = Wire.read() << 8 | Wire.read(); 
  if (int_cal == 2000) GyX -= GyX_off;
  GyY = Wire.read() << 8 | Wire.read(); 
  if (int_cal == 2000) GyY -= GyY_off;
  GyZ = Wire.read() << 8 | Wire.read(); 
  if (int_cal == 2000) GyZ -= GyZ_off;
}
