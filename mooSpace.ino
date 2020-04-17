#include <Audio.h>
#include "aVerb.h"

aVerb ai_verb;
AudioInputI2S in;
AudioOutputI2S out;
AudioControlSGTL5000 audioShield;
AudioConnection patchCord0(in, 0, ai_verb, 0);
AudioConnection patchCord1(in, 1, ai_verb, 1);
AudioConnection patchCord2(ai_verb, 0, out, 0);
AudioConnection patchCord3(ai_verb, 1, out, 1);

float param1;
float param2;


void setup() {
  AudioMemory(1000);

  audioShield.enable();
  audioShield.lineInLevel(0);
  audioShield.adcHighPassFilterDisable();
  audioShield.inputSelect(AUDIO_INPUT_LINEIN);
  audioShield.volume(0.7);
}

void loop() {
  param1 = (analogRead(A0) / 1023.0) * 24.9 + 0.1;
  ai_verb.setParamValue("Input Diffusion", param1);
  param2 = (analogRead(A1) / 1023.0);
  ai_verb.setParamValue("Room Size", param2);
  delay(10);

}
