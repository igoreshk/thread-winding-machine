
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd( 0x27 , 16 , 2 );

const int pinStep = 5; // Pin connected to STEP
const int pinDir = 4; // Pin Connected to DIR
const int buttonPin = 8; // Button Pin
const int analogInPin = A1; // Rotations
const int delayInPin = A2;

int sensorValue = 0; // Reading from Reostst
int delaySensorValue = 0; //Reading from Reostat

int Count = 2; // Rotation count
char *s;

int move_delay = 300; // Delay metween steps (microsec)

const int steps_rotate_360 = 200; // Steps for 360 degree rotete
int buttonState = 0; // State of button
const int btn_1_value = 350; // Values from buttos
const int btn_2_value = 442;
const int btn_3_value = 618;
const int btn_4_value = 833;

const int btn_plus_value = 508;
const int btn_minus_value = 390;
const int btn_acc = 10; // Accuracy of reading
const int cassete_length = 24;

const int length_1 = 45;
const int length_2 = 60;
const int length_3 = 75;
const int length_4 = 210;
const int lengt_aj = 1;
int Length = 30;

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
   Length = 30;
}

void loop()
{

  buttonState = digitalRead(buttonPin);
  sensorValue = analogRead(analogInPin);
  delaySensorValue = analogRead(delayInPin);
  
  // Count = map(sensorValue, 0, 1023, 200, 700);
  move_delay = map(delaySensorValue, 0, 1023, 300, 1300);
  // sprintf(s,"Rotations: %d",Count);
  // lcd.setCursor(1,0);
  // lcd.print("Rotations: "+(String)((float)Count/100));
  // lcd.setCursor(1,1);

  if ((sensorValue > btn_1_value - btn_acc ) && (sensorValue < btn_1_value + btn_acc )) Length=length_1;
  if ((sensorValue > btn_2_value - btn_acc ) && (sensorValue < btn_2_value + btn_acc )) Length=length_2;
  if ((sensorValue > btn_3_value - btn_acc ) && (sensorValue < btn_3_value + btn_acc )) Length=length_3;
  if ((sensorValue > btn_4_value - btn_acc ) && (sensorValue < btn_4_value + btn_acc )) Length=length_4;
  
  if ((sensorValue > btn_plus_value - btn_acc ) && (sensorValue < btn_plus_value + btn_acc )) { Length++; delay(300);};
  if ((sensorValue > btn_minus_value - btn_acc ) && (sensorValue < btn_minus_value + btn_acc )) { Length--; delay(300);};  
  Count = (Length*100)/cassete_length;

   lcd.setCursor(1,0);
   lcd.print("Length: "+(String)(Length)+" sm");
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
        delayMicroseconds(50);
//      delayMicroseconds(250);
//      delayMicroseconds(move_delay);
      digitalWrite(pinStep, LOW);
      delayMicroseconds(move_delay);
 //     delayMicroseconds(move_delay);
      }
  }
//  delay(move_delay*10);


//  delay(move_delay*10);
}
