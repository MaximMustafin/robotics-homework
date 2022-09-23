#include <SoftwareSerial.h> 
#include <ctype.h>
#include <stdio.h>

const int ENA = 5;
const int ENB = 6;
const int IN1 = 7;
const int IN2 = 8;
const int IN3 = 9;
const int IN4 = 10;

int power = 180;

SoftwareSerial blue(2, 3); // RX | TX

void setup()  
{
  Serial.begin(9600);
  blue.begin(9600);  //Default Baud for comm, it may be different for your Module. 
  Serial.println("The bluetooth gates are open.\n Connect to HC-05 from any other bluetooth device with 1234 as pairing key!.");

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop()
{
  if (blue.available())
  {
    auto comm = blue.read();

    switch(comm)
    {
      case 'f':
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, HIGH);   
        digitalWrite(IN4, LOW);   
        move();
        break;
      case 'b':
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, LOW);   
        digitalWrite(IN4, HIGH);
        move();
        break;
      case 'l':
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, HIGH);   
        digitalWrite(IN4, LOW); 
        move(); 
        break;
      case 'r':
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);   
        digitalWrite(IN4, HIGH);  
        move();
        break;        
      case 'p':      
        power = 255;
        break;
      case 'm':
        power = 180;      
      case 'w':
        power = 100;
        break;
    } 
     
  }
 
}

void move()
{
  unsigned long start = millis();
  unsigned long end = start;  


    while(end - start <= 3000)
    {  
       if(blue.read() == 's')
       {
          break;       
       }
       else
       {
         analogWrite(ENA, power);
         analogWrite(ENB, power);
       }   

       end = millis(); 
    }    
     
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}


