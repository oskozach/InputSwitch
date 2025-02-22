#include "src/InputSwitch/InputSwitch.h"

Timer timer;
InputSwitch btn(&timer, 12, FALLING, true);

void setup() {
  Serial.begin(9600);
  delay(500);

  btn.begin();
}

void loop() {
  if(btn.changed())
    Serial.println("changed");
}
