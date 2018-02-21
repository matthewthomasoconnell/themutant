

#include <Audio.h>
#include <Wire.h>
#include <Bounce.h>

// GUItool: begin automatically generated code
AudioSynthNoiseWhite     voice2n;        //xy=284,645.6666870117188
AudioSynthWaveform       voice1a;        //xy=285,411
AudioSynthNoiseWhite     voice1n;        //xy=285,487
AudioSynthWaveform       voice3a;        //xy=284,737.3333435058594
AudioSynthWaveform       voice3b;        //xy=284,779.3333435058594
AudioSynthWaveform       voice2b;        //xy=285,608.6666870117188
AudioSynthWaveform       voice1b;        //xy=286,448
AudioSynthWaveform       voice2a;        //xy=286,568.6666870117188
AudioSynthNoiseWhite     voice3n;        //xy=285,821.3333435058594
AudioSynthNoiseWhite     voice4n;        //xy=284.6666564941406,1042.1429026126862
AudioSynthWaveform       voice4b;        //xy=285.6666564941406,998.1429026126862
AudioSynthWaveform       voice4a;        //xy=286.6666564941406,957.1429026126862
AudioMixer4              voice1mix;      //xy=434,433
AudioSynthWaveformDc     voice1env;      //xy=434,489
AudioMixer4              voice2mix;      //xy=434,588.6666870117188
AudioSynthWaveformDc     voice2env;      //xy=434,648.6666870117188
AudioMixer4              voice3mix;      //xy=436,762.3333435058594
AudioSynthWaveformDc     voice3env;      //xy=437,822.3333435058594
AudioSynthWaveformDc     voice4env;      //xy=437.6666564941406,1037.1429026126862
AudioMixer4              voice4mix;      //xy=439.6666564941406,978.1429026126862
AudioEffectMultiply      voice4multiply; //xy=626.2380790710449,1008.0000705718994
AudioSynthWaveformDc     voice4filterenv; //xy=628.2380790710449,1042.0000705718994
AudioEffectMultiply      voice3multiply; //xy=633.9999771118164,806.3333549499512
AudioSynthWaveformDc     voice3filterenv; //xy=636.9999771118164,840.3333549499512
AudioMixer4              voice3filterModMixer;         //xy=638.0951919555664,894.0952186584473
AudioMixer4              voice4filterModMixer;         //xy=639.3650512695312,1092.03173828125
AudioEffectMultiply      voice1multiply; //xy=645.6666870117188,431.22224283218384
AudioSynthWaveformDc     voice1filterenv; //xy=646.6666870117188,468.22224283218384
AudioMixer4              voice1filterModMixer;         //xy=647.2221984863281,522.825439453125
AudioEffectMultiply      voice2multiply; //xy=648.9999771118164,627.6666984558105
AudioSynthWaveformDc     voice2filterenv; //xy=650.9999771118164,665.6666984558105
AudioSynthWaveform       masterLFO;      //xy=654.0477142333984,383.3333110809326
AudioMixer4              voice2filterModMixer;         //xy=655.3174133300781,718.2221984863281
AudioFilterStateVariable voice1filter;   //xy=894,462
AudioFilterStateVariable voice2filter;   //xy=899,630.6666870117188
AudioFilterStateVariable voice3filter;   //xy=902,807.3333435058594
AudioFilterStateVariable voice4filter;   //xy=905.6666641235352,977.0000553131104
AudioMixer4              oscillatorMixer;      //xy=1113.6667098999023,473.3333306312561
AudioMixer4              masterMixer;         //xy=1118.4166717529297,545.4999809265137
AudioEffectDelay         masterDelay;         //xy=1119.6666717529297,715.3333435058594
AudioFilterStateVariable delayFilter;        //xy=1131.2500457763672,617.5000247955322
AudioOutputI2S           i2s1;           //xy=1362.5000534057617,645.1666922569275
AudioConnection          patchCord1(voice2n, 0, voice2mix, 2);
AudioConnection          patchCord2(voice1a, 0, voice1mix, 0);
AudioConnection          patchCord3(voice1n, 0, voice1mix, 2);
AudioConnection          patchCord4(voice3a, 0, voice3mix, 0);
AudioConnection          patchCord5(voice3b, 0, voice3mix, 1);
AudioConnection          patchCord6(voice2b, 0, voice2mix, 1);
AudioConnection          patchCord7(voice1b, 0, voice1mix, 1);
AudioConnection          patchCord8(voice2a, 0, voice2mix, 0);
AudioConnection          patchCord9(voice3n, 0, voice3mix, 2);
AudioConnection          patchCord10(voice4n, 0, voice4mix, 2);
AudioConnection          patchCord11(voice4b, 0, voice4mix, 1);
AudioConnection          patchCord12(voice4a, 0, voice4mix, 0);
AudioConnection          patchCord13(voice1mix, 0, voice1multiply, 0);
AudioConnection          patchCord14(voice1env, 0, voice1multiply, 1);
AudioConnection          patchCord15(voice2mix, 0, voice2multiply, 0);
AudioConnection          patchCord16(voice2env, 0, voice2multiply, 1);
AudioConnection          patchCord17(voice3mix, 0, voice3multiply, 0);
AudioConnection          patchCord18(voice3env, 0, voice3multiply, 1);
AudioConnection          patchCord19(voice4env, 0, voice4multiply, 1);
AudioConnection          patchCord20(voice4mix, 0, voice4multiply, 0);
AudioConnection          patchCord21(voice4multiply, 0, voice4filter, 0);
AudioConnection          patchCord22(voice4filterenv, 0, voice4filterModMixer, 0);
AudioConnection          patchCord23(voice3multiply, 0, voice3filter, 0);
AudioConnection          patchCord24(voice3filterenv, 0, voice3filterModMixer, 0);
AudioConnection          patchCord25(voice3filterModMixer, 0, voice3filter, 1);
AudioConnection          patchCord26(voice4filterModMixer, 0, voice4filter, 1);
AudioConnection          patchCord27(voice1multiply, 0, voice1filter, 0);
AudioConnection          patchCord28(voice1filterenv, 0, voice1filterModMixer, 0);
AudioConnection          patchCord29(voice1filterModMixer, 0, voice1filter, 1);
AudioConnection          patchCord30(voice2multiply, 0, voice2filter, 0);
AudioConnection          patchCord31(voice2filterenv, 0, voice2filterModMixer, 0);
AudioConnection          patchCord32(masterLFO, 0, voice1filterModMixer, 1);
AudioConnection          patchCord33(masterLFO, 0, voice2filterModMixer, 1);
AudioConnection          patchCord34(masterLFO, 0, voice3filterModMixer, 1);
AudioConnection          patchCord35(masterLFO, 0, voice4filterModMixer, 1);
AudioConnection          patchCord36(voice2filterModMixer, 0, voice2filter, 1);
AudioConnection          patchCord37(voice1filter, 0, oscillatorMixer, 0);
AudioConnection          patchCord38(voice2filter, 0, oscillatorMixer, 1);
AudioConnection          patchCord39(voice3filter, 0, oscillatorMixer, 2);
AudioConnection          patchCord40(voice4filter, 0, oscillatorMixer, 3);
AudioConnection          patchCord41(oscillatorMixer, 0, masterMixer, 0);
AudioConnection          patchCord42(masterMixer, masterDelay);
AudioConnection          patchCord43(masterMixer, 0, i2s1, 0);
AudioConnection          patchCord44(masterMixer, 0, i2s1, 1);
AudioConnection          patchCord45(masterDelay, 0, delayFilter, 0);
AudioConnection          patchCord46(delayFilter, 0, masterMixer, 3);
AudioControlSGTL5000     sgtl5000_1;     //xy=1353,689
// GUItool: end automatically generated code


// Sets constants for Knobs and Sliders
const int KNOB1 = A21;
const int KNOB2 = A19;
const int KNOB3 = A18;
const int KNOB4 = A6;
const int KNOB5 = A7;
const int KNOB6 = A2;
const int KNOB7 = A3;
const int SLIDER1 = A15;
const int SLIDER2 = A14;
const int SLIDER3 = A12;
const int SLIDER4 = A13;
const int FOOTPEDAL = A20;
const int SWITCHLEFTBOTTOM = 30;
const int SWITCHLEFTMIDDLE = 29;
const int SWITCHLEFTTOP = 7;
const int SWITCHRIGHTBOTTOM = 28;
const int SWITCHRIGHTMIDDLE = 27;
const int SWITCHRIGHTTOP = 26;

// Effects Constants
const int TREMOLO = 0;
const int WARBLE = 1;
const int DELAY = 2;
const int BELLOWS = 3;

const int TONEBANK[6][3] = {  
   {WAVEFORM_SQUARE, WAVEFORM_SQUARE, BELLOWS},
   {WAVEFORM_TRIANGLE, WAVEFORM_TRIANGLE, BELLOWS},
   {WAVEFORM_SAWTOOTH, WAVEFORM_SAWTOOTH, BELLOWS},
   {WAVEFORM_SQUARE, WAVEFORM_TRIANGLE, BELLOWS},
   {WAVEFORM_SINE, WAVEFORM_SINE, BELLOWS},
   {WAVEFORM_SQUARE, WAVEFORM_SAWTOOTH_REVERSE, BELLOWS} 
};

// Tonebank Constants
const int ORGAN = 0;
const int LATCH = 1;
const int TAMBOURA = 2;

int knob1, knob2, knob3, knob4, knob5, knob6, knob7, footpedal;

// Initialize Buttons and Note Pins
const int notePins[4] = {0,1,24,25};
const int indicatorLeds[4] = {6,2,8,4};
//int btnState[4];
int channelOn[4] = {false, false, false, false}; // I don't understand why this solves the envelope problem, but it does
int envelopeOpen[4] = {false, false, false, false};


// Tamboura Stuff
unsigned long previousTambouraMillis = 0;        // will store last time LED was updated
unsigned long tambouraInterval = 10000;


// Initialize Buttons
Bounce noteBounce[] = {
  Bounce(notePins[0],10),
  Bounce(notePins[1],10),
  Bounce(notePins[2],10),
  Bounce(notePins[3],10)
};


// Initialize Rotary Switches
const int ROTARY_REFRESH_RATE = 50;
const int TONEBANK_ROTARY_PIN = A17;
const int TRANSPOSE_ROTARY_PIN = A16;
long toneBankLastChecked = 0;
long transposeLastChecked = 0;
int current_transpose = 0;
int newScale;

//Oscillator Intervals and Ranges
int oscillator_octave = 4;
int oscillator_range = 5;
int oscillator_interval = 5; // in half steps (5 => 4ths, 7 => 5ths)
int slider1, slider2, slider3, slider4;

// Initialize the Tonebank variables
// I'd like to put volume, octave, and other variables in here for more consistency
int oldTonebankNumber, tonebankNumber, voiceaWaveform, voicebWaveform, tonebankEffect, lastToneBankEffect;
float warbleAmount, bellowsAmount;



// Initialize Scales and Waveforms
// C C# D D# E F F# G G# A A# B
const float frequencies[12] = {4186.01, 4434.92, 4698.63, 4978.03, 5274.04, 5587.65, 5919.91, 6271.93, 6644.88, 7040.00, 7458.62, 7902.13};
int old_transpose = 0; // I don't remember what this is doing.

// Initialize Modes
// C C# D D# E F F# G G# A A# B
// 0 1  2 3  4 5 6  7 8  9 10 11
// These modes are based off of the root C, which can be transposed later.
const int modes[6][4][2] = 
{
  {{ 0, 2 }, { 2, 4 }, { 7, 9 },{ 9, 11 }},         // Mode 1 {{1|C,2|D},{2|D,3|E},{5|G,6|A},{6|A,8|C}}  PENTATONIC A
  {{ 9, 12 }, { 12, 14 }, { 14, 16 },{ 19, 21 }},   // Mode 2 {{6|A,8|C},{1|C,2|D},{2|D,3|E},{5|G,6|A}}  PENTATONIC B
  {{ 0, 5 }, { 7, 9 }, { 9, 11 },{ 11, 12 }},       // Mode 3 {{1|C,4|F},{5|G,6|A},{6|A,7|B},{7|B,8|C}}  ALTERNATIVE
  {{ 7, 9 }, { 12, 14 }, { 14, 16 },{ 19, 21 }},    // Mode 4 {{5|G,6|A},{1|C,2|D},{2|D,3|E},{5|G,6|A}}  STILL LIFE
  {{ 5, 7 }, { 12, 14 }, { 16, 17 },{ 19, 21 }},    // Mode 5 {{4|F,5|G},{1|C,2|D},{3|E,4|F},{5|G,6|A}}  SURFER
  {{ 0, 12 }, { 0, 12 }, { 0, 12 },{ 0, 12 }}       // Mode 6 {{1|C,8|C},{1|C,8|C},{1|C,8|C},{1|C,8|C}}  TAMBOURA
};



// Initialize Envelope
int droneMode;
int attackTime, decayTime, releaseTime;
int filterAttackTime, filterDecayTime, filterReleaseTime;
float sustainLevel;
float filterSustainLevel;
bool noteTrigFlag[4];
unsigned long attackWait[4];
float oscillatorDetuneAmount;


// Initialize "Bellows"
const int lengthIntervalFilter = 30;
unsigned beginningFilterInterval, currentMillis, bellowsPressureMapped;
float currentBellowsPressure = 0;
float lastBellowsPressure = 0;
const float BELLOWS_RELEASE_CONSTANT = .04;
const float BELLOWS_FILL_CONSTANT = .4;


void setup() {
  initializePins();
  initializeTeensyAudio();
  initializeOscillators();
  initializeMixersandFilters();
  flashRebootLights(60);
}

void loop() {
  
  updateTonebank(); // Right Rotary Switch
  updateKnobs(); // 7 Rotary Pots
  updateSliders(); // 4 Slider Pots
  updateTranspose(); // Left Rotary Switch
  updateDroneMode(); // Left Toggle Switch
  updateEnvelopeMode(); // Right Toggle Switch
  updateKeys(); // 4 Momentary Switches
  updateIndicators(); // 4 Indicator Leds
  
}







