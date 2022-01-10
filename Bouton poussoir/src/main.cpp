#include <Arduino.h>

void setup() {
  pinMode(13, OUTPUT);
  pinMode(12, INPUT_PULLUP);
}
 
void loop() {
  bool switchState = digitalRead(12);
  digitalWrite(13, switchState);
}