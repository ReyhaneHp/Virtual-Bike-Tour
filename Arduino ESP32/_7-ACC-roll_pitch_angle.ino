#include <Wire.h>
#define MPU 0x68  

double AcX, AcY, AcZ;
int Pitch, Roll;

void setup() {
  Serial.begin(9600);
  init_MPU();
}
void loop() {
  FunctionsMPU(); 

  Roll = FunctionsPitchRoll(AcX, AcY, AcZ);  
  Pitch = FunctionsPitchRoll(AcY, AcX, AcZ); 

  Serial.print("Pitch:"); Serial.print(Pitch);Serial.print(",");
  //Serial.print("\t");
  Serial.print("Roll:"); Serial.println(Roll);
  //Serial.print("\n");
}
void init_MPU() {
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  
  Wire.write(0);    
  Wire.endTransmission(true);
  delay(1000);
}

double FunctionsPitchRoll(double A, double B, double C) {
  double DataA, DataB, Value;
  DataA = A;
  DataB = (B * B) + (C * C);
  DataB = sqrt(DataB);
  Value = atan2(DataA, DataB);
  Value = Value * 180 / 3.14;
  return (int)Value;
}

void FunctionsMPU() {
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true);
  AcX = Wire.read() << 8 | Wire.read(); 
  AcY = Wire.read() << 8 | Wire.read(); 
  AcZ = Wire.read() << 8 | Wire.read(); 
}
