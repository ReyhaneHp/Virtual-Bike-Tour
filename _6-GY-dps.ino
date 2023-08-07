#include<Wire.h>
const int MPU=0x68;  
int16_t GyX,GyY,GyZ;
void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); 
  Wire.write(0);     
  Wire.endTransmission(true);
  Serial.begin(9600);
}
void loop(){
  Wire.beginTransmission(MPU);
  Wire.write(0x43); 
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,6,true);  
  GyX=Wire.read()<<8|Wire.read(); 
  GyY=Wire.read()<<8|Wire.read();  
  GyZ=Wire.read()<<8|Wire.read();  

  GyX=GyX/131;
  GyY=GyY/131;
  GyZ=GyZ/131;
  
  //Serial.print("Gyroscope: ");
  Serial.print("X:"); Serial.print(GyX);Serial.print(",");
  Serial.print("Y:"); Serial.print(GyY);Serial.print(",");
  Serial.print("Z:"); Serial.println(GyZ);
}
