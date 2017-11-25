#include <Adafruit_DotStar.h>
#include <MIDI.h>

#define NUMPIXELS 60

//#define DATAPIN 11  // 11 and 13 are the SPI pins on the UNO. Supposedly faster
//#define CLOCKPIN 13 // and not needed in the constructor call
Adafruit_DotStar strip = Adafruit_DotStar(NUMPIXELS, DOTSTAR_BRG);

MIDI_CREATE_DEFAULT_INSTANCE();

void handleNoteOn(byte channel, byte pitch, byte velocity)
{
  if (pitch-30 >= 0 && pitch-30 < NUMPIXELS)
  {
    strip.setPixelColor(pitch-30, 0x880000);
  }
  strip.show();
}

void handleNoteOff(byte channel, byte pitch, byte velocity)
{
  if (pitch-30 >= 0 && pitch-30 < NUMPIXELS)
  {
    strip.setPixelColor(pitch-30, 0);
  }
  strip.show();
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
}
