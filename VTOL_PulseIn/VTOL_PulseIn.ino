#include <Servo.h>
Servo esc1, esc2;
int ch1, ch2, ch3;

void setup()
{
  pinMode(5, INPUT); // Signal for Throttle coming from the receiver (THRO)
  pinMode(6, INPUT); // Signal for Yaw coming from the receiver (AILE)
  pinMode(3, INPUT); // Signal for Pitch coming from the receiver (ELEV)
  esc1.attach(9); // Yellow, Green, Black //Top  motor
  esc2.attach(10); // Red, Green, Black //Bottom motor
  pinMode(9,OUTPUT); // assigned to ESC1
  pinMode(10,OUTPUT); // assigned to ESC2
  pinMode(11,OUTPUT); // assigned to the tail rotor
  Serial.begin(9600);
}

//////////////////////FUNCTIONS/////////////////////////
void calculateThrottle()
{
  ch1 = pulseIn(5, HIGH, 25000); // 25000 micro seconds, 1/40th seconds
  esc1.write(ch1);
  esc2.write(ch1);
}

void calculateYaw()
{
  ch2 = pulseIn(6, HIGH, 25000);
  if (ch2 < 1500)
  {
    int difference = 1500 - ch2;
    int newSpeed = ch1 - difference;
    esc1.write(newSpeed);
    esc2.write(ch1);
    //Serial.println("Yaw esc1: ");
    //Serial.println(newSpeed);
    //Serial.println("Yaw esc2: ");
    //Serial.println(ch1);
  }
  else if (ch2 >= 1500)
  {
    int difference = ch2 - 1500;
    int newSpeed = ch1 - difference;
    esc1.write(ch1);
    esc2.write(newSpeed);
    //Serial.println("Yaw esc1:" );
    //Serial.println(ch1);
    //Serial.println("Yaw esc2: ");
    //Serial.println(newSpeed);
  }
  else
  {
    esc1.write(ch1);
    esc2.write(ch1);
    //Serial.println("Middle");
  }   
}

void calculatePitch()
{
  ch3 = pulseIn(3, HIGH, 25000);
  
  if (ch3 > 1525)
  {  
  digitalWrite(11, HIGH); 
  //Serial.println("Pitch:" );
  //Serial.println(newSpeed);
  }
  else if (ch3 <= 1525);
  {
  digitalWrite(11, LOW);
  //Serial.println("Pitch:" );
  //Serial.println(newSpeed);
  }
}

//////////////////////LOOP/////////////////////////
void loop() 
{
  calculateThrottle();
  calculateYaw();
  //calculatePitch();
}


  
  
  
