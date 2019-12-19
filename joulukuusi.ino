#include <Adafruit_NeoPixel.h>

#define PIN 10

Adafruit_NeoPixel strip = Adafruit_NeoPixel(30, PIN, NEO_GRB + NEO_KHZ800);

int punaisuus=0;

void setup() {
  delay(500);
  strip.begin();
  strip.show();
  randomSeed(analogRead(0));
}

void loop() {
  valkynta2 (400,30);
  valkynta (30*3,10*1000);
}

void testi() {
  // Some example procedures showing how to display to the pixels:
  colorWipe(strip.Color(255, 0, 0), 50); // Red
  colorWipe(strip.Color(0, 255, 0), 50); // Green
  colorWipe(strip.Color(0, 0, 255), 50); // Blue
  // Send a theater pixel chase in...
  theaterChase(strip.Color(127, 127, 127), 50); // White
  theaterChase(strip.Color(127,   0,   0), 50); // Red
  theaterChase(strip.Color(  0,   0, 127), 50); // Blue

  rainbow(20);
  rainbowCycle(20);
  theaterChaseRainbow(50);
}

void valkynta(int pituus, int nopeus)
{
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, punaisuus,0,0);
  }
  strip.show();

  for(int i=0;i<pituus;i++)
  {
    int r;
    r=random(strip.numPixels());
    strip.setPixelColor(r,255,255,255);
    strip.show();
    delay(50);
    strip.setPixelColor(r,punaisuus,0,0);
    strip.show();
    delay(1000);

    r=random(strip.numPixels());
    strip.setPixelColor(r,255,255,255);
    strip.show();
    delay(50);
    strip.setPixelColor(r,punaisuus,0,0);
    strip.show();
    delay(1000);

    r=random(strip.numPixels());
    strip.setPixelColor(r,255,255,255);
    strip.show();
    delay(50);
    strip.setPixelColor(r,punaisuus,0,0);
    strip.show();

    delay(nopeus);
  }
}

void valkynta2(int pituus, int nopeus)
{
  int r1,r2,r3;
  
  colorWipe(strip.Color(63, 63, 63), 20);
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, 0,0,0);
  }
  strip.show();

  for(int i=0;i<pituus;i++)
  {
    r1=random(strip.numPixels());
    r2=random(strip.numPixels());
    r3=random(strip.numPixels());
    strip.setPixelColor(r1,255,255,255);
    strip.setPixelColor(r2,255,255,255);
    strip.setPixelColor(r3,255,255,255);
    strip.show();
    delay(10);
    strip.setPixelColor(r1,0,0,0);
    strip.setPixelColor(r2,0,0,0);
    strip.setPixelColor(r3,0,0,0);
    strip.show();
    delay(nopeus);
  }
}


// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();
     
      delay(wait);
     
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        }
        strip.show();
       
        delay(wait);
       
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}
