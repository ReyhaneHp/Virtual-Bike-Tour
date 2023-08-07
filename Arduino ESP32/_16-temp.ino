#include<Wire.h>
const int MPU=0x68;  
int16_t Tmp;

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
  Wire.write(0x41); 
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,2,true); 
  Tmp=Wire.read()<<8|Wire.read(); 

  Serial.print("Temperature: "); Serial.print(Tmp/340.00+36.53); Serial.println(" C "); 
 
  delay(333);
}

