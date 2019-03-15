#include <LiquidCrystal.h>
const unsigned int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // open serial port
  Serial.begin(9600);
  
  // initialize lcd
  lcd.begin(16, 2);
  lcd.print("Temp:");
  lcd.setCursor(0, 1);
  lcd.print("Up-time:");
}

void loop() {
  // tmp36 connected to pin A0
  const unsigned int sensorPin = A0;

  // determine temperature from sensor reading
  int sensorVal = analogRead(sensorPin);
  /*Serial.print("Sensor value: ");
  Serial.print(sensorVal);
  Serial.print('\n');*/
  float voltage = sensorVal*(5.0/1024.0); // bit*(5.0 V/1024.0 bit)
  /*Serial.print("Voltage: ");
  Serial.print(voltage);
  Serial.print(" V\n");*/
  float temperature = (voltage - 0.5)*100.0;
  /*Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" degC\n");*/
  
  // print temperature to lcd
  lcd.setCursor(6, 0);
  lcd.print(temperature);
  lcd.print(" degC");

  // print up-time to lcd
  lcd.setCursor(9, 1);
  lcd.print(millis() / 1000); // note: integer division, number truncates!
  lcd.print(" s");

  delay(1000);
}
