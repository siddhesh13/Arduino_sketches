#include <Wire.h>

long accelX, accelY, accelZ;
float gForceX, gForceY, gForceZ;

long gyroX, gyroY, gyroZ;
float rotX, rotY, rotZ;
float gyroX_cal, gyroY_cal, gyroZ_cal;
float angle_pitch, angle_roll;
float angle_roll_acc, angle_pitch_acc;
float angle_pitch_output, angle_roll_output;

unsigned long previousMillis = 0;
unsigned int count=0;
long loop_timer;
void setup(){
  Serial.begin(9600);
  Wire.begin();
  setupMPU();
  delay(1000);
  Serial.println("caliberating MPU6050");
  for(int i=0; i<2000; i++){
    if(i %125 == 0) Serial.print(".");
    recordGyroRegisters();
    gyroX_cal += gyroX;
    gyroY_cal += gyroY;
    gyroZ_cal += gyroZ;
    delay(3);
  }
  gyroX_cal /= 2000;
  gyroY_cal /= 2000;
  gyroZ_cal /= 2000;
  Serial.print("gyroX_cal: ");
  Serial.print(gyroX_cal);
  Serial.print("  gyroY_cal: ");
  Serial.print(gyroY_cal);
  Serial.print("  gyroZ_cal: ");
  Serial.print(gyroZ_cal);
  delay(2000);
  loop_timer = micros();
}

void loop(){
  count= count+1;
  recordAccelRegisters();
  recordGyroRegisters();
  
  gyroX -= gyroX_cal;
  gyroY -= gyroY_cal;
  gyroZ -= gyroZ_cal;
  //printData();
  angle_pitch += gyroX * 0.0002443;
  angle_roll += gyroY * 0.0002443;

   //0.000001066 = 0.0000611 * (3.142(PI) / 180degr) The Arduino sin function is in radians
  angle_pitch += angle_roll * sin(gyroZ * 0.000004261);               //If the IMU has yawed transfer the roll angle to the pitch angel
  angle_roll -= angle_pitch * sin(gyroZ * 0.000004261);               //If the IMU has yawed transfer the pitch angle to the roll angel
  
  // Serial.print("X: ");
  Serial.println(angle_pitch);
  //Serial.print("  ");
  Serial.println(angle_roll);
 /* if(millis() - previousMillis  > 1000){
    Serial.print("count: ");
    Serial.println(count);
    count =0;
    previousMillis = millis(); 
   }*/
   //delay(2);

   while(micros() - loop_timer < 4000);
    loop_timer = micros();
  
  //Serial.print("mil");
  //Serial.println(micros()-loop_timer); 
  //loop_timer = micros();
  }
  
void setupMPU(){
  Wire.beginTransmission(0b1101000);
  Wire.write(0x6B);
  Wire.write(0b00000000);
  Wire.endTransmission();
  Wire.beginTransmission(0b1101000);
  Wire.write(0x1B);
  Wire.write(0x08);
  Wire.endTransmission();
  Wire.beginTransmission(0b1101000);
  Wire.write(0x1C);
  Wire.write(0x10);
  Wire.endTransmission();
}

void recordAccelRegisters(){
  Wire.beginTransmission(0b1101000);
  Wire.write(0x3B);
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6);
  while(Wire.available() < 6);
  accelX = Wire.read() << 8 | Wire.read();
  accelY = Wire.read() << 8 | Wire.read();
  accelZ = Wire.read() << 8 | Wire.read();
  //processAccelData();
}

void processAccelData(){
  gForceX = accelX / 16384.0;
  gForceY = accelY / 16384.0;
  gForceZ = accelZ / 16384.0;
}

void recordGyroRegisters(){
  Wire.beginTransmission(0b1101000);
  Wire.write(0x43);
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6);
  gyroX = Wire.read() << 8 | Wire.read();
  gyroY = Wire.read() << 8 | Wire.read();
  gyroZ = Wire.read() << 8 | Wire.read();
  //processGyroData();
}

void processGyroData(){
  rotX = gyroX / 131.0;
  rotY = gyroY / 131.0;
  rotZ = gyroZ / 131.0;
}

void printData(){
  Serial.print("Gyro:  ");
  Serial.print("X: ");
  Serial.print(gyroX);
  Serial.print(" Y: ");
  Serial.print(gyroY);
  Serial.print(" Z: ");
  Serial.println(gyroZ);
  /*
  Serial.print(" Accel(g):  ");
  Serial.print("X: ");
  Serial.print(gForceX);
  Serial.print(" Y: ");
  Serial.print(gForceY);
  Serial.print(" Z: ");
  Serial.println(gForceZ);*/
}
