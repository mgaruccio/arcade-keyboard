#include <Adafruit_DotStar.h>
#include <Bounce2.h>
#include <Keyboard.h>

#define BUTTON_PIN 0

Bounce debouncer = Bounce();

Adafruit_DotStar strip = Adafruit_DotStar(1, INTERNAL_DS_DATA, INTERNAL_DS_CLK, DOTSTAR_BGR);

unsigned short currentColor = 0;
uint32_t colors[] = { 0x00CCFF, 0x00CC00, 0x0000CC, 0xFF8000, 0xB404AE, 0xFA58AC };
const short numColors = sizeof(colors) / sizeof(colors[0]);

unsigned long prevMillis = 0;

void setup() {
  debouncer.attach(BUTTON_PIN, INPUT_PULLUP);
  debouncer.interval(30);
  Keyboard.begin();
  strip.begin();
}
 
void loop() {
  debouncer.update();

  unsigned long nowMillis = millis();

  if (nowMillis - prevMillis >= 1000) {
    prevMillis = nowMillis;
    
    strip.setPixelColor(0, colors[currentColor]); 

    currentColor++;
    if (currentColor > numColors - 1) {
      currentColor = 0;
    }
    
    strip.show();    
  }

  if (debouncer.fell()) {
    strip.setPixelColor(0, 0xFF0000);
    strip.show();
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press(KEY_F1);
    delay(100);
    Keyboard.releaseAll();
    delay(600);
  }
}
