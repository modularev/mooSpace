#include<Audio.h>
#include"mooSpace.h"
#include"filter_table.h"

#define upper_switch 4
#define lower_switch 5
#define shift_button 3
#define footswitch 2
#define red_led 30
#define blue_led 32

/*int SR = 44100; // Sampling Rate
  int BS = 128; // Block Size
  DspFaust mooSpace(SR, BS);*/

mooSpace mooSpace;
AudioInputI2S in;
AudioOutputI2S out;
AudioControlSGTL5000 audioShield;

AudioConnection patchCord0(in, 0, mooSpace, 0);
AudioConnection patchCord1(in, 1, mooSpace, 1);
AudioConnection patchCord2(mooSpace, 0, out, 0);
AudioConnection patchCord3(mooSpace, 1, out, 1);

const int knob_pin[5] = {A0, A1, A2, A3, A8};
uint16_t current_knob[5] = {0, 0, 0, 0, 0};
uint16_t last_knob[5] = {0, 0, 0, 0, 0};

float smear;  // modulation of input diffusion
float decay;  // feedback of reverberation network
float drag;   // modulation of reverberation network
float push;   // amount of cubical distortion
float mix;    // mix between dry and wet sound
float move;   // random modlation of allpass-delaytimes
uint16_t lag;      // input delay
uint16_t lpf;      // highcut
uint16_t hpf;      // lowcut
float colour; // dampening in reverberation network
uint8_t reverse;  // activate reverse delay

int shift_state = 0;

void set_smear(uint16_t adc_reading) {
  mooSpace.setParamValue("smear", (adc_reading / 1023.0) * 25.0);
}

void set_decay(uint16_t adc_reading) {
  mooSpace.setParamValue("decay", adc_reading / 1023.0);
}

void set_drag(uint16_t adc_reading) {
  mooSpace.setParamValue("drag", (adc_reading / 1023.0) * 10.0);
}

void set_push(uint16_t adc_reading) {
  mooSpace.setParamValue("push", adc_reading / 1023.0);
}

void set_mix(uint16_t adc_reading) {
  mooSpace.setParamValue("mix", adc_reading / 1023.0);
}

void set_move(uint16_t adc_reading) {
  mooSpace.setParamValue("modulate", adc_reading / 1023.0);
}

void set_lag(uint16_t adc_reading) {
  mooSpace.setParamValue("lag", adc_reading >> 2);
}

void set_lpf(uint16_t adc_reading) {
  mooSpace.setParamValue("High Cut", filter_table[adc_reading >> 1]);
}

void set_hpf(uint16_t adc_reading) {
  mooSpace.setParamValue("Low Cut", filter_table[511 - (adc_reading >> 1)]);
}

void set_colour(uint16_t adc_reading) {
  mooSpace.setParamValue("colour", adc_reading / 1023.0);
}



void setup() {
  AudioMemory(1500);

  //mooSpace.setDevice(0, 0);
  //mooSpace.start();

  audioShield.enable();
  audioShield.lineInLevel(0);
  audioShield.lineOutLevel(14);
  audioShield.adcHighPassFilterDisable();
  audioShield.inputSelect(AUDIO_INPUT_LINEIN);
  audioShield.volume(0.7);

  // define pin modes
  pinMode(footswitch, INPUT_PULLUP);
  pinMode(shift_button, INPUT_PULLUP);
  pinMode(upper_switch, INPUT_PULLUP);
  pinMode(lower_switch, INPUT_PULLUP);
  pinMode(red_led, OUTPUT);
  pinMode(blue_led, OUTPUT);

  digitalWrite(red_led, LOW);
  digitalWrite(blue_led, LOW);

}

void main_check(uint16_t i) {

  if ((current_knob[i] < (last_knob[i] - 2)) || ((current_knob[i] > (last_knob[i] + 2)))) {
    switch (i) {
      case 0:
        set_smear(current_knob[i]);
        break;

      case 1:
        set_decay(current_knob[i]);
        break;

      case 2:
        set_drag(current_knob[i]);
        break;

      case 3:
        set_push(current_knob[i]);
        break;

      case 4:
        set_mix(current_knob[i]);
        break;
    }
  }
}

void shift_check(uint16_t i) {

  if ((current_knob[i] < (last_knob[i] - 2)) || ((current_knob[i] > (last_knob[i] + 2)))) {
    switch (i) {
      case 0:
        set_move(current_knob[i]);

        break;

      case 1:
        set_lag(current_knob[i]);
        break;

      case 2:
        set_lpf(current_knob[i]);
        break;

      case 3:
        set_hpf(current_knob[i]);
        break;

      case 4:
        set_colour(current_knob[i]);
        break;
    }
  }
}

void serialprint(uint16_t i) {
  Serial.print(shift_state);
  Serial.print("\t");
  Serial.print(current_knob[i]);
  Serial.print("\t");
  Serial.println(i);
}

void loop() {

  shift_state = digitalRead(shift_button);

  //read knob positions
  for (int i = 0 ; i < 5 ; i++) {
    last_knob[i] = current_knob[i];

    current_knob[i] = analogRead(knob_pin[i]);

    if (shift_state == LOW) shift_check(i);
    else main_check(i);
  }
  delay(10);

}
