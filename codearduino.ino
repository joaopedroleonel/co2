#include <LiquidCrystal.h>
LiquidCrystal lcd(1, 2, 8, 9, 10, 11);


#define LedAzul 3
#define LedVerde 4
#define LedAmarelo 5
#define LedVermelho 6

void setup()
{
  configureLCD();
  setupPins();

  tone(12, 1000, 100);
  delay(200);
  tone(12, 1000, 100);
}

void loop()
{
  delay(1000);
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print(getSensorData());

  if(getSensorData() <= 36.0)
  {
    SetLedLevel(1);
  }else if(getSensorData() >= 38.0 & getSensorData() <= 39.0)
  {
    SetLedLevel(2);
  }else if(getSensorData() >= 40.0 & getSensorData() <= 41.0)
  {
    SetLedLevel(3);
  }else if(getSensorData() >= 42.0)
  {
    SetLedLevel(4);
  }
}

void configureLCD()
{
  lcd.begin(16,2);
  lcd.clear();
}

void setupPins()
{
  pinMode(LedAzul, OUTPUT);
  pinMode(LedVerde, OUTPUT);
  pinMode(LedAmarelo, OUTPUT);
  pinMode(LedVermelho, OUTPUT);
}

float getSensorData()
{
  float sensorData = analogRead(A0);

  return sensorData;
}

void SetLedLevel(int level)
{
  LedClear();
  switch(level)
  {
    case 1:
    digitalWrite(LedAzul, HIGH);
    break;

    case 2:
    digitalWrite(LedAzul, HIGH);
    digitalWrite(LedVerde, HIGH);
    break;

    case 3:
    digitalWrite(LedAzul, HIGH);
    digitalWrite(LedVerde, HIGH);
    digitalWrite(LedAmarelo, HIGH);
    break;

    case 4:
    digitalWrite(LedAzul, HIGH);
    digitalWrite(LedVerde, HIGH);
    digitalWrite(LedAmarelo, HIGH);
    digitalWrite(LedVermelho, HIGH);
    break;
  }
}

void LedClear()
{
  digitalWrite(LedAzul, LOW);
  digitalWrite(LedVerde, LOW);
  digitalWrite(LedAmarelo, LOW);
  digitalWrite(LedVermelho, LOW);
}