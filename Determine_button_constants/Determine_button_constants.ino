
const int analogInPin = A1;  // Analog input pin that the buttons attached

int sensorValue = 0;        // value read from the button

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
 
  Serial.print("Button constant = ");
  Serial.println(sensorValue);

  // wait 20 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(20);
}
