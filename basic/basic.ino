/*Программа для вращения шагового мотора NEMA 17, серии 17HS4402 + драйвер A4988. Сначала мотор совершает полный оборот в одну сторону, потом в другую*/
/*целочисленная константа, хранящая номер цифрового контакта Arduino, который подаёт сигнал Step на драйвер. Каждый импульс от этого контакта — это перемещение мотора на один шаг*/
const int pinStep = 5;
/*целочисленная константа, хранящая номер цифрового контакта Arduino, который подаёт сигнал Direction на драйвер. Наличие импульса - мотор вращается в одну сторону, отсутствие - в другую*/
const int pinDir = 4;
const int buttonPin = 9;
const int pinEn = 7;
const int analogInPin = A2;
int sensorValue = 0;
// Количество оборотов для намотки

int Count = 2;

//временная задержка между шагами мотора в мс 
const int move_delay = 1;

//шагов на полный оборот
const int steps_rotate_360 = 200;
int buttonState = 0; 

/*Функция, в которой происходит инициализация всех переменных программы*/
void setup()
{
/*задаём контактам Step и Direction режим вывода, то есть они выдают напряжение*/

  pinMode(pinStep, OUTPUT);
  pinMode(pinDir, OUTPUT);
  pinMode(buttonPin, INPUT);
  // pinMode(pinEn, LOW);
//устанавливаем начальный режим
  digitalWrite(pinStep, HIGH);
  digitalWrite(pinDir, LOW);
}

/*Функция-цикл в которой задаётся поведение программы*/
void loop()
{
//устанавливаем направление вращения
  buttonState = digitalRead(buttonPin);
  sensorValue = analogRead(analogInPin);
  Count = map(sensorValue, 0, 1023, 2, 7);
  
  if (buttonState == HIGH) {
    digitalWrite(pinDir, HIGH);
    digitalWrite(pinEn, HIGH);
    for(int i = 0; i < steps_rotate_360*Count; i++)
      {
      digitalWrite(pinStep, HIGH);
      delay(move_delay);
      digitalWrite(pinStep, LOW);
      delay(move_delay);
      }
  }
  delay(move_delay*10);

//устанавливаем направление вращения обратное
/*  digitalWrite(pinDir, LOW);

  for(int i = 0; i < steps_rotate_360; i++)
  {
    digitalWrite(pinStep, HIGH);
    delay(move_delay);
    digitalWrite(pinStep, LOW);
    delay(move_delay);
  } */

  delay(move_delay*10);
}
