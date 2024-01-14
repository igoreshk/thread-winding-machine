
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

 
//#define DEBUG       // NOTE! This significantly slows rotation
#define SmoothStart // Define if you want smooth start
#define SmoothStop  // Define if you want smooth stop
#define RETURN_TO_START // Waiting for second press of the button
LiquidCrystal_I2C lcd( 0x27 , 16 , 2 );

const int pinStep = 5;      // Pin connected to STEP
const int pinDir = 3;       // Pin Connected to DIR
const int pinEn = 2;        // Pin Connected to ENABLE
const int buttonPin = 8;    // Button START Pin
const int reedPin = 7;      // Reed switch (magnetic sensor) Pin 
const int analogInPin = A1; // Keys Pin
const int delayInPin = A2;  // Speed potenciometer
const int SmoothSteps = 100;   // Steps for smooth start
const int StartSmoothDelay = 2500; // Min Delay for smooth start 
const int RotDir = LOW ;    // Rotation direction HIGH - ClockWise LOW - ContraClockWise
const int SecondDelay = 1500 ; // Delay for "Return to start" rotation

int sensorValue = 0;      // Reading from Reostst
int delaySensorValue = 0; //Calculater delay for smooth start

char s[16];

int Count = 2; // Rotation count

int move_delay = 600;    // Delay metween steps (microsec)
int smooth_move_delay = move_delay; // Delay after smooth corection

const int steps_rotate_360 = 200; // Steps for 360 degree rotete (200 for 1.8 degree motors)
int buttonState = 0; // State of button
const int btn_1_value = 350; // Values from buttons
const int btn_2_value = 442;
const int btn_3_value = 618;
const int btn_4_value = 833;

const int btn_plus_value = 508;
const int btn_minus_value = 390;
const int btn_acc = 10; // Accuracy of reading
const int cassete_length = 24;

const int length_1 = 45;  // Lengths for buttons
const int length_2 = 60;
const int length_3 = 75;
const int length_4 = 90;

int Length = 240; // Initial length

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
  pinMode(reedPin, OUTPUT);
// Initial state

  digitalWrite(pinEn, LOW);
  lcd.init();
  lcd.backlight();
 // lcd.setCursor(1,0); 
 //  lcd.display();
   pinMode(LED_BUILTIN, OUTPUT);
  // Length = 300;
}

void loop()
{
  
  int steps = 0; // Steps for current rotation
  
  buttonState = digitalRead(buttonPin);
  sensorValue = analogRead(analogInPin);
  delaySensorValue = analogRead(delayInPin);
  
 
  move_delay = map(delaySensorValue, 0, 1023, 300, 3000);

  if ((sensorValue > btn_1_value - btn_acc ) && (sensorValue < btn_1_value + btn_acc )) Length=length_1;
  if ((sensorValue > btn_2_value - btn_acc ) && (sensorValue < btn_2_value + btn_acc )) Length=length_2;
  if ((sensorValue > btn_3_value - btn_acc ) && (sensorValue < btn_3_value + btn_acc )) Length=length_3;
  if ((sensorValue > btn_4_value - btn_acc ) && (sensorValue < btn_4_value + btn_acc )) Length=length_4;
  
  if ((sensorValue > btn_plus_value - btn_acc ) && (sensorValue < btn_plus_value + btn_acc )) { Length++; delay(300);};
  if ((sensorValue > btn_minus_value - btn_acc ) && (sensorValue < btn_minus_value + btn_acc )) { Length--; delay(300);};  
  Count = (Length*100)/cassete_length;


  sprintf(s,"Len:%3d Del:%4d",Length,move_delay); 
  
//   lcd.setCursor(0,0);
//   lcd.print("Length: "+(String)(Length)+" sm ");
//   lcd.setCursor(0 ,1);
//   lcd.print("Delay: "+(String)(move_delay)+" ");
//   lcd.display();

  lcd.setCursor(0,0);
  lcd.print(s);
  sprintf(s,"%-4d%-4d%4d%4d",length_1,length_2,length_3,length_4);
  lcd.setCursor(0,1);
  lcd.print(s);
  lcd.display();


  if (buttonState == HIGH) {
    digitalWrite(pinEn, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(pinDir, RotDir); //Direction


#ifdef DEBUG
   Serial.println("Length:");
   Serial.println(Length);
   Serial.println("count");
   Serial.println(Count);
   Serial.println("move_delay");
   Serial.println(move_delay);
#endif

steps = steps_rotate_360*Count/100 ;
    


    for(int i = 0; i < steps; i++)
      {
        smooth_move_delay = move_delay;

#ifdef SmoothStart
        if ( i < SmoothSteps) {
          
          smooth_move_delay = move_delay + StartSmoothDelay - (StartSmoothDelay/SmoothSteps)*i;
        } ;
#endif
       
#ifdef SmoothStop
        if ( i > steps - SmoothSteps ) {
          smooth_move_delay = move_delay + StartSmoothDelay - (StartSmoothDelay/SmoothSteps)*(steps - i);
        }
#endif
        
      digitalWrite(pinStep, LOW);
      delayMicroseconds(150);
//     delayMicroseconds(smooth_move_delay);
      digitalWrite(pinStep, HIGH);
 
#ifdef DEBUG     
      // NOTE! This significantly slows rotation 
//      Serial.println("smooth_move_delay");
//      Serial.println(smooth_move_delay);
#endif  
      delayMicroseconds(smooth_move_delay);
 //     delayMicroseconds(move_delay);
      }
  digitalWrite(pinEn, LOW);
  
  
#ifdef RETURN_TO_START

  lcd.setCursor(0,1);
  lcd.print("* Press button *");
  lcd.display();

  while (not digitalRead(buttonPin) ) {delay(1) ; 
  
  Serial.println("Waiting....");
  }
   digitalWrite(pinEn, HIGH);
   
  while (not digitalRead(reedPin)) {
      digitalWrite(pinStep, LOW);
      delayMicroseconds(150);
      digitalWrite(pinStep, HIGH);
      delayMicroseconds(SecondDelay);
  }
  digitalWrite(pinEn, LOW);
  lcd.setCursor(1,1);
  lcd.print("                ");
  lcd.display();
#endif
  }
}
