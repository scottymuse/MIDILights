#include <Adafruit_DotStar.h>
#include <MIDI.h>

#define NUMPIXELS 60
#define OFFSET 36

struct {
  byte color;
}lights[NUMPIXELS];

//#define DATAPIN 11  // 11 and 13 are the SPI pins on the UNO. Supposedly faster
//#define CLOCKPIN 13 // and not needed in the constructor call
Adafruit_DotStar strip = Adafruit_DotStar(NUMPIXELS, DOTSTAR_BRG);

MIDI_CREATE_DEFAULT_INSTANCE();

void handleNoteOn(byte channel, byte pitch, byte velocity)
{
  byte light = pitch-OFFSET;
  switch(channel) {
    case 0x01 :
      rainbow_note(light);
      break;
  }
/*
  if (light >= 0 && light < NUMPIXELS)
  {
    strip.setPixelColor(light, 0x880000);
  }
*/
}

void handleNoteOff(byte channel, byte pitch, byte velocity)
{
  byte light = pitch-OFFSET;
  switch(channel) {
    case 0x01 :
      rainbow_note_off(light);
      break;
  }
/*  
  if (light >= 0 && light < NUMPIXELS)
  {
    strip.setPixelColor(light, 0);
  }
*/
}

void setup()
{
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleNoteOff(handleNoteOff);
  MIDI.begin(MIDI_CHANNEL_OMNI);

  strip.begin();
  strip.show();
}

void loop()
{
  MIDI.read();
  strip.show();
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

void rainbow_note(byte light) {
  static byte color = 0;
  strip.setPixelColor(light, Wheel(color++));
  if (color > 255) {
    color = 0;
  }
}

void rainbow_note_off(byte light) {
  strip.setPixelColor(light, 0);
}
