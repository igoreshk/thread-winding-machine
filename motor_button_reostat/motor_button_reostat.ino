
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd( 0x27 , 16 , 2 );

const int pinStep = 5; // Pin connected to STEP
const int pinDir = 4; // Pin Connected to DIR
const int buttonPin = 8; // Button Pin
const int analogInPin = A2; // Rotations
const int delayInPin = A3; // Delay

int sensorValue = 0; // Reading from Reostst
int delaySensorValue = 0; //Reading from Reostat

int Count = 2; // Rotation count
char *s;

int move_delay = 300; // Delay metween steps (microsec)

const int steps_rotate_360 = 200; // Steps for 360 degree rotete
int buttonState = 0; // State of button

void setup()
{
// Pin modes
  pinMode(pinStep, OUTPUT);
  pinMode(pinDir, OUTPUT);
  pinMode(buttonPin, INPUT);
// Initial state
  digitalWrite(pinStep, HIGH);
  digitalWrite(pinDir, HIGH);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(1,0); 
   lcd.display();
   pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{

  buttonState = digitalRead(buttonPin);
  sensorValue = analogRead(analogInPin);
  delaySensorValue = analogRead(delayInPin);
  Count = map(sensorValue, 0, 1023, 200, 700);
  move_delay = map(delaySensorValue, 0, 1023, 300, 1300);
  //sprintf(s,"Rotations: %d",Count);
  lcd.setCursor(1,0);
  lcd.print("Rotations: "+(String)((float)Count/100));
  lcd.setCursor(1,1);
  
  lcd.print("Delay: "+(String)(move_delay)+" ");
   lcd.display();

  if (buttonState == HIGH) {
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(pinDir, HIGH); //Direction
//     lcd.setCursor(1,1);
  //   lcd.print("------- rotating -------");
    // lcd.display();
 
    for(int i = 0; i < steps_rotate_360*Count/100; i++)
      {
      digitalWrite(pinStep, HIGH);
      delayMicroseconds(move_delay);
      digitalWrite(pinStep, LOW);
      delayMicroseconds(move_delay);
      }
  }
//  delay(move_delay*10);


//  delay(move_delay*10);
}
