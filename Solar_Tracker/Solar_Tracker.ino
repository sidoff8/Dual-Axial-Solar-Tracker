
#include <Servo.h> // include Servo library 

// 180 horizontal MAX
Servo horizontal; // horizontal servo
int servoh = 0;   // 90;     // stand horizontal servo

int servohLimitHigh = 150;
int servohLimitLow = 0;

// 65 degrees MAX
Servo vertical;   // vertical servo 
int servov = 70;    //   90;     // stand vertical servo

int servovLimitHigh = 180;
int servovLimitLow = 0;


// LDR pin connections
//  name  = analogpin;
int ldrlt = 0; //LDR top left - BOTTOM LEFT    <--- BDG
int ldrrt = 1; //LDR top rigt - BOTTOM RIGHT 
int ldrld = 2; //LDR down left - TOP LEFT
int ldrrd = 3; //ldr down rigt - TOP RIGHT

void setup()
{
  Serial.begin(115200);
// servo connections
// name.attacht(pin);
  horizontal.attach(8); 
  vertical.attach(9);
  horizontal.write(20);
  vertical.write(30);
  delay(3000);
}

void loop() 
{
  int lt = analogRead(ldrlt); // top left
  int rt = analogRead(ldrrt); // top right
  int ld = analogRead(ldrld); // down left
  int rd = analogRead(ldrrd); // down rigt0
  Serial.print(" lt :");
  Serial.println(lt);
  Serial.print(" rt :");
  Serial.println(rt);
  Serial.print(" ld :");
  Serial.println(ld);
  Serial.print(" rd :");
  Serial.println(rd);
  
  // int dtime = analogRead(4)/20; // read potentiometers  
  // int tol = analogRead(5)/4;
  int dtime = 10;
  int tol = 20;
  
  int avt = (lt + rt) / 2; // average value top
  int avd = (ld + rd) / 2; // average value down
  int avl = (lt + ld) / 2; // average value left
  int avr = (rt + rd) / 2; // average value right

  int dvert = avt - avd; // check the diffirence of up and down
  int dhoriz = avl - avr;// check the diffirence og left and rigt
  
  
 
  
    
  if (-1*tol > dvert || dvert > tol) // check if the diffirence is in the tolerance else change vertical angle
  {
  if (avt > avd)
  {
    servov= --servov;
    if (servov < servovLimitLow)
    {
    servov = servovLimitLow;
   }
  }
  else if (avt < avd)
  {
    servov = ++servov;
     if (servov > servovLimitHigh) 
     { 
      servov = servovLimitHigh;
     }
  }
  vertical.write(servov);
  }
  
  if (-1*tol > dhoriz || dhoriz > tol) // check if the diffirence is in the tolerance else change horizontal angle
  {
  if (avl > avr)
  {
    servoh = ++servoh;
     if (servoh > servohLimitHigh)
     {
     servoh = servohLimitHigh;
     }
  }
  else if (avl < avr)
  {
     servoh = --servoh;
    if (servoh < servohLimitLow)
    {
    servoh = servohLimitLow;
    }
  }
  else if (avl = avr)
  {
    // nothing
  }
  horizontal.write(servoh);
  }
   delay(dtime);

}
