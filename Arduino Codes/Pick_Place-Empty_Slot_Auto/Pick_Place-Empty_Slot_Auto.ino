#include <AccelStepper.h>
#include <MultiStepper.h>
#include <AS5600.h>
#include <Wire.h>

AccelStepper stepper1(AccelStepper::DRIVER, 2, 5); 
AccelStepper stepper2(AccelStepper::DRIVER, 3, 6);
AccelStepper stepper3(AccelStepper::DRIVER, 4, 7);

MultiStepper steppersControl;

AS5600 as5600_1;
AS5600 as5600_2;   
AS5600 as5600_3;   

long gotoposition[3];

volatile float f=13.5;
volatile float e=6.75;
volatile float rf=11.5;
volatile float re=22.5;
float angle_1;
float angle_2;
float angle_3;
float T=1;

int a1;
float b1;
float c1;
int a2;
float b2;
float c2;
int a3;
float b3;
float c3;

float ag_dis1;
float ag_dis2;
float ag_dis3;

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
  float x[4];
  float y[4];
  float z[4];
  float z1=-20;
  float z2=-22;
  float p;
  float q;
  float r;
  float ps;
  float qs;
  float rs;
  float pd;
  float qd;
  float rd;

//  Serial.begin(38400);

  delay(2000);
   
  steppersControl.addStepper(stepper1);
  steppersControl.addStepper(stepper2);
  steppersControl.addStepper(stepper3);

  TCA9548A(0);
  as5600_1.begin(24);  
  as5600_1.setDirection(AS5600_CLOCK_WISE); 
 
  TCA9548A(1);
  as5600_2.begin(30);  
  as5600_2.setDirection(AS5600_CLOCK_WISE); 
  
  TCA9548A(2);
  as5600_3.begin(32);  
  as5600_3.setDirection(AS5600_CLOCK_WISE);

  pinMode(36,OUTPUT);
  pinMode(38,OUTPUT);

  pos_red();

  x[0]=p3;
  y[0]=q3;
  z[0]=r3;
  
  pinMode(8,OUTPUT);
  digitalWrite(8,LOW);
  delay(1000);
  digitalWrite(8,HIGH);

  pos_red();

  x[1]=p3;
  y[1]=q3;
  z[1]=r3;

  digitalWrite(8,LOW);
  delay(1000);
  digitalWrite(8,HIGH);

  pos_red();

  x[2]=p3;
  y[2]=q3;
  z[2]=r3;

  digitalWrite(8,LOW);
  delay(1000);
  digitalWrite(8,HIGH);

  pos_red();

  x[3]=p3;
  y[3]=q3;
  z[3]=r3;

  digitalWrite(8,LOW);
  delay(1000);
  digitalWrite(8,HIGH);

  delay(3000);
  digitalWrite(8,LOW);

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
      
  ag_dis1=-c1;
  ag_dis2=-c2;
  ag_dis3=-c3;
  
  p=ag_dis1/0.225;
  q=ag_dis2/0.225;
  r=ag_dis3/0.225;

  pd=round(p);
  qd=round(q);
  rd=round(r);

  ps=abs(round(p/T));
  qs=abs(round(q/T));
  rs=abs(round(r/T));

  stepper1.setMaxSpeed(ps);
  stepper2.setMaxSpeed(qs);
  stepper3.setMaxSpeed(rs);
  stepper1.setSpeed(ps);
  stepper2.setSpeed(qs);
  stepper3.setSpeed(rs);

  gotoposition[0] = pd;  
  gotoposition[1] = qd;
  gotoposition[2] = rd;

  steppersControl.moveTo(gotoposition); 
  steppersControl.runSpeedToPosition(); 

  stepper1.setCurrentPosition(0);
  stepper2.setCurrentPosition(0);
  stepper3.setCurrentPosition(0);

  delay(2000);

 for(int i=1;i<4;i++)
 {

  angle_1=angle1(x[i],y[i],z1);
  if(!(angle_1>360))
  {
  angle_2=angle2(x[i],y[i],z1);
    if(!(angle_2>360))
    {
        angle_3=angle3(x[i],y[i],z1);
    }
  }

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
  
  ag_dis1=angle_1-c1;
  ag_dis2=angle_2-c2;
  ag_dis3=angle_3-c3;
    
  p=ag_dis1/0.225;
  q=ag_dis2/0.225;
  r=ag_dis3/0.225;

  pd=round(p);
  qd=round(q);
  rd=round(r);
  
  ps=abs(round(p/T));
  qs=abs(round(q/T));
  rs=abs(round(r/T));

  stepper1.setMaxSpeed(ps);
  stepper2.setMaxSpeed(qs);
  stepper3.setMaxSpeed(rs);
  stepper1.setSpeed(ps);
  stepper2.setSpeed(qs);
  stepper3.setSpeed(rs);

  gotoposition[0] = pd;  
  gotoposition[1] = qd;
  gotoposition[2] = rd;

  steppersControl.moveTo(gotoposition); 
  steppersControl.runSpeedToPosition(); 
  stepper1.setCurrentPosition(0);
  stepper2.setCurrentPosition(0);
  stepper3.setCurrentPosition(0);
  delay(2000);
  
  digitalWrite(36,HIGH);
  digitalWrite(38,LOW);
  delay(1000);
  
   angle_1=angle1(x[i],y[i],z[i]);
  if(!(angle_1>360))
  {
  angle_2=angle2(x[i],y[i],z[i]);
    if(!(angle_2>360))
    {
        angle_3=angle3(x[i],y[i],z[i]);
    }
  }

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

  ag_dis1=angle_1-c1;
  ag_dis2=angle_2-c2;
  ag_dis3=angle_3-c3;
    
  p=ag_dis1/0.225;
  q=ag_dis2/0.225;
  r=ag_dis3/0.225;

  pd=round(p);
  qd=round(q);
  rd=round(r);
  
  ps=abs(round(p/T));
  qs=abs(round(q/T));
  rs=abs(round(r/T));

  stepper1.setMaxSpeed(ps);
  stepper2.setMaxSpeed(qs);
  stepper3.setMaxSpeed(rs);
  stepper1.setSpeed(ps);
  stepper2.setSpeed(qs);
  stepper3.setSpeed(rs);

  gotoposition[0] = pd;  
  gotoposition[1] = qd;
  gotoposition[2] = rd;

  steppersControl.moveTo(gotoposition); 
  steppersControl.runSpeedToPosition(); 
  stepper1.setCurrentPosition(0);
  stepper2.setCurrentPosition(0);
  stepper3.setCurrentPosition(0);
  delay(3000);
 
   angle_1=angle1(x[i],y[i],z1);
  if(!(angle_1>360))
  {
  angle_2=angle2(x[i],y[i],z1);
    if(!(angle_2>360))
    {
        angle_3=angle3(x[i],y[i],z1);
    }
  }

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

  ag_dis1=angle_1-c1;
  ag_dis2=angle_2-c2;
  ag_dis3=angle_3-c3;
    
  p=ag_dis1/0.225;
  q=ag_dis2/0.225;
  r=ag_dis3/0.225;

  pd=round(p);
  qd=round(q);
  rd=round(r);
  
  ps=abs(round(p/T));
  qs=abs(round(q/T));
  rs=abs(round(r/T));

  stepper1.setMaxSpeed(ps);
  stepper2.setMaxSpeed(qs);
  stepper3.setMaxSpeed(rs);
  stepper1.setSpeed(ps);
  stepper2.setSpeed(qs);
  stepper3.setSpeed(rs);

  gotoposition[0] = pd;  
  gotoposition[1] = qd;
  gotoposition[2] = rd;

  steppersControl.moveTo(gotoposition); 
  steppersControl.runSpeedToPosition(); 
  stepper1.setCurrentPosition(0);
  stepper2.setCurrentPosition(0);
  stepper3.setCurrentPosition(0);
  delay(1000);

  angle_1=angle1(x[i-1],y[i-1],z2);
  if(!(angle_1>360))
  {
  angle_2=angle2(x[i-1],y[i-1],z2);
    if(!(angle_2>360))
    {
        angle_3=angle3(x[i-1],y[i-1],z2);
    }
  }

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

  ag_dis1=angle_1-c1;
  ag_dis2=angle_2-c2;
  ag_dis3=angle_3-c3;
    
  p=ag_dis1/0.225;
  q=ag_dis2/0.225;
  r=ag_dis3/0.225;

  pd=round(p);
  qd=round(q);
  rd=round(r);
  
  ps=abs(round(p/T));
  qs=abs(round(q/T));
  rs=abs(round(r/T));

  stepper1.setMaxSpeed(ps);
  stepper2.setMaxSpeed(qs);
  stepper3.setMaxSpeed(rs);
  stepper1.setSpeed(ps);
  stepper2.setSpeed(qs);
  stepper3.setSpeed(rs);

  gotoposition[0] = pd;  
  gotoposition[1] = qd;
  gotoposition[2] = rd;

  steppersControl.moveTo(gotoposition); 
  steppersControl.runSpeedToPosition(); 
  stepper1.setCurrentPosition(0);
  stepper2.setCurrentPosition(0);
  stepper3.setCurrentPosition(0);
  delay(1000);

  digitalWrite(36,LOW);
  digitalWrite(38,LOW);
  delay(1000);
 }

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

  ag_dis1=-c1;
  ag_dis2=-c2;
  ag_dis3=-c3;
  
  p=ag_dis1/0.225;
  q=ag_dis2/0.225;
  r=ag_dis3/0.225;

  pd=round(p);
  qd=round(q);
  rd=round(r);

  ps=abs(round(p/T));
  qs=abs(round(q/T));
  rs=abs(round(r/T));

  stepper1.setMaxSpeed(ps);
  stepper2.setMaxSpeed(qs);
  stepper3.setMaxSpeed(rs);
  stepper1.setSpeed(ps);
  stepper2.setSpeed(qs);
  stepper3.setSpeed(rs);

  gotoposition[0] = pd;  
  gotoposition[1] = qd;
  gotoposition[2] = rd;

  steppersControl.moveTo(gotoposition); 
  steppersControl.runSpeedToPosition(); 

  stepper1.setCurrentPosition(0);
  stepper2.setCurrentPosition(0);
  stepper3.setCurrentPosition(0);

  delay(2000);
}

void loop()
{
//  TCA9548A(0);
//  a1=as5600_1.rawAngle();
//  b1=as5600_1.rawAngle() * AS5600_RAW_TO_DEGREES;
//
//  TCA9548A(1);
//  a2=as5600_2.rawAngle();
//  b2=as5600_2.rawAngle() * AS5600_RAW_TO_DEGREES;
//
//  TCA9548A(2);
//  a3=as5600_3.rawAngle();
//  b3=as5600_3.rawAngle() * AS5600_RAW_TO_DEGREES;
//
//  Serial.print(b1);
//  Serial.print("\t");
//  Serial.print(b2);
//  Serial.print("\t");
//  Serial.println(b3);
//  delay(500); 
  }

 float angle1(float x0,float y0,float z0)
{
  float a;
  float b;
  float c;
  float d;
  float m;
  float n;
  float g;
  float h;
  float i;
  float j;
  float k;
  float y;
  float z;
  float theta1=400;
  m=f/(2*sqrt(3));
  n=y0-e/sqrt(3);
  a=(-m-n)/z0;
  b=(rf*rf-re*re+x0*x0+z0*z0-m*m+n*n)/(2*z0);
  c=1+a*a;
  d=2*m+2*a*b;
  g=m*m+b*b-rf*rf;
  h=d*d-4*c*g;
  if(h>=0)
  { 
  i=sqrt(h);
  j=(-d+i)/(2*c);
  k=(-d-i)/(2*c);
  if(j<0 && k>0)
  {
    y=j;
  }
  else if(j>0 && k<0)
  {
    y=k;
  }
  else if(j<0 && k<0)
  {
    if(j>k)
    {
      y=k;
    }
    else if(k>j)
    {
      y=j;
    }
  }
  z=a*y+b;
  theta1=-(180/3.1416)*atan(z/(-m-y));
  if(z<0 && (theta1<0 && theta1>-90))
  {
    theta1=180+theta1;
  }
  }
  else
  {
//    Serial.println("The point can't be reached");
  }
  return theta1;
}

float angle2(float x0,float y0,float z0)
{
  float a;
  float b;
  float c;
  float d;
  float m;
  float n;
  float g;
  float h;
  float i;
  float j;
  float k;
  float y;
  float z;
  float theta2=400;
  float x1;
  float y1;
  x1=x0*cos(120*(3.1416/180))+y0*sin(120*(3.1416/180));
  y1=-x0*sin(120*(3.1416/180))+y0*cos(120*(3.1416/180));
  m=f/(2*sqrt(3));
  n=y1-e/sqrt(3);
  a=(-m-n)/z0;
  b=(rf*rf-re*re+x1*x1+z0*z0-m*m+n*n)/(2*z0);
  c=1+a*a;
  d=2*m+2*a*b;
  g=m*m+b*b-rf*rf;
  h=d*d-4*c*g;
  if(h>=0)
  {
  i=sqrt(h);
  j=(-d+i)/(2*c);
  k=(-d-i)/(2*c);
  if(j<0 && k>0)
  {
    y=j;
  }
  else if(j>0 && k<0)
  {
    y=k;
  }
  else if(j<0 && k<0)
  {
    if(j>k)
    {
      y=k;
    }
    else if(k>j)
    {
      y=j;
    }
  }
  z=a*y+b;
  theta2=-(180/3.1416)*atan(z/(-m-y));
  if(z<0 && (theta2<0 && theta2>-90))
  {
    theta2=180+theta2;
  }
  }
  else
  {
//    Serial.println("The point can't be reached");
  }
  return theta2;
}

float angle3(float x0,float y0,float z0)
{
  float a;
  float b;
  float c;
  float d;
  float m;
  float n;
  float g;
  float h;
  float i;
  float j;
  float k;
  float y;
  float z;
  float theta3=400;
  float x1;
  float y1;
  x1=x0*cos(240*(3.1416/180))+y0*sin(240*(3.1416/180));
  y1=-x0*sin(240*(3.1416/180))+y0*cos(240*(3.1416/180));
  m=f/(2*sqrt(3));
  n=y1-e/sqrt(3);
  a=(-m-n)/z0;
  b=(rf*rf-re*re+x1*x1+z0*z0-m*m+n*n)/(2*z0);
  c=1+a*a;
  d=2*m+2*a*b;
  g=m*m+b*b-rf*rf;
  h=d*d-4*c*g;
  if(h>=0)
  {
  i=sqrt(h);
  j=(-d+i)/(2*c);
  k=(-d-i)/(2*c);
  if(j<0 && k>0)
  {
    y=j;
  }
  else if(j>0 && k<0)
  {
    y=k;
  }
  else if(j<0 && k<0)
  {
    if(j>k)
    {
      y=k;
    }
    else if(k>j)
    {
      y=j;
    }
  }
  z=a*y+b;
  theta3=-(180/3.1416)*atan(z/(-m-y));
  if(z<0 && (theta3<0 && theta3>-90))
  {
    theta3=180+theta3;
  }
  }
  else
  {
//    Serial.println("The point can't be reached");
  }
  return theta3;
}

void pos_red()
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

  delay(1000);

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

  delay(1000);
  
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

  delay(1000);

  dp1=abs(p1-p2);
  dp2=abs(p2-p3);
  dq1=abs(q1-q2);
  dq2=abs(q2-q3);
  dr1=abs(r1-r2);
  dr2=abs(r2-r3);

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

  if((dp1>=0 && dp1<=0.5)&&(dp2>=0 && dp2<=0.5)&&(dq1>=0 && dq1<=0.5)&&(dq2>=0 && dq2<=0.5)&&(dr1>=0 && dr1<=0.5)&&(dr2>=0 && dr2<=0.5))
  {
    break;
  }
  }
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
