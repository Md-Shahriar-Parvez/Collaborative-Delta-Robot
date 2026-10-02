#include <AccelStepper.h>
#include <MultiStepper.h>

AccelStepper stepper1(AccelStepper::DRIVER, 2, 5); 
AccelStepper stepper2(AccelStepper::DRIVER, 3, 6);
AccelStepper stepper3(AccelStepper::DRIVER, 4, 7);

MultiStepper steppersControl;  

long gotoposition[3];

volatile float f=13.5;
volatile float e=6.75;
volatile float rf=11.5;
volatile float re=22.5;
float angle_1;
float angle_2;
float angle_3;
float p;
float q;
float r;
float ps;
float qs;
float rs;
float T=1;
int en=8;

void setup()
{
//  digitalWrite(en,HIGH);
  float x0;
  float y0;
  float z0;
  float pd;
  float qd;
  float rd;

  steppersControl.addStepper(stepper1);
  steppersControl.addStepper(stepper2);
  steppersControl.addStepper(stepper3);
  
  Serial.begin(38400);
  Serial.println("Enter the 'x' coordinate of the position: ");
  while(Serial.available()==0){}
  x0=Serial.parseFloat();
  Serial.println(x0);
  Serial.println("Enter the 'y' coordinate of the position: ");
  while(Serial.available()==0){}
  y0=Serial.parseFloat();
  Serial.println(y0);
  Serial.println("Enter the 'z' coordinate of the position: ");
  while(Serial.available()==0){}
  z0=Serial.parseFloat();
  Serial.println(z0);
  angle_1=angle1(x0,y0,z0);
  if(!(angle_1>360))
  {
  angle_2=angle2(x0,y0,z0);
    if(!(angle_2>360))
    {
        angle_3=angle3(x0,y0,z0);
    }
  }
  if(!(angle_1>360||angle_2>360||angle_3>360)) 
  {
  Serial.println("The values of respective angles are: ");
  Serial.println(angle_1);
  Serial.println(angle_2);
  Serial.println(angle_3);
  }
  pinMode(en,OUTPUT);
  digitalWrite(en,LOW);

  p=angle_1/0.225;
  q=angle_2/0.225;
  r=angle_3/0.225;

  pd=round(p);
  qd=round(q);
  rd=round(r);

  ps=abs(round(p/T));
  qs=abs(round(q/T));
  rs=abs(round(r/T));
  
  stepper1.setMaxSpeed(ps); 
  stepper1.setSpeed(ps);
  stepper2.setMaxSpeed(qs);
  stepper2.setSpeed(qs);
  stepper3.setMaxSpeed(rs);
  stepper3.setSpeed(rs);

//  steppersControl.addStepper(stepper1);
//  steppersControl.addStepper(stepper2);
//  steppersControl.addStepper(stepper3);

  gotoposition[0] = pd;  
  gotoposition[1] = qd;
  gotoposition[2] = rd;

  steppersControl.moveTo(gotoposition); 
  steppersControl.runSpeedToPosition(); 

  stepper1.setCurrentPosition(0);
  stepper2.setCurrentPosition(0);
  stepper3.setCurrentPosition(0);

  delay(2000);
  digitalWrite(en,HIGH);
}

void loop(){
//  gotoposition[0] = p;  
//  gotoposition[1] = q;
//  gotoposition[2] = r;
//
//  steppersControl.moveTo(gotoposition); 
//  steppersControl.runSpeedToPosition(); 
//  delay(300);
//
//  gotoposition[0] = 0;
//  gotoposition[1] = 0;
//  gotoposition[2] = 0;
//
//  steppersControl.moveTo(gotoposition);
//  steppersControl.runSpeedToPosition();
//
//  delay(300); 
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
