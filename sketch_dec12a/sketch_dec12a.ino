#include <Wire.h>
#define accel_module (0x53)
byte values[6];
char output[512];
           
void setup() {
  Wire.begin();
  Serial.begin(9600);
  Wire.beginTransmission(accel_module);
  Wire.write(0x2D);
  Wire.write(0);
  Wire.endTransmission();
  Wire.beginTransmission(accel_module);
  Wire.write(0x2D);
  Wire.write(16);
  Wire.endTransmission();
  Wire.beginTransmission(accel_module);
  Wire.write(0x2D);
  Wire.write(8);
  Wire.endTransmission();
  
}



void loop() {
  int x, y, z;
  int xyzregister = 0x32;

  Wire.beginTransmission(accel_module);
  Wire.write(xyzregister);
  Wire.endTransmission();

  Wire.beginTransmission(accel_module);
  Wire.requestFrom(accel_module, 6);

  int i = 0;
  while (Wire.available()) {
    values[i] = Wire.read();
    i++;
  }
  Wire.endTransmission();
  x = (((int)values[1]) << 8) | values[0];
  y = (((int)values[3]) << 8) | values[2];
  /*Serial.print((int) values[3]);
  Serial.print("   ");
  Serial.print(((int)values[3]) << 8);
  Serial.print("   ");
  Serial.print(values[2]);
  Serial.print("   ");
  Serial.print(y);
  Serial.println();*/
  z = (((int)values[5]) << 8) | values[4];

  Serial.println(255 << 8);
  
  //sprintf(output, "%d %d %d", x , y, z);
  //Serial.print(output);
  //Serial.write(10);

  delay(1000);
}
/*void cal() { 
  xCal = x;
  
  yCal = y;

  zCal = z;

} 
*/

