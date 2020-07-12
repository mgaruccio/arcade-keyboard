#include <Adafruit_DotStar.h>
#include <Bounce2.h>
#include <Keyboard.h>

#define BUTTON_PIN 0
#define LED_PIN 13

Bounce debouncer = Bounce();

Adafruit_DotStar strip = Adafruit_DotStar(1, INTERNAL_DS_DATA, INTERNAL_DS_CLK, DOTSTAR_BGR);

uint32_t color = 0xFF0000;
unsigned long prevMillis = 0;

void setup() {
  debouncer.attach(BUTTON_PIN, INPUT_PULLUP);
  debouncer.interval(30);
  pinMode(LED_PIN, OUTPUT);
  Keyboard.begin();
  strip.begin();
}
 
// the loop function runs over and over again forever
void loop() {
  debouncer.update();

  unsigned long nowMillis = millis();

  if (nowMillis - prevMillis >= 1000) {
    prevMillis = nowMillis;
    
    if((color >>= 8) == 0) {
      color = 0xFF0000; 
    }

    strip.setPixelColor(0, color); 
    strip.show();    
  }

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
