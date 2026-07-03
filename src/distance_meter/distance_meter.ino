/*
 https://docs.arduino.cc/learn/electronics/lcd-displays

*/

// Libraries
#include <math.h>
#include <LiquidCrystal.h>

// initialize the LCD
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// initialise ultrasonic sensor
const int usb = 7, ust = 8, use = 9; // Ultrasonic (button, trigger, echo)
float duration, distance;
int eCount;

void setup() {
  // set up the LCD
  lcd.begin(16, 2);
  lcd.print("Distance in m:");

  // set up ultrasonic pins
  pinMode(usb, OUTPUT);
  pinMode(ust, OUTPUT);
  pinMode(use, INPUT);
}

void loop() {
  // reset
  lcd.setCursor(0, 1);
  eCount = 0;

  // check if the button has been pressed
  if (digitalRead(usb)) {
    // Trigger ultrasonic sensor
    digitalWrite(ust, LOW);
    delayMicroseconds(2);
    digitalWrite(ust, HIGH);
    delayMicroseconds(10);
    digitalWrite(ust, LOW);

    // Time echo signal
    duration = pulseIn(use, HIGH);

    // Calculate distance
    distance = (duration*.000343)/2;

    // Convert to scientific notation
    while (distance >= 10) {
      distance /= 10.0;
      eCount ++;
    }
    distance = round(distance * 10000.0) / 10000.0;

    // Format string
    char lcdOut[32];
    char strDistance[8] = "hehehe";
    dtostrf(distance, 2, 4, strDistance);
    sprintf(lcdOut, "%s%c%d", strDistance, 'e', eCount);

    // Output result
    lcd.print(lcdOut);
  }
}