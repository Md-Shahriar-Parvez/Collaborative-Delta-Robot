#include "AS5600.h"
#include "Wire.h"

AS5600 as5600_1;
AS5600 as5600_2;   
AS5600 as5600_3;   

int a1;
float b1;
int a2;
float b2;
int a3;
float b3;

void TCA9548A(uint8_t bus)
{
  Wire.beginTransmission(0x70);
  Wire.write(1<<bus);
  Wire.endTransmission();
}

void setup()
{
  Serial.begin(38400);

//  pinMode(26,OUTPUT);
//
//  digitalWrite(26,HIGH);

  TCA9548A(0);
  as5600_1.begin(24);  
  as5600_1.setDirection(AS5600_CLOCK_WISE); 

  TCA9548A(1);
  as5600_2.begin(30);  
  as5600_2.setDirection(AS5600_CLOCK_WISE); 

  TCA9548A(2);
  as5600_3.begin(32);  
  as5600_3.setDirection(AS5600_CLOCK_WISE); 
}

void loop()
{
  TCA9548A(0);
  a1=as5600_1.rawAngle();
  b1=as5600_1.rawAngle() * AS5600_RAW_TO_DEGREES;

  TCA9548A(1);
  a2=as5600_2.rawAngle();
  b2=as5600_2.rawAngle() * AS5600_RAW_TO_DEGREES;

  TCA9548A(2);
  a3=as5600_3.rawAngle();
  b3=as5600_3.rawAngle() * AS5600_RAW_TO_DEGREES;
 
  Serial.print(b1);
  Serial.print("\t");
  Serial.print(b2);
  Serial.print("\t");
  Serial.println(b3);
  delay(500);
}
