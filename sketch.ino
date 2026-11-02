#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

const int TRIG1 = 9, ECHO1 = 10, GREEN1 = 6, RED1 = 7;
const int TRIG2 = 11, ECHO2 = 12, GREEN2 = 4, RED2 = 5;
const int GATE = 3;
const int BUZZER = 8;

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo gate;

int readDistance(int trig, int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long duration = pulseIn(echo, HIGH, 30000);
  if (duration == 0) return 999;
  return duration * 0.034 / 2;
}

void setup() {
  pinMode(TRIG1, OUTPUT); pinMode(ECHO1, INPUT);
  pinMode(TRIG2, OUTPUT); pinMode(ECHO2, INPUT);
  pinMode(GREEN1, OUTPUT); pinMode(RED1, OUTPUT);
  pinMode(GREEN2, OUTPUT); pinMode(RED2, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  gate.attach(GATE);
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
}

void loop() {
  int d1 = readDistance(TRIG1, ECHO1);
  int d2 = readDistance(TRIG2, ECHO2);

  bool occ1 = d1 < 20;
  bool occ2 = d2 < 20;

  digitalWrite(RED1, occ1);
  digitalWrite(GREEN1, !occ1);
  digitalWrite(RED2, occ2);
  digitalWrite(GREEN2, !occ2);

  int freeSlots = (!occ1) + (!occ2);

  if (freeSlots > 0) {
    gate.write(90);
    noTone(BUZZER);
  } else {
    gate.write(0);
    tone(BUZZER, 1000, 200);
  }

  lcd.setCursor(0, 0);
  if (freeSlots == 0) {
    lcd.print("** LOT FULL ** ");
  } else {
    lcd.print("Free slots: ");
    lcd.print(freeSlots);
    lcd.print("/2 ");
  }

  lcd.setCursor(0, 1);
  lcd.print("S1:");
  lcd.print(occ1 ? "FULL " : "FREE ");
  lcd.print("S2:");
  lcd.print(occ2 ? "FULL" : "FREE");

  Serial.print("D1: ");
  Serial.print(d1);
  Serial.print(" | D2: ");
  Serial.println(d2);
  delay(300);
}
