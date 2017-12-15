#include <Wire.h>
#define accel_module (0x53)
byte values[6];
char output[512];
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin
int xCal;
int yCal;
int zCal;
int calX;
int calY;
int calZ;

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
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
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
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
  z = (((int)values[5]) << 8) | values[4];

  sprintf(output, "%d %d %d %d", x , y, z, buttonState);
  Serial.print(output);
  Serial.write(10);
  buttonState = digitalRead(buttonPin);
  if ( buttonState == 1) {
    digitalWrite(ledPin, 1);
//  cal();
  }
  else {
    digitalWrite(ledPin, 0);
  }
  delay(1000);
}
/*void cal() { 
  xCal = x;
  
  yCal = y;

  zCal = z;

} 
*/

