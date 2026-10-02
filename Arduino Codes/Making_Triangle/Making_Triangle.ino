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
float T=0.5;

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

void TCA9548A(uint8_t bus)
{
  Wire.beginTransmission(0x70);
  Wire.write(1<<bus);
  Wire.endTransmission();
}

void setup()
{
  float x[10]={-7.5,-2.5,2.5,7.5,5,2.11,0,-2.11,-5,-7.5};
  float y[10]={-4.33,-4.33,-4.33,-4.33,0,5,8.66,5,0,-4.33};
  float z=-25;
  float p;
  float q;
  float r;
  float ps;
  float qs;
  float rs;
  float pd;
  float qd;
  float rd;
//  int itn;

//  Serial.begin(38400);

  delay(2000);
  
  steppersControl.addStepper(stepper1);
  steppersControl.addStepper(stepper2);
  steppersControl.addStepper(stepper3);

//  stepper1.setMaxSpeed(1000);
//  stepper2.setMaxSpeed(1000);
//  stepper3.setMaxSpeed(1000);

  pinMode(8,OUTPUT);
  digitalWrite(8,LOW);
  delay(3000);

  TCA9548A(0);
  as5600_1.begin(24);  
  as5600_1.setDirection(AS5600_CLOCK_WISE); 
  a1=as5600_1.rawAngle();
  b1=as5600_1.rawAngle() * AS5600_RAW_TO_DEGREES;
  c1=b1-172;

  TCA9548A(1);
  as5600_2.begin(30);  
  as5600_2.setDirection(AS5600_CLOCK_WISE); 
  a2=as5600_2.rawAngle();
  b2=as5600_2.rawAngle() * AS5600_RAW_TO_DEGREES;
  c2=b2-168;

  TCA9548A(2);
  as5600_3.begin(32);  
  as5600_3.setDirection(AS5600_CLOCK_WISE); 
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

  delay(4000);

  angle_1=angle1(x[0],y[0],-20);
  if(!(angle_1>360))
  {
  angle_2=angle2(x[0],y[0],-20);
    if(!(angle_2>360))
    {
        angle_3=angle3(x[0],y[0],-20);
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

 for(int i=0;i<10;i++)
 {
   angle_1=angle1(x[i],y[i],z);
  if(!(angle_1>360))
  {
  angle_2=angle2(x[i],y[i],z);
    if(!(angle_2>360))
    {
        angle_3=angle3(x[i],y[i],z);
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
  delay(100);
 }

   angle_1=angle1(x[9],y[9],-20);
  if(!(angle_1>360))
  {
  angle_2=angle2(x[9],y[9],-20);
    if(!(angle_2>360))
    {
        angle_3=angle3(x[9],y[9],-20);
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
  delay(100);

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
