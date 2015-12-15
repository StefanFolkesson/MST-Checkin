/*###

Project: Bifrost
Module: bifrost_checkin_indicator_bb
Description: Runs on Trinket (5v 16MHz) to control a 24 led neopixel ring according to data sent via bit-banged serial from a Raspberry Pi.

###*/
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

/*### Settings ###*/
int setPixelPin = 4;
int setDataPin = 1;
int setClockPin = 0;

int setWait = 30;            //Default delay used in animations.

/*## Memory ##*/
volatile byte memColorR = 0; //Red
volatile byte memColorG = 0; //Green
volatile byte memColorB = 0; //Blue
volatile byte memAnimation = 0; //Animation to run
volatile int memOperation = 0; //0 = run no animation, 1 = run once, 2 = run continous
 

Adafruit_NeoPixel strip = Adafruit_NeoPixel(24, setPixelPin, NEO_GRB + NEO_KHZ800); //Initiate Neopixel ring



/*## Setup ##*/
void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code


/*## Setup Pins ##*/
  pinMode(setDataPin, INPUT);
  pinMode(setClockPin, INPUT);
  attachInterrupt(0, receiveEvent, FALLING); //Enables Interupt 0 (= pin 2) on falling flank and calls function "receiveEvent"

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  blinkRing(); //Blink once to indicate startup
}


/*## Main loop ##*/
void loop() {
  if (memOperation == 2) {        //Continous animation
    startAnimation(memAnimation, strip.Color(memColorR, memColorG, memColorB));
  }
  else if (memOperation == 1) {   //Single animation
    memOperation = 0; //Done running
    blankRing();      //Clear prevoius pixel data
    startAnimation(memAnimation, strip.Color(memColorR, memColorG, memColorB));
  }
}


/*## Functions ##*/
void startAnimation(byte a, int32_t c) {  //Calls animation (found in animations.ino)
    switch (a) {
    case 1: //Singlewipe to color
      color1Wipe(c,setWait);
      break;
    case 2: //Doublewipe to color
      color2Wipe(c,setWait);
      break;
    case 3: //Quadwipe to color
      color4Wipe(c,setWait);
      break;
    case 4: //Quadwipe (mirror) to color
      color4WipeMirror(c,setWait);
      break;
    case 5: //Rotate one dot
      color1Rotate1(c,setWait);
      break;
    case 6: //Rotate three dots with same color
      color1Rotate3Solid(c,setWait);
      break;
    case 7: //Rotate three dots with fading color
      color1Rotate3Fade(c,setWait);
      break;
    case 8: //Fade the color from black to color and back
      colorPulse(c,setWait);
      break;
    default: //Do nothing
      break;
  }
}


/*## Interupt ##*/
void receiveEvent() { //Function runs on falling flank on pin 2
  int rSt = 0;        //State of clockpin, used to find positive flank
  int rCn = 0;        //Number of recieved bits
  int32_t rDa = 0;    //Total serial Data, 32 bits
  int32_t newA = 0;   //Animation command (what animation to run), converts to byte (only 7 bits used)
  int32_t newO = 0;   //Operations command (single och continous animation), only 1 bit used, controls int value.
  int32_t newCR = 0;  //Red command, converts to byte.
  int32_t newCG = 0;  //Green command, converts to byte.
  int32_t newCB = 0;  //Blue command, converts to byte.

  while(rCn < 32) {
    if (digitalRead(setClockPin) == HIGH && rSt == 0) {       //Positive flank
      rSt = 1;
      rCn++;
      rDa = bitWrite(rDa, 32 - rCn, digitalRead(setDataPin)); //Data recievd from most sigificant bit, bitWrite writes from least significant bit 
    }
    else if (digitalRead(setClockPin) == LOW && rSt == 1) {   //Negative flank
      rSt = 0;
    }
  }

  
  newA = (rDa >> 24) & 0x7F;  //Bitshift to remove color data and bitwise and to remove operations bit, converts to byte later
  newO = rDa >> 32;           //Bitshift to remove color and animation data
  newCR = rDa >> 16;          //Bitshift to remove other color data, converts to byte later
  newCG = rDa >> 8;           //Bitshift to remove other color data, converts to byte later
  newCB = rDa;                //No bitshift needed, converts to byte later
  
  memColorR = (byte)newCR;    //Save to memory
  memColorG = (byte)newCG;    //Save to memory
  memColorB = (byte)newCB;    //Save to memory
  memAnimation = (byte)newA;  //Save to memory

  if (newO == 0) {            //If single animation
    memOperation = 1;         //Save to memory
  }
  else {                      //If continous animation
    memOperation = 2;         //Save to memory
  }

}



