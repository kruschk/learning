/*
 *
 * Modified from blog article by Jennifer Marsh on Udemy.com (https://blog.udemy.com/arduino-voltmeter/)
 * Building an Arduino DC Voltmeter
 *
 */
#include <LiquidCrystal.h>
const unsigned int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const unsigned int ADCPin = A0;
float vPow = 5.08; // measured from Arduino +5 V to GND
float r1 = 10000000;
float r2 = 1000000;
 
void setup() {
  /*
  // open serial port
  Serial.begin(9600);

  // initialize serial monitor
  Serial.println("--------------------");
  Serial.println("DC VOLTMETER");
  Serial.print("Maximum Voltage: ");
  Serial.print(vPow*(r1+r2)/r2);
  Serial.println("V");
  Serial.println("--------------------");
  Serial.println();
  */

  // initialize lcd
  lcd.begin(16, 2);
  lcd.print("Voltage:");
}

void loop() {
  // calculate v_in, which is the measured voltage (v_out is the voltage read by ADCPin)
  float v_out = analogRead(0)*(vPow/1024.0);
  float v_in = v_out*(r1+r2)/r2;

  /*
  // print voltage to serial monitor
  Serial.print(v_in);
  Serial.println(" V");
  */

  // print voltage to lcd
  lcd.setCursor(9, 0);
  lcd.print(v_in);
  lcd.print(" V");

  delay(250);
}
