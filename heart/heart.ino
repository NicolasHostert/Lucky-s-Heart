#include <Adafruit_NeoPixel.h>

// Strip global declaration
#define PINLEFT            9
#define LENGTHLEFT      140
Adafruit_NeoPixel left = Adafruit_NeoPixel(LENGTHLEFT, PINLEFT, NEO_GRB + NEO_KHZ800);
#define PINRIGHT            3
#define LENGTHRIGHT      126
Adafruit_NeoPixel right = Adafruit_NeoPixel(LENGTHRIGHT, PINRIGHT, NEO_GRB + NEO_KHZ800);

// Testing variable
Adafruit_NeoPixel strip = Adafruit_NeoPixel(10, 6, NEO_GRB + NEO_KHZ800);

// Global delays
#define SLIDERDELAY  50 // Delay in sliderfull and sliderblock modes 
#define RANDODELAY  150 // Delay in sliderfull and sliderblock modes 
#define TESTDELAY 2000   // Delay for the init script

// Iterations variables
int travellingrandoruns = 7;
int breathingruns = 11;
int sliderfullruns = 10;

// Randomization variables
int randomlenght() {
  // creates a random length of LEDs to light
  int length;
  length = random(1, 5);
  return length;
};

uint32_t randomcolor() {
  // This creates a random 32-bit merged color value 
  uint32_t color = ((random (0, 255) << 16) + (random (0, 255) << 8) + random (0, 255));
  return color;
};

int random255() {
  int value;
  value = random(0, 255);
  return value;
};

// Color variables
  int R, G, B;

void setup() {
  // Init to see that the strip is working
  // All red for 2 seconds, then off
  left.begin();
  for (int i = 0; i < left.numPixels(); i = i + 1) {
    left.setPixelColor(i, 255, 0, 0);
  }
  right.begin();
  for (int i = 0; i < right.numPixels(); i = i + 1) {
    right.setPixelColor(i, 0, 0, 255);
  }
  left.show();
  right.show();
  delay(TESTDELAY);
  blackout();
  delay(TESTDELAY);
};

void loop() {
  
  //for (int i = 1; i < travellingrandoruns; i = i + 1) {
  //  travellingrando(); // Tested OK
  //}
  
  //for (int i = 1; i < breathingruns; i = i + 1) {
  //  R = random255();
  //  G = random255();
  //  B = random255();
  //  breathing(R,G,B,10); // Tested OK
  //}
  //for (int i = 1; i < sliderfullruns; i = i + 1) {
  //  R = random255();
  //  G = random255();
  //  B = random255();
  //  sliderfull(R,G,B); // Tested OK
  //}
  blackout();
  delay(TESTDELAY);
};

void shiftall() {
  // This is used to move the colors along the strip
  for (int i = (left.numPixels() - 1); i > 0; i = i - 1) {
    uint32_t currentcolor = left.getPixelColor(i-1);
    left.setPixelColor(i, currentcolor);
  }
  for (int i = (right.numPixels() - 1); i > 0; i = i - 1) {
    uint32_t currentcolor = right.getPixelColor(i-1);
    right.setPixelColor(i, currentcolor);
  }
  left.show();
  right.show();
}

void travellingrando() {
  for (int i = 0; i < left.numPixels(); i = i + 1) {
  shiftall();
  left.setPixelColor(0, randomcolor());
  right.setPixelColor(0, randomcolor());
  left.show();
  right.show();
  delay(RANDODELAY);
  }
}

void sliderfull(int color1, int color2, int color3) {
  // Fills the strip and drains it afterwards, always same direction
  blackout();
  for (int i = 0; i < 101; i = i + 1) {
    left.setPixelColor((i*left.numPixels()/100), color1, color2, color3);
    left.setPixelColor(((i*left.numPixels()/100)-1), color1, color2, color3);
    right.setPixelColor((i*right.numPixels()/100), color1, color2, color3);
    right.setPixelColor(((i*right.numPixels()/100)-1), color1, color2, color3);
    left.show();
    right.show();
    delay(SLIDERDELAY);
  }
  for (int i = 0; i < 101; i = i + 1) {
    left.setPixelColor((i*left.numPixels()/100), 0, 0, 0);
    left.setPixelColor(((i*left.numPixels()/100)-1), 0, 0, 0);
    right.setPixelColor((i*right.numPixels()/100), 0, 0, 0);
    right.setPixelColor(((i*right.numPixels()/100)-1), 0, 0, 0);
    left.show();
    right.show();
    delay(SLIDERDELAY);
  }
}

void sliderfullbounce(int color1, int color2, int color3) {
  // Fills the strip and drains it afterwards, opposite direction
  blackout();
  for (int i = 0; i < 99; i = i + 1) {
    left.setPixelColor((i*left.numPixels()/100), color1, color2, color3);
    right.setPixelColor((i*right.numPixels()/100), color1, color2, color3);
    left.show();
    right.show();
    delay(SLIDERDELAY);
  }
  for (int i = 100; i > 1; i = i - 1) {
    left.setPixelColor((i*left.numPixels()/100), 0, 0, 0);
    right.setPixelColor((i*right.numPixels()/100), 0, 0, 0);
    left.show();
    right.show();
    delay(SLIDERDELAY);
  }
}

void sliderblock(int color1, int color2, int color3, int blocksize) {
  // Slides a block of LEDs across
  blackout();
  for (int i = 0; i < 99; i = i + 1) {
    strip.setPixelColor((i*strip.numPixels()/100), color1, color2, color3);
    strip.setPixelColor(((i*strip.numPixels()/100)-blocksize), 0, 0, 0);
    strip.show();
    delay(SLIDERDELAY);
  }
}

void sliderblockbounce(int color1, int color2, int color3, int blocksize) {
  // Bounces a block of LEDs across
  blackout();
  for (int i = 0; i < 99; i = i + 1) {
    strip.setPixelColor((i*strip.numPixels()/100), color1, color2, color3);
    strip.setPixelColor(((i*strip.numPixels()/100)-blocksize), 0, 0, 0);
    strip.show();
    delay(SLIDERDELAY);
  }
  for (int i = 99; i > 0; i = i - 1) {
    strip.setPixelColor((i*strip.numPixels()/100), 0, 0, 0);
    strip.setPixelColor(((i*strip.numPixels()/100)-blocksize), color1, color2, color3);
    strip.show();
    delay(SLIDERDELAY);
  }
}



void breathing(int color1, int color2, int color3, int delayvalue) {
  // Goes from 0 to 255 power on the specified colors, back to 0
  for (int level = 0; level < 255; level = level + 5) {
    for (int i = 0; i < 99; i = i + 1) {
      left.setPixelColor((i*left.numPixels()/100), (level*color1/255) , (level*color2/255), (level*color3/255));
      right.setPixelColor((i*right.numPixels()/100), (level*color1/255) , (level*color2/255), (level*color3/255));
    }
    left.show();
    right.show();
    delay(delayvalue);
  }
  for (int level = 255; level > 0; level = level - 5) {
    for (int i = 0; i < 99; i = i + 1) {
      left.setPixelColor((i*left.numPixels()/100), (level*color1/255) , (level*color2/255), (level*color3/255));
      right.setPixelColor((i*right.numPixels()/100), (level*color1/255) , (level*color2/255), (level*color3/255));
    }
    left.show();
    right.show();
    delay(delayvalue);
  }
}

// init functions
void allredleft()  {
  for (int i = 0; i < left.numPixels(); i = i + 1) {
    left.setPixelColor(i, 255, 0, 0);
  }
  left.show();
}

void allblueright()  {
  for (int i = 0; i < right.numPixels(); i = i + 1) {
    right.setPixelColor(i, 0, 0, 255);
  }
  right.show();
}

void blackout() {
  for (int i = 0; i < (left.numPixels() + 1); i = i + 1) {
    left.setPixelColor(i, 0, 0, 0);
  }
  for (int i = 0; i < (right.numPixels() + 1); i = i + 1) {
    right.setPixelColor(i, 0, 0, 0);
  }
  left.show();
  right.show();
}