#include <Bounce2.h>
#include <Keyboard.h>

#define BUTTON_PIN 0
#define LED_PIN 13

Bounce debouncer = Bounce();

void setup() {
  debouncer.attach(BUTTON_PIN, INPUT_PULLUP);
  debouncer.interval(30);
  pinMode(LED_PIN, OUTPUT);
  Keyboard.begin();
}
 
// the loop function runs over and over again forever
void loop() {
  debouncer.update();

  if (debouncer.fell()) {
    digitalWrite(LED_PIN, HIGH);
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press(KEY_F1);
    delay(100);
    Keyboard.releaseAll();
    
    digitalWrite(LED_PIN, LOW);
  }
}
