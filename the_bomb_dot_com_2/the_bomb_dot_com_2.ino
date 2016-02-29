#include <Adafruit_NeoPixel.h>

#define PIN 6
#define NUMLEDS 30
#define DELAY 25
#define VALUE 17

Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, 12 , NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(NUMLEDS, PIN, NEO_GRB + NEO_KHZ800);

int pattern = 1, counter = 0;
int holder[3] = {255,0,0};

void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.show();
  strip.setBrightness(128);
  delay(100);
  for(int x = 0; x <16; x++) {
  strip.setPixelColor(x, 0, 255, 0);
  }
  strip.show();
  strip2.begin();
  strip2.show();
}

void loop() {
  //TODO make method to change the patterns
  if (pattern==1) {
    for (int x=0;x<NUMLEDS;x++) {
      if (x<NUMLEDS/3) {
        strip2.setPixelColor((x+counter)%NUMLEDS, 255-x*255/(NUMLEDS/3), x*255/(NUMLEDS/3), 0);
      } else if (x<2*NUMLEDS/3) {
        strip2.setPixelColor((x+counter)%NUMLEDS, 0, 255-(x-NUMLEDS/3)*255/(NUMLEDS/3), (x-NUMLEDS/3)*255/(NUMLEDS/3));
      } else {
        strip2.setPixelColor((x+counter)%NUMLEDS, (x-2*NUMLEDS/3)*255/(NUMLEDS/3), 0, 255-(x-2*NUMLEDS/3)*255/(NUMLEDS/3));
      }
    }
    counter = (counter+1)%NUMLEDS;
  } else if (pattern==2) {
    int temp[3] = {holder[0],holder[1],holder[2]};
    for (int x=0;x<NUMLEDS/2;x++) {
      strip2.setPixelColor(NUMLEDS/2-(x+1), temp[0], temp[1], temp[2]);
      strip2.setPixelColor(NUMLEDS/2+x, temp[0], temp[1], temp[2]);
      if (temp[0]<255 && temp[1]>0 && temp[2]==0) {
        temp[0] += VALUE;
        temp[1] -= VALUE;
      } else if (temp[1]<255 && temp[2]>0 && temp[0]==0) {
        temp[1] += VALUE;
        temp[2] -= VALUE;
      } else {
        temp[2] += VALUE;
        temp[0] -= VALUE;
      }
    }
    if (holder[0]>0 && holder[1]<255 && holder[2]==0) {
      holder[0] -= VALUE;
      holder[1] += VALUE;
    } else if (holder[1]>0 && holder[2]<255 && holder[0]==0) {
      holder[1] -= VALUE;
      holder[2] += VALUE;
    } else {
      holder[2] -= VALUE;
      holder[0] += VALUE;
    }
  }
  strip2.show();
  delay(DELAY);
}

void serialEvent() {
  while(Serial.available())
  {
    pattern = (int) Serial.read() - '0';
  }
}
