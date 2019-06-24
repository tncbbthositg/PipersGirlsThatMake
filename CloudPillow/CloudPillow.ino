#include <Adafruit_NeoPixel.h>

#define PIN 11
#define LED_COUNT 5

struct Color {
  byte red;
  byte green;
  byte blue;

  Color interpolate(Color next, double progress) {
    byte adjustedRed = interpolate(red, next.red, progress);
    byte adjustedGreen = interpolate(green, next.green, progress);
    byte adjustedBlue = interpolate(blue, next.blue, progress);

    return { adjustedRed, adjustedGreen, adjustedBlue };
  }

  private:
    byte interpolate(byte current, byte next, double progress) {
      return (next - current) * progress + current;
    }
};

//const Color colors[] = {
//  { 255, 0, 0 },
//  { 255, 255, 0 },
//  { 102, 255, 102 },
//  { 0, 153, 235 },
//  { 204, 0, 255 }
//};

const Color rainbow[] = {
  { 255, 0, 0 },
  { 255, 127, 0 },
  { 255, 255, 0 },
  { 0, 255, 0 },
  { 0, 0, 255 },
  { 127, 0, 127 }
};

const Color colors[] = {
  { 0, 0, 255 },
  { 0, 0, 255 },
  { 0, 0, 255 },
  { 0, 0, 255 },
  { 0, 0, 255 },
  { 255, 127, 0 },
  { 255, 127, 0 },
  { 255, 127, 0 },
  { 255, 127, 0 },
  { 255, 127, 0 },
};

const Color white[] = {
  { 0, 0, 0 },       // RGB - BLACK
  { 64, 64, 64 },       
  { 128, 128, 128 },       
  { 191, 191, 191 }, 
  { 255, 255, 255 }, // RGB - WHITE
  { 191, 191, 191 }, 
  { 128, 128, 128 },       
  { 64, 64, 64 },       
};

const byte colorCount = sizeof(colors) / sizeof(colors[0]);

Adafruit_NeoPixel leds = Adafruit_NeoPixel(LED_COUNT, PIN, NEO_GRB + NEO_KHZ800);
void setup() {
  // put your setup code here, to run once:
  leds.begin();
  leds.show();
}

void loop() {
  unsigned long maximumTime = colorCount * 256;
  unsigned long currentTime = (millis() / 3) % maximumTime;
  showColorGradient(maximumTime - currentTime);
}

void showColorGradient(unsigned long currentTimeOffset) {
  for (byte i = 0; i < LED_COUNT; i++) {
    showColor(i, currentTimeOffset);
  }

  leds.show();
}

void showColor(byte index, unsigned int colorOffset) {
  Color currentColor = getColorWithOffset(index * 256 + colorOffset);
  leds.setPixelColor(index, currentColor.red, currentColor.green, currentColor.blue);
}

Color getColorWithOffset(unsigned int colorOffset) {
  byte startingColorIndex = colorOffset / 256;
  startingColorIndex %= colorCount;

  double percentage = (colorOffset % 256) / 256.0;

  byte nextColorIndex = startingColorIndex + 1;
  nextColorIndex %= colorCount;

  Color startingColor = colors[startingColorIndex];
  Color nextColor = colors[nextColorIndex];

  return startingColor.interpolate(nextColor, percentage);
}

void blinkRainbow() {
  // put your main code here, to run repeatedly:
  leds.setPixelColor(0, 255,0,0); //red
  leds.setPixelColor(1, 255,255,0); //yellow
  leds.setPixelColor(2, 102,255,102); //green
  leds.setPixelColor(3, 0,153,235); //blue
  leds.setPixelColor(4, 204,0,255); //purple
  leds.show();
  delay(1000);

  leds.setPixelColor(0, 204,0,255); //purple
  leds.setPixelColor(1, 255,0,0); //red
  leds.setPixelColor(2, 255,255,0); //yellow
  leds.setPixelColor(3, 102,255,102); //green
  leds.setPixelColor(4, 0,153,235); //blue
  leds.show();
  delay(1000);

  leds.setPixelColor(0, 0,153,235); //blue
  leds.setPixelColor(1, 204,0,255); //purple
  leds.setPixelColor(2, 255,0,0); //red
  leds.setPixelColor(3, 255,255,0); //yellow
  leds.setPixelColor(4, 102,255,102); //green
  leds.show();
  delay(1000);

  leds.setPixelColor(0, 102,255,102); //green
  leds.setPixelColor(1, 0,153,235); //blue
  leds.setPixelColor(2, 204,0,255); //purple
  leds.setPixelColor(3, 255,0,0); //red
  leds.setPixelColor(4, 255,255,0); //yellow
  leds.show();
  delay(1000);

  leds.setPixelColor(0, 255,255,0); //yellow
  leds.setPixelColor(1, 102,255,102); //green
  leds.setPixelColor(2, 0,153,235); //blue
  leds.setPixelColor(3, 204,0,255); //purple
  leds.setPixelColor(4, 255,0,0); //red
  leds.show();
  delay(1000);
}
