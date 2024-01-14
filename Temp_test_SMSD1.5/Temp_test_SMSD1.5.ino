
#include <Wire.h>

const int pinStep = 5;      // Pin connected to STEP
const int pinDir = 3;       // Pin Connected to DIR
const int buttonPin = 8;    // Button START Pin
const int pinEn = 2;
const int freeDelay = 10000; // Delay between rotations (ms)

int Count = 2; // Rotation count

int move_delay = 900;    // Delay metween steps (microsec)

const int steps_rotate_360 = 200; // Steps for 360 degree rotete (200 for 1.8 degree motors)
const int cassete_length = 24;

int Length = 150; // Initial length
int buttonState = 0; // State of button

void setup()
{

  pinMode(pinStep, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(pinEn, OUTPUT);
  digitalWrite(pinEn, LOW);

}

void loop()
{
  
  int steps = 0; // Steps for current rotation
  
  buttonState = digitalRead(buttonPin);
  Count = (Length*100)/cassete_length;

  delay(300);

  if (buttonState == HIGH) {

    steps = steps_rotate_360*Count/100 ;
    

    while (not digitalRead(buttonPin)) {
      digitalWrite(pinEn, HIGH);
      for(int i = 0; i < steps; i++)
          {
        
          digitalWrite(pinStep, LOW);
          delayMicroseconds(150);
          digitalWrite(pinStep, HIGH);
          delayMicroseconds(move_delay);
          }
      digitalWrite(pinEn, LOW);
      delay(freeDelay);
    }

  

  }
}
