#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <SPI.h>
#include <MFRC522.h>


const int EN=7, RS=6, D7=5, D6=4, D5=3, D4=2;
LiquidCrystal lcd(RS,EN, D4, D5, D6, D7); 

#define SS_PIN 10
#define RST_PIN 9

MFRC522 rfid(SS_PIN,RST_PIN);

void setup() {
  // put your setup code here, to run once:
lcd.begin(16,2);
SPI.begin();
rfid.PCD_Init();
}

void loop() {
  // put your main code here, to run repeatedly:

if (! rfid.PICC_IsNewCardPresent()){
  return;
}
if (rfid.PICC_ReadCardSerial()){
  return;
}
String content= "";
byte letter;
for (byte i = 0; i < rfid.uid.size; i++)
{ 
content.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
content.concat(String(rfid.uid.uidByte[i], HEX));
}

content.toUpperCase();
lcd.setCursor(0,0);
lcd.print("KEY: "+content.substring(1));

if (content.substring(1) == "A7 FE 76 B5")
{
lcd.setCursor(0,1);
lcd.print("ACCESS OK");
delay(5000);
lcd.clear();
}
if (content.substring(1) != "A7 FE 76 B5")
{
lcd.setCursor(0,1);
lcd.print("ACCES DENIED");
delay(3000);
lcd.clear();
}
}