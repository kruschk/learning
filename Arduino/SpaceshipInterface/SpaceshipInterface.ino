int switchState = 0;

void setup() {
  // sets up 4 digital pins as either inputs or outputs
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(2,INPUT);
}

void loop() {
  // checks the status of the input pin 2, if it's LOW, the green light turns on and reds turn off, if it's HIGH, the green lights turn on, red 1 turns on, and red 2 flashes.
  switchState = digitalRead(2);
  if (switchState == LOW) {
    digitalWrite(3,HIGH); // turn on the green LED
    digitalWrite(4,LOW); // turn off the red LED
    digitalWrite(5,LOW); // turn off the other red LED
  }
  else {
    digitalWrite(3,LOW); // green off
    digitalWrite(4,HIGH); // red 1 on
    digitalWrite(5,HIGH); // red 2 on

    delay(250);
    digitalWrite(4,HIGH); // red 1 on
    digitalWrite(5,LOW); // red 2 off
    delay(250);
  }
}
