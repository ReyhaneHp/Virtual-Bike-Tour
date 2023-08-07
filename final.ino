// Basic demo for accelerometer readings from Adafruit MPU6050

#include <BluetoothSerial.h>
#include <Adafruit_MPU6050.h>
//#include <Adafruit_Sensor.h>
#include <Wire.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

Adafruit_MPU6050 mpu;

#define LED 26

int acceleration[2][2];
float acc_eq;
int Acc_eq;
float teta_acc;

void setup(void) {
  pinMode (LED, OUTPUT);
  Serial.begin(115200);
  SerialBT.begin("VirtualBike"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_1000_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break; 
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }

  Serial.println("");
  delay(100);

  // acceleration[0][j] is x
  // acceleration[1][j] is y
  // acceleration[2][j] is z
  
    /*______________define t=0 acceleration______________*/
  acceleration[0][0]= 0;
  acceleration[1][0]= 0;
  acceleration[2][0]= 0;
}

void loop() {

  /* _______Get new sensor events with the readings_______ */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  digitalWrite(LED,LOW);
  
  /*______________Offset______________*/  
  a.acceleration.x = a.acceleration.x - 0.01;
  a.acceleration.y = a.acceleration.y - 0.02;
  a.acceleration.z = a.acceleration.z - 7.4;

  /*______________define______________*/
  acceleration[0][1]= a.acceleration.x;
  acceleration[1][1]= a.acceleration.y;
  acceleration[2][1]= a.acceleration.z;
 
  /*______________Print out the values______________*/  
  /*Serial.print("Acceleration X: ");
  Serial.println(a.acceleration.x);
  Serial.print(" Y: ");
  Serial.println(a.acceleration.y);
  Serial.print(" Z: ");
  Serial.print(a.acceleration.z);
  Serial.println(" m/s^2");
  
  /*______________speed______________*/

  /*SerialBT.print("X: ");
  SerialBT.println(acceleration[0][0]);
  SerialBT.print("Y: ");
  SerialBT.println(acceleration[1][0]);
  SerialBT.print("Z: ");
  SerialBT.println(acceleration[2][0]);*/

  
  acc_eq = (sqrt((acceleration[0][1]*acceleration[0][1])+(acceleration[1][1]*acceleration[1][1])+(acceleration[2][1]*acceleration[2][1]))); 

  
  /*______________maping into 0 to 9______________*/  
  Acc_eq = map(acc_eq, 0, 80, 0, 9);

  char btbuffer[7]={0};
  //sprintf(btbuffer,":%dY*\r\n",Acc_eq);
  Serial.print("Speed:");
  Serial.println(Acc_eq);
  //SerialBT.println(Acc_eq);
  
  //Serial.println("");

  /*______________Bluetooth______________*/ 

  /*SerialBT.println("Acceleration: ");
  SerialBT.print(" X: ");
  SerialBT.print(a.acceleration.x);
  SerialBT.println(" m/s^2");
  SerialBT.print(" Y: ");
  SerialBT.print(a.acceleration.y);
  SerialBT.println(" m/s^2");
  SerialBT.print(" Z: ");
  SerialBT.print(a.acceleration.z);
  SerialBT.println(" m/s^2");
//SerialBT.println("");
  */
//  teta_acc= atan( acceleration[1][1]/acceleration[2][1]);
//  Serial.print(" teta_acc ");
//  SerialBT.println(teta_acc);
  
  delay(100);
}
