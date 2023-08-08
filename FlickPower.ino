#include <LiquidCrystal.h>
const int piezoReadout = A0;
const int greenLedOne = 8;
const int greenLedTwo = 7;
const int yellowLedOne = 6;
const int yellowLedTwo = 5;
const int redLedOne = 4;
const int redLedTwo = 3;
const int flickMinimum = 100;
const int fadeLightDelay = 2000;
int flickVal;
int savedFlickVal;
unsigned long currentTime;
unsigned long lastFlickTime;
LiquidCrystal lcd(9, 2, 10, 11,12, 13);

void setup() 
{
 pinMode(greenLedOne, OUTPUT);
 pinMode(greenLedTwo, OUTPUT);
 pinMode(yellowLedOne, OUTPUT);
 pinMode(yellowLedTwo, OUTPUT);
 pinMode(redLedOne, OUTPUT);
 pinMode(redLedTwo, OUTPUT);

 Serial.begin(9600);

 lcd.begin(16, 2);
 printFlick();
}

void loop() 
{
  flickVal = analogRead(piezoReadout);
  if(flickVal > 30)
  {
    Serial.println(flickVal);
    printFlick();
  }
  displayFlickValueOnLights(flickVal);
}

void displayFlickValueOnLights(int knockVal)
{
  currentTime = millis();

  if(flickVal > flickMinimum && currentTime >= lastFlickTime + 100)
  {
    clearLights();
    delay(100);

    digitalWrite(greenLedOne, HIGH);
    lastFlickTime = currentTime;
    savedFlickVal = flickVal;

  }
  if(savedFlickVal > flickMinimum + 75 && currentTime >= lastFlickTime + 300)
  {
    digitalWrite(greenLedTwo, HIGH);
  }
  if(savedFlickVal > flickMinimum + 150 && currentTime >= lastFlickTime + 600)
  {
    digitalWrite(yellowLedOne, HIGH);
  }

  if(savedFlickVal > flickMinimum + 225 && currentTime >= lastFlickTime + 900)
  {
    digitalWrite(yellowLedTwo, HIGH);
  }
  if(savedFlickVal > flickMinimum + 300 && currentTime >= lastFlickTime + 1200)
  {
    digitalWrite(redLedOne, HIGH);
  }
  if(savedFlickVal > flickMinimum + 375 && currentTime >= lastFlickTime + 1500)
  {
    digitalWrite(redLedTwo, HIGH);
  }

  if(currentTime >= lastFlickTime + fadeLightDelay)
  {
    fadeLights(currentTime, lastFlickTime);
  }
}

void clearLights()
{
  digitalWrite(redLedTwo, LOW);
  digitalWrite(redLedOne, LOW);
  digitalWrite(yellowLedTwo, LOW);
  digitalWrite(yellowLedOne, LOW);
  digitalWrite(greenLedTwo, LOW);
  digitalWrite(greenLedOne, LOW);
}

void fadeLights(int currentTime, int lastFlickTime)
{
  if(currentTime > lastFlickTime + fadeLightDelay)
  {
    digitalWrite(redLedTwo, LOW);
    savedFlickVal = 0;
  }
  if(currentTime > lastFlickTime + fadeLightDelay + 50)
  {
    digitalWrite(redLedOne, LOW);
  }
  if(currentTime > lastFlickTime + fadeLightDelay + 100)
  {
    digitalWrite(yellowLedTwo, LOW);
  }
  if(currentTime > lastFlickTime + fadeLightDelay + 150)
  {
    digitalWrite(yellowLedOne, LOW);
  }
  if(currentTime > lastFlickTime + fadeLightDelay + 200)
  {
    digitalWrite(greenLedTwo, LOW);
  }
  if(currentTime > lastFlickTime + fadeLightDelay + 250)
  {
    digitalWrite(greenLedOne, LOW);
    lcd.clear();
    clearLights();
  }
}

void printFlick()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("FlickPower!!");
  lcd.setCursor(0, 1);
  lcd.print(flickVal);
}
