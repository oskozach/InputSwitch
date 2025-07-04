#include <Arduino.h>
#include <InputButton.h>

#define BTN_PIN 4

InputButton btn(BTN_PIN);

void onChange() { Serial.println("Changed"); }
void onPress() { Serial.println("Pressed"); }
void onRelease() { Serial.println("Released"); }
void onClick() { Serial.println("Click"); }
void onDoubleClick() { Serial.println("Double Click"); }
void onLongPress() { Serial.println("Long Pressed"); }

void setup() {
  Serial.begin(9600);
    
  btn.begin();

  btn.onChanged(onChanged);
  btn.onPressed(onPressed);
  btn.onReleased(onReleased);
  btn.onClick(onClick);
  btn.onDoubleClick(onDoubleClick);
  btn.onLongPressed(onLongPressed);
}

void loop() {
  btn.update();
  delay(10);
}
