#include <AS5600.h>
#include <Wire.h>

AS5600 as5600_1;
AS5600 as5600_2;   
AS5600 as5600_3; 

int a1;
float b1;
float c1;
int a2;
float b2;
float c2;
int a3;
float b3;
float c3;

float x;
float y;
float z;

volatile float f=13.5;
volatile float e=6.75;
volatile float rf=11.5;
volatile float re=22.5;

struct co_ordinate
{
  float a;
  float b;
  float c;
};

void TCA9548A(uint8_t bus)
{
  Wire.beginTransmission(0x70);
  Wire.write(1<<bus);
  Wire.endTransmission();
}

void setup()
{
  TCA9548A(0);
  as5600_1.begin(24);  
  as5600_1.setDirection(AS5600_CLOCK_WISE); 
 
  TCA9548A(1);
  as5600_2.begin(30);  
  as5600_2.setDirection(AS5600_CLOCK_WISE); 
  
  TCA9548A(2);
  as5600_3.begin(32);  
  as5600_3.setDirection(AS5600_CLOCK_WISE);  

  Serial.begin(38400);
}

void loop()
{
  TCA9548A(0);
  a1=as5600_1.rawAngle();
  b1=as5600_1.rawAngle() * AS5600_RAW_TO_DEGREES;
  c1=b1-172;

  TCA9548A(1);
  a2=as5600_2.rawAngle();
  b2=as5600_2.rawAngle() * AS5600_RAW_TO_DEGREES;
  c2=b2-166.5;

  TCA9548A(2);
  a3=as5600_3.rawAngle();
  b3=as5600_3.rawAngle() * AS5600_RAW_TO_DEGREES;
  c3=b3-174;
  
  co_ordinate pos2=delta_calcForward(c1,c2,c3);
  x=pos2.a;
  y=pos2.b;
  z=pos2.c;

//  Serial.print(c1);
//  Serial.print("\t");
//  Serial.print(c2);
//  Serial.print("\t");
//  Serial.println(c3);
  Serial.print(x);
  Serial.print("\t");
  Serial.print(y);
  Serial.print("\t");
  Serial.println(z);
  delay(500);
}

co_ordinate delta_calcForward(float theta1, float theta2, float theta3) 
 {       
     float x0;
     float y0;
     float z0;
     
     const float sqrt3 = sqrt(3.0);
     const float sin30 = 0.5;
     const float tan60 = sqrt3;
     
     float t = f/(2*sqrt3)-e/sqrt3;
     float dtr = 3.1416/180.0;
 
     theta1 *= dtr;
     theta2 *= dtr;
     theta3 *= dtr;
 
     float y1 = -(t + rf*cos(theta1));
     float z1 = -rf*sin(theta1);
 
     float y2 = (t + rf*cos(theta2))*sin30;
     float x2 = y2*tan60;
     float z2 = -rf*sin(theta2);
 
     float y3 = (t + rf*cos(theta3))*sin30;
     float x3 = -y3*tan60;
     float z3 = -rf*sin(theta3);
 
     float dnm = (y2-y1)*x3-(y3-y1)*x2;
 
     float w1 = y1*y1 + z1*z1;
     float w2 = x2*x2 + y2*y2 + z2*z2;
     float w3 = x3*x3 + y3*y3 + z3*z3;
     
     float a1 = (z2-z1)*(y3-y1)-(z3-z1)*(y2-y1);
     float b1 = -((w2-w1)*(y3-y1)-(w3-w1)*(y2-y1))/2.0;
 
     float a2 = -(z2-z1)*x3+(z3-z1)*x2;
     float b2 = ((w2-w1)*x3 - (w3-w1)*x2)/2.0;
 
     float a = a1*a1 + a2*a2 + dnm*dnm;
     float b = 2*(a1*b1 + a2*(b2-y1*dnm) - z1*dnm*dnm);
     float c = (b2-y1*dnm)*(b2-y1*dnm) + b1*b1 + dnm*dnm*(z1*z1 - re*re);
  
     float d = b*b - 4.0*a*c;
     if (d < 0) 
     {
     }
     else 
     {
     z0 = -0.5*(b+sqrt(d))/a;
     x0 = (a1*z0 + b1)/dnm;
     y0 = (a2*z0 + b2)/dnm;

     co_ordinate pos1;
     pos1.a=x0;
     pos1.b=y0;
     pos1.c=z0;

     return pos1;
     }
 }
