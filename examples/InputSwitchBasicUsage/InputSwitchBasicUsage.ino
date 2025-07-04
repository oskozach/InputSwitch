#include <InputSwitch.h>

#define SWITCH_PIN D3

InputSwitch sw(SWITCH_PIN, true);

void setup() {
  Serial.begin(9600);
  delay(500);

  sw.begin();
  sw.onChanged([]() { Serial.println("changed"); });
  sw.onRising([]() { Serial.println("rising"); });
  sw.onFalling([]() { Serial.println("falling"); });
}

void loop() { sw.update(); }
