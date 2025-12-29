#include <Wire.h>
#include <Adafruit_LiquidCrystal.h>
#include <Servo.h>

Adafruit_LiquidCrystal lcd(0);
Servo flowServo;

#define potPin A3
#define redLED 3
#define yellowLED 2
#define greenLED 1
#define buzzer 6

const int maxDrops = 100;  // Max drops in bottle

void setup() {
  flowServo.attach(10);
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(buzzer, OUTPUT);
  lcd.begin(16, 2);
  lcd.print("Saline monitor System");
  delay(2000);
  lcd.clear();
}

void loop() {
  int potVal = analogRead(potPin);  // 0-1023
  int drops = map(potVal, 0, 1023, 0, maxDrops);  // Convert pot to drops
  lcd.clear();

  if(potVal > 700){  // HIGH level
    digitalWrite(greenLED,HIGH);
    digitalWrite(yellowLED,LOW);
    digitalWrite(redLED,LOW);
    digitalWrite(buzzer,LOW);
    flowServo.write(0); // Flow open
    lcd.print("Saline: HIGH");
    lcd.clear();
    lcd.print("Drops: "); lcd.print(drops);
    lcd.clear();
  }
  else if(potVal > 400){  // MID level
    digitalWrite(greenLED,LOW);
    digitalWrite(yellowLED,HIGH);
    digitalWrite(redLED,LOW);
    digitalWrite(buzzer,LOW);
    flowServo.write(0); // Flow open
    lcd.print("Saline: MID");
    lcd.clear();
    lcd.print("Drops: "); lcd.print(drops);
    lcd.clear();
  }
  else{  // LOW level
    digitalWrite(greenLED,LOW);
    digitalWrite(yellowLED,LOW);
    digitalWrite(redLED,HIGH);
    tone(buzzer,1000);
    flowServo.write(90); // Stop flow
    lcd.print("LOW! CALL NURSE");
    lcd.clear();
    lcd.print("CRITICAL!");
    lcd.clear();
    lcd.print("Drops: "); lcd.print(drops);
    lcd.clear();
  }

  delay(200);
}
