
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//#define DEBUG


LiquidCrystal_I2C lcd( 0x27 , 16 , 2 );

const int pinStep = 5;      // Pin connected to STEP
const int pinDir = 3;       // Pin Connected to DIR
const int pinEn = 2;        // Pin Connected to ENABLE
const int buttonPin = 8;    // Button START Pin
const int stopPin = 7;      // Button STOP Pin 
const int analogInPin = A1; // Keys Pin
const int delayInPin = A2;  // Speed potenciometer
const int SmoothSteps = 20;   // Steps for smooth start
const int StartSmoothDelay = 1500;

int sensorValue = 0; // Reading from Reostst
int delaySensorValue = 0; //Reading from Reostat


int Count = 2; // Rotation count
char *s;

int move_delay = 600; // Delay metween steps (microsec)
int smooth_move_delay = move_delay; // Delay after smooth corection

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
const int length_4 = 90;

int Length = 240;

void setup()
{

#ifdef DEBUG
  Serial.begin(9600);
#endif
  
// Pin modes
  pinMode(pinStep, OUTPUT);
  pinMode(pinDir, OUTPUT);
  pinMode(pinEn, OUTPUT);
  pinMode(buttonPin, INPUT);
// Initial state
// digitalWrite(pinStep, HIGH);
  digitalWrite(pinDir, HIGH);
  digitalWrite(pinEn, LOW);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(1,0); 
   lcd.display();
   pinMode(LED_BUILTIN, OUTPUT);
  // Length = 300;
}

void loop()
{

  buttonState = digitalRead(buttonPin);
  sensorValue = analogRead(analogInPin);
  delaySensorValue = analogRead(delayInPin);
  
 
  move_delay = map(delaySensorValue, 0, 1023, 650, 3000);

  if ((sensorValue > btn_1_value - btn_acc ) && (sensorValue < btn_1_value + btn_acc )) Length=length_1;
  if ((sensorValue > btn_2_value - btn_acc ) && (sensorValue < btn_2_value + btn_acc )) Length=length_2;
  if ((sensorValue > btn_3_value - btn_acc ) && (sensorValue < btn_3_value + btn_acc )) Length=length_3;
  if ((sensorValue > btn_4_value - btn_acc ) && (sensorValue < btn_4_value + btn_acc )) Length=length_4;
  
  if ((sensorValue > btn_plus_value - btn_acc ) && (sensorValue < btn_plus_value + btn_acc )) { Length++; delay(300);};
  if ((sensorValue > btn_minus_value - btn_acc ) && (sensorValue < btn_minus_value + btn_acc )) { Length--; delay(300);};  
  Count = (Length*100)/cassete_length;

   lcd.setCursor(1,0);
   lcd.print("Length: "+(String)(Length)+" sm ");
   lcd.setCursor(1,1);


  
  lcd.print("Delay: "+(String)(move_delay)+" ");
   lcd.display();

  if (buttonState == HIGH) {
    digitalWrite(pinEn, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(pinDir, HIGH); //Direction


#ifdef DEBUG
   Serial.println("Length:");
   Serial.println(Length);
   Serial.println("count");
   Serial.println(Count);
   Serial.println("move_delay");
   Serial.println(move_delay);
#endif
    
    for(int i = 0; i < steps_rotate_360*Count/100; i++)
      {
        if ( i < SmoothSteps) {
          
          smooth_move_delay = move_delay + StartSmoothDelay - (StartSmoothDelay/SmoothSteps)*i;
        } else {
          smooth_move_delay = move_delay;
        }
      digitalWrite(pinStep, HIGH);
      delayMicroseconds(150);
//     delayMicroseconds(smooth_move_delay);
      digitalWrite(pinStep, LOW);
 
#ifdef DEBUG     
      Serial.println("smooth_move_delay");
      Serial.println(smooth_move_delay);
#endif  
      delayMicroseconds(smooth_move_delay);
 //     delayMicroseconds(move_delay);
      }
  digitalWrite(pinEn, LOW);
  }
//  delay(move_delay*10);


//  delay(move_delay*10);
}
