const int ledPin = LED_BUILTIN;
int ledState = LOW;
unsigned long int previousMillis = 0;
const long int interval = 1000;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long int currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    ledState = (ledState == LOW) ? HIGH : LOW;
  }

  digitalWrite(ledPin, ledState);
}
