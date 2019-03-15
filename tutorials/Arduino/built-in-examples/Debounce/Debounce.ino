const int buttonPin = 2;
const int ledPin = 10;

int ledState = HIGH;
int buttonState;
int lastButtonState = LOW;

unsigned long int lastDebounceTime = 0;
unsigned long int debounceDelay = 50;

void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

  digitalWrite(ledPin, ledState);
}

void loop() {
  // put your main code here, to run repeatedly:
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == HIGH) {
        ledState = !ledState;
      }
    }
  }

  digitalWrite(ledPin, ledState);

  lastButtonState = reading;
}
