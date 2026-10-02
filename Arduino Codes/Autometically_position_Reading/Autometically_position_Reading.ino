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
//float angle_1;
//float angle_2;
//float angle_3;

  float p1;
  float q1;
  float r1;
  float p2;
  float q2;
  float r2;
  float p3;
  float q3;
  float r3;
  float dp1;
  float dq1;
  float dr1;
  float dp2;
  float dq2;
  float dr2;

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
  
//  while(1)
//  {
//  TCA9548A(0); 
//  a1=as5600_1.rawAngle();
//  b1=as5600_1.rawAngle() * AS5600_RAW_TO_DEGREES;
//  c1=b1-172;
//
//  TCA9548A(1);
//  a2=as5600_2.rawAngle();
//  b2=as5600_2.rawAngle() * AS5600_RAW_TO_DEGREES;
//  c2=b2-168;
//
//  TCA9548A(2);
//  a3=as5600_3.rawAngle();
//  b3=as5600_3.rawAngle() * AS5600_RAW_TO_DEGREES;
//  c3=b3-174;
//  
//  co_ordinate pos2_1=delta_calcForward(c1,c2,c3);
//  p1=pos2_1.a;
//  q1=pos2_1.b;
//  r1=pos2_1.c;
//
//  delay(2000);
//
//  TCA9548A(0); 
//  a1=as5600_1.rawAngle();
//  b1=as5600_1.rawAngle() * AS5600_RAW_TO_DEGREES;
//  c1=b1-172;
//
//  TCA9548A(1);
//  a2=as5600_2.rawAngle();
//  b2=as5600_2.rawAngle() * AS5600_RAW_TO_DEGREES;
//  c2=b2-168;
//
//  TCA9548A(2);
//  a3=as5600_3.rawAngle();
//  b3=as5600_3.rawAngle() * AS5600_RAW_TO_DEGREES;
//  c3=b3-174;
//  
//  co_ordinate pos2_2=delta_calcForward(c1,c2,c3);
//  p2=pos2_2.a;
//  q2=pos2_2.b;
//  r2=pos2_2.c;
//
//  delay(2000);
//  
//  TCA9548A(0); 
//  a1=as5600_1.rawAngle();
//  b1=as5600_1.rawAngle() * AS5600_RAW_TO_DEGREES;
//  c1=b1-172;
//
//  TCA9548A(1);
//  a2=as5600_2.rawAngle();
//  b2=as5600_2.rawAngle() * AS5600_RAW_TO_DEGREES;
//  c2=b2-168;
//
//  TCA9548A(2);
//  a3=as5600_3.rawAngle();
//  b3=as5600_3.rawAngle() * AS5600_RAW_TO_DEGREES;
//  c3=b3-174;
//  
//  co_ordinate pos2_3=delta_calcForward(c1,c2,c3);
//  p3=pos2_3.a;
//  q3=pos2_3.b;
//  r3=pos2_3.c;
//
//  delay(2000);
//
//  dp1=abs(p1-p2);
//  dp2=abs(p2-p3);
//  dq1=abs(q1-q2);
//  dq2=abs(q2-q3);
//  dr1=abs(r1-r2);
//  dr2=abs(r2-r3);
//
//  Serial.print(dp1);
//  Serial.print("\t");
//  Serial.print(dp2);
//  Serial.print("\t");
//  Serial.print(dq1);
//  Serial.print("\t");
//  Serial.print(dq2);
//  Serial.print("\t");
//  Serial.print(dr1);
//  Serial.print("\t");
//  Serial.println(dr2);
//  delay(100);
//
//
//  if((dp1>=0 && dp1<=0.5)&&(dp2>=0 && dp2<=0.5)&&(dq1>=0 && dq1<=0.5)&&(dq2>=0 && dq2<=0.5)&&(dr1>=0 && dr1<=0.5)&&(dr2>=0 && dr2<=0.5))
//  {
//    break;
//  }
//  }
//  x=p3;
//  y=q3;
//  z=r3;
//
//  Serial.print(x);
//  Serial.print("\t");
//  Serial.print(y);
//  Serial.print("\t");
//  Serial.println(z);
}

void loop()
{
  while(1)
  {
  TCA9548A(0); 
  a1=as5600_1.rawAngle();
  b1=as5600_1.rawAngle() * AS5600_RAW_TO_DEGREES;
  c1=b1-172;

  TCA9548A(1);
  a2=as5600_2.rawAngle();
  b2=as5600_2.rawAngle() * AS5600_RAW_TO_DEGREES;
  c2=b2-168;

  TCA9548A(2);
  a3=as5600_3.rawAngle();
  b3=as5600_3.rawAngle() * AS5600_RAW_TO_DEGREES;
  c3=b3-174;
  
  co_ordinate pos2_1=delta_calcForward(c1,c2,c3);
  p1=pos2_1.a;
  q1=pos2_1.b;
  r1=pos2_1.c;

  delay(2000);

  TCA9548A(0); 
  a1=as5600_1.rawAngle();
  b1=as5600_1.rawAngle() * AS5600_RAW_TO_DEGREES;
  c1=b1-172;

  TCA9548A(1);
  a2=as5600_2.rawAngle();
  b2=as5600_2.rawAngle() * AS5600_RAW_TO_DEGREES;
  c2=b2-168;

  TCA9548A(2);
  a3=as5600_3.rawAngle();
  b3=as5600_3.rawAngle() * AS5600_RAW_TO_DEGREES;
  c3=b3-174;
  
  co_ordinate pos2_2=delta_calcForward(c1,c2,c3);
  p2=pos2_2.a;
  q2=pos2_2.b;
  r2=pos2_2.c;

  delay(2000);
  
  TCA9548A(0); 
  a1=as5600_1.rawAngle();
  b1=as5600_1.rawAngle() * AS5600_RAW_TO_DEGREES;
  c1=b1-172;

  TCA9548A(1);
  a2=as5600_2.rawAngle();
  b2=as5600_2.rawAngle() * AS5600_RAW_TO_DEGREES;
  c2=b2-168;

  TCA9548A(2);
  a3=as5600_3.rawAngle();
  b3=as5600_3.rawAngle() * AS5600_RAW_TO_DEGREES;
  c3=b3-174;
  
  co_ordinate pos2_3=delta_calcForward(c1,c2,c3);
  p3=pos2_3.a;
  q3=pos2_3.b;
  r3=pos2_3.c;

  delay(2000);

  dp1=abs(p1-p2);
  dp2=abs(p2-p3);
  dq1=abs(q1-q2);
  dq2=abs(q2-q3);
  dr1=abs(r1-r2);
  dr2=abs(r2-r3);

  Serial.print(dp1);
  Serial.print("\t");
  Serial.print(dp2);
  Serial.print("\t");
  Serial.print(dq1);
  Serial.print("\t");
  Serial.print(dq2);
  Serial.print("\t");
  Serial.print(dr1);
  Serial.print("\t");
  Serial.println(dr2);
  delay(100);


  if((dp1>=0 && dp1<=0.5)&&(dp2>=0 && dp2<=0.5)&&(dq1>=0 && dq1<=0.5)&&(dq2>=0 && dq2<=0.5)&&(dr1>=0 && dr1<=0.5)&&(dr2>=0 && dr2<=0.5))
  {
    break;
  }
  }
  x=p3;
  y=q3;
  z=r3;

  Serial.print(x);
  Serial.print("\t");
  Serial.print(y);
  Serial.print("\t");
  Serial.println(z);
  
//  TCA9548A(0); 
//  a1=as5600_1.rawAngle();
//  b1=as5600_1.rawAngle() * AS5600_RAW_TO_DEGREES;
//  c1=b1-172;
//
//  TCA9548A(1);
//  a2=as5600_2.rawAngle();
//  b2=as5600_2.rawAngle() * AS5600_RAW_TO_DEGREES;
//  if(b2>177 && b2<351.5)
//  {
//    c2=b2-351.5;
//  }
//  else if(b2>=351.5 && b2<360)
//  {
//    c2=b2-351.5;
//  }
//  else if(b2<177 && b2>=0)
//  {
//    c2=b2+(360-351.5);
//  }
//
//  TCA9548A(2);
//  a3=as5600_3.rawAngle();
//  b3=as5600_3.rawAngle() * AS5600_RAW_TO_DEGREES;
//  c3=b3-174;
//  
//  co_ordinate pos2=delta_calcForward(c1,c2,c3);
//  x=pos2.a;
//  y=pos2.b;
//  z=pos2.c;
//
//  Serial.print(c1);
//  Serial.print("\t");
//  Serial.print(c2);
//  Serial.print("\t");
//  Serial.println(c3);
//  Serial.print(x);
//  Serial.print("\t");
//  Serial.print(y);
//  Serial.print("\t");
//  Serial.println(z);
//  delay(500);
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
