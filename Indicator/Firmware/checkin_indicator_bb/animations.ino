/*###

Animations moved to separat file.

###*/


// Fill the dots one after the other with a color
void color1Wipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<24; i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void color2Wipe(uint32_t c, uint8_t wait) {
    for(uint16_t i=0; i<12; i++) {
    strip.setPixelColor(i, c);
    strip.setPixelColor(i+12, c);
    strip.show();
    delay(wait);
  }
}

void color4Wipe(uint32_t c, uint8_t wait) {
    for(uint16_t i=0; i<6; i++) {
    strip.setPixelColor(i, c);
    strip.setPixelColor(i+6, c);
    strip.setPixelColor(i+12, c);
    strip.setPixelColor(i+18, c);
    strip.show();
    delay(wait);
  }
}

void color4WipeMirror(uint32_t c, uint8_t wait) {
    for(uint16_t i=0; i<6; i++) {
    strip.setPixelColor(i, c);
    strip.setPixelColor(11-i, c);
    strip.setPixelColor(i+12, c);
    strip.setPixelColor(23-i, c);
    strip.show();
    delay(wait);
  }
}

void color4WipeBlink(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<6; i++) {
    strip.setPixelColor(i, c);
    strip.setPixelColor(11-i, c);
    strip.setPixelColor(i+12, c);
    strip.setPixelColor(23-i, c);
    strip.show();
    delay(wait);
  }
  delay(wait*4);
  for(int i=6; i>=0; i--) {
    strip.setPixelColor(i, strip.Color(0,0,0));
    strip.setPixelColor(11-i, strip.Color(0,0,0));
    strip.setPixelColor(i+12, strip.Color(0,0,0));
    strip.setPixelColor(23-i, strip.Color(0,0,0));
    strip.show();
    delay(wait);
  }
}

void color1Rotate1(uint32_t c, uint8_t wait) {
    for(int i=0; i<24; i++) {
      if (i > 0) { 
        strip.setPixelColor(i-1, strip.Color(0,0,0)); 
      }
      else { 
        strip.setPixelColor(23, strip.Color(0,0,0)); 
      }
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void color1Rotate3Solid(uint32_t c, uint8_t wait) { //Rotate three dots with same color
  color1Rotate3(c,c,c,wait); 
}

void color1Rotate3Fade(uint32_t c, uint8_t wait) { //Rotate three dots with fading strenght
  uint32_t c1,c2,c3;
  byte cR, cG, cB;

  int fade1 = 4;
  int fade2 = 8;

  c1 = c;
  
  cB = byte(c);
  c = c >> 8;
  cG = byte(c);
  c = c >> 8;
  cR = byte(c);

  c2 = strip.Color(cR/fade1,cG/fade1,cB/fade1);
  c3 = strip.Color(cR/fade2,cG/fade2,cB/fade2);
  
  _color1Rotate3(c1,c2,c3,wait);
}

void _color1Rotate3(uint32_t c1, uint32_t c2, uint32_t c3, uint8_t wait) { //Helper function to rotate three dots with individual colors
    for(uint16_t i=0; i<24; i++) {
      blankRing();
      int tail1, tail2;
      if (i == 0) {
        tail1 = 23;
        tail2 = 22;
      }
      else if (i == 1) {
        tail1 = 0;
        tail2 = 23;
      }
      else {
        tail1 = i-1;
        tail2 = i-2;
      }
      strip.setPixelColor(i, c1);
      strip.setPixelColor(tail1, c2);
      strip.setPixelColor(tail2, c3);
      strip.show();
      delay(wait);
  }
}

void colorPulse(uint32_t c, uint8_t wait) { //Fades from black to color and back
  byte cRm, cGm, cBm; //Max values
  byte cRt, cGt, cBt; //Temporary values
  
  cBm = byte(c);
  c = c >> 8;
  cGm = byte(c);
  c = c >> 8;
  cRm = byte(c);

  for(int i = 0; i < 101; i++) {  //Fade to color
    cRt = map(i,0,100,0,cRm);
    cGt = map(i,0,100,0,cGm);
    cBt = map(i,0,100,0,cBm);
    for(int p = 0; p < 24; p++) {
       strip.setPixelColor(p, strip.Color(cRt,cGt,cBt));
    }
    delay(wait);
  }

  for(int i = 100; i > 0; i--) {  //Fade to black
    cRt = map(i,1,100,0,cRm);
    cGt = map(i,1,100,0,cGm);
    cBt = map(i,1,100,0,cBm);
    for(int p = 0; p < 24; p++) {
       strip.setPixelColor(p, strip.Color(cRt,cGt,cBt));
    }
    delay(wait);
  }
}

void blankRing() {
  for(uint16_t i=0; i<24; i++) {
    strip.setPixelColor(i, strip.Color(0,0,0));
  }
  strip.show();
}

void blinkRing(uint32_t c = strip.Color(255,255,255)) {
  for(uint16_t i=0; i<24; i++) {
    strip.setPixelColor(i, c);
  }
  strip.show();
  delay(150);
  for(uint16_t i=0; i<24; i++) {
    strip.setPixelColor(i, strip.Color(0,0,0));
  }
  strip.show();
  delay(150);
}

void countRing(uint32_t c = strip.Color(255,255,255), int t) {
  blankRing();
  for(uint16_t i=0; i<t; i++) {
    strip.setPixelColor(i, c);
  }
  strip.show();
}
