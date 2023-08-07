#include<Wire.h>
const int MPU=0x68;  
int16_t AcX,AcY,AcZ;
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
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,6,true);  
  AcX=Wire.read()<<8|Wire.read();      
  AcY=Wire.read()<<8|Wire.read(); 
  AcZ=Wire.read()<<8|Wire.read();  
  
  //Serial.print("Accelerometer: ");
  Serial.print("X :"); Serial.print(AcX);Serial.print(",");
  Serial.print("Y :"); Serial.print(AcY);Serial.print(",");
  Serial.print("Z :"); Serial.println(AcZ);  

}
