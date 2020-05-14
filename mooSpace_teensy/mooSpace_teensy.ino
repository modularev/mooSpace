#include<Audio.h>
#include <elapsedMillis.h>
#include"mooSpace.h"
//#include"filter_table.h"
#include "Smoothed.h"

#define upper_switch 4
#define lower_switch 5
#define shift_button 3
#define footswitch 2
#define blue_led 30
#define red_led 32

const float max_adc_value = 998.0;

elapsedMillis elapsed_time;

unsigned int led_time = 100;

DMAMEM mooSpace mooSpace;
AudioInputI2S in;
AudioOutputI2S out;
AudioControlSGTL5000 audioShield;

AudioConnection patchCord0(in, 0, mooSpace, 0);
AudioConnection patchCord1(in, 1, mooSpace, 1);
AudioConnection patchCord2(mooSpace, 0, out, 0);
AudioConnection patchCord3(mooSpace, 1, out, 1);

const int knob_pin[5] = {A0, A1, A2, A3, A8};

Smoothed <unsigned int> current_knob[5];
uint16_t last_main[5];
uint16_t last_shift[5];

int curr_button = 0;
int prev_button = 0;
int page = 0;

int main_checked = 0;
int shift_checked = 0;


const char* param[] = {
  "smear",
  "decay",
  "drag",
  "push",
  "mix",
  "modulate",
  "lag",
  "High Cut",
  "Low Cut",
  "colour"
};

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

/*
void set_smear(uint16_t adc_reading) {
  mooSpace.setParamValue(param[0], adc_reading / max_adc_value);
}

void set_decay(uint16_t adc_reading) {
  mooSpace.setParamValue(param[1], adc_reading / max_adc_value);
}

void set_drag(uint16_t adc_reading) {
  mooSpace.setParamValue(param[2], adc_reading / max_adc_value);
}

void set_push(uint16_t adc_reading) {
  mooSpace.setParamValue(param[3], adc_reading / max_adc_value);
}

void set_mix(uint16_t adc_reading) {
  mooSpace.setParamValue(param[4], adc_reading / max_adc_value);
}

void set_move(uint16_t adc_reading) {
  mooSpace.setParamValue(param[5], adc_reading);
}

void set_lag(uint16_t adc_reading) {
  mooSpace.setParamValue(param[6], adc_reading / max_adc_value);
}

void set_lpf(uint16_t adc_reading) {
  mooSpace.setParamValue(param[7], adc_reading / max_adc_value);
}

void set_hpf(uint16_t adc_reading) {
  mooSpace.setParamValue(param[8], adc_reading / max_adc_value);
}

void set_colour(uint16_t adc_reading) {
  mooSpace.setParamValue(param[9], adc_reading / max_adc_value);
}*/



void setup() {
  Serial.begin(9600);
  AudioMemory(100);
  //mooSpace.setDevice(0, 0);
  //mooSpace.start();

  //analogReadAveraging(16);

  audioShield.enable();
  audioShield.lineInLevel(0);
  audioShield.lineOutLevel(14);
  audioShield.adcHighPassFilterEnable();
  audioShield.inputSelect(AUDIO_INPUT_LINEIN);
  audioShield.volume(0.7);
/*  audioShield.surroundSoundEnable();
  audioShield.surroundSound(5);*/

  // Start ADC Smoothing
  for (int i = 0; i < 5; i++) {
    current_knob[i].begin(SMOOTHED_EXPONENTIAL, 4);
  }

  // define pin pages
  pinMode(footswitch, INPUT_PULLUP);
  pinMode(shift_button, INPUT_PULLUP);
  pinMode(upper_switch, INPUT_PULLUP);
  pinMode(lower_switch, INPUT_PULLUP);
  pinMode(red_led, OUTPUT);
  pinMode(blue_led, OUTPUT);
  digitalWrite(red_led, HIGH);
  digitalWrite(blue_led, LOW);


}

void main_page(int i) {

  //if (digitalRead(lower_switch) == LOW) mooSpace.setParamValue("reverse", 1);

  if (current_knob[i].get() != last_main[i]) {
    elapsed_time = 0;
    digitalWrite(red_led, LOW);
    mooSpace.setParamValue(param[i], current_knob[i].get() / max_adc_value);
    /*switch (i) {
      case 0:
        set_smear(current_knob[i].get());
        break;

      case 1:
        set_decay(current_knob[i].get());
        break;

      case 2:
        set_drag(current_knob[i].get());
        break;

      case 3:
        set_push(current_knob[i].get());
        break;

      case 4:
        set_mix(current_knob[i].get());
        break;
    }*/
    last_main[i] = current_knob[i].get();
  }
  if (elapsed_time > led_time) digitalWrite(red_led, HIGH);
}

void shift_page(int i) {

  if (current_knob[i].get() != last_shift[i]) {
    elapsed_time = 0;
    digitalWrite(blue_led, LOW);
    mooSpace.setParamValue(param[i+5], current_knob[i].get() / max_adc_value);
    /*switch (i) {
      case 0:
        set_move(current_knob[i].get());
        break;

      case 1:
        set_lag(current_knob[i].get());
        break;

      case 2:
        set_lpf(current_knob[i].get());
        break;

      case 3:
        set_hpf(current_knob[i].get());
        break;

      case 4:
        set_colour(current_knob[i].get());
        break;
    }*/
    last_shift[i] = current_knob[i].get();
  }
  if (elapsed_time > led_time) digitalWrite(blue_led, HIGH);
}

void serialprint(int i) {
  Serial.print(page);
  Serial.print("\t");
  Serial.print(i);
  Serial.print("\t");
  Serial.println(current_knob[i].get());
}

void check_page() {
  curr_button = !(digitalRead(shift_button));

  if (prev_button == LOW && curr_button == HIGH) {
    if (page == 0) {
      page = 1;
      for (int i = 0 ; i < 5 ; i++) {
        last_main[i] = current_knob[i].get();
      }
      digitalWrite(blue_led, HIGH);
      digitalWrite(red_led, LOW);
      main_checked = 0;
    }
    else if (page == 1) {
      page = 0;
      for (int i = 0 ; i < 5 ; i++) {
        last_shift[i] = current_knob[i].get();
      }
      digitalWrite(red_led, HIGH);
      digitalWrite(blue_led, LOW);
      shift_checked = 0;
    }
  }

  if (main_checked == 0) {
    for (int i = 0 ; i < 5 ; i++) {
      last_shift[i] = current_knob[i].get();
    }
    main_checked = 1;
  }
  else if (shift_checked == 0) {
    for (int i = 0 ; i < 5 ; i++) {
      last_main[i] = current_knob[i].get();
    }
    shift_checked = 1;
  }

  prev_button = curr_button;
}


void loop() {
  //read knob positions
  for (int i = 0 ; i < 5 ; i++) {
    current_knob[i].add(analogRead(knob_pin[i]));
  }

  check_page();

  for (int i = 0 ; i < 5 ; i++) {
    if (page == 0 ) main_page(i);
    else if (page == 1) shift_page(i);
  }
}
