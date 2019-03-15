/*
 * Illuminates an LED when a pushbutton is pressed using a digital input pin,
 * a digital output pin, and a pull-down resistor.
 */

const int ledPin = LED_BUILTIN; // pin 13 on UNO
const int pushButtonPin = 2;

void setup() {
  // initialize the LED
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  // initialize the button
  pinMode(pushButtonPin, INPUT);
}

void loop() {
  // check if the button is pressed (HIGH or LOW)
  int pushButtonState = digitalRead(pushButtonPin);
  // write the button's state to the LED pin
  digitalWrite(ledPin, pushButtonState);
}
