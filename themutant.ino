#include <Audio.h>
#include <Wire.h>
#include <Bounce.h>

// GUItool: begin automatically generated code
AudioSynthNoiseWhite     voice2n;        //xy=122,332
AudioSynthWaveform       voice1a;        //xy=123,98
AudioSynthWaveform       voice3a;        //xy=122,424
AudioSynthNoiseWhite     voice1n;        //xy=123,174
AudioSynthWaveform       voice3b;        //xy=122,466
AudioSynthWaveform       voice2b;        //xy=123,295
AudioSynthWaveform       voice1b;        //xy=124,135
AudioSynthNoiseWhite     voice4n;        //xy=122,729
AudioSynthWaveform       voice2a;        //xy=124,255
AudioSynthNoiseWhite     voice3n;        //xy=123,508
AudioSynthWaveform       voice4b;        //xy=123,685
AudioSynthWaveform       voice4a;        //xy=124,644
AudioMixer4              voice1mix;      //xy=272,120
AudioSynthWaveformDc     voice1env;      //xy=272,176
AudioMixer4              voice2mix;      //xy=272,275
AudioSynthWaveformDc     voice2env;      //xy=272,335
AudioMixer4              voice3mix;      //xy=274,449
AudioSynthWaveformDc     voice3env;      //xy=275,509
AudioSynthWaveformDc     voice4env;      //xy=275,724
AudioMixer4              voice4mix;      //xy=277,665
AudioEffectMultiply      voice4multiply; //xy=464,695
AudioSynthWaveformDc     voice4filterenv; //xy=466,729
AudioEffectMultiply      voice3multiply; //xy=471,493
AudioSynthWaveformDc     voice3filterenv; //xy=474,527
AudioMixer4              voice3filterModMixer; //xy=476,581
AudioMixer4              voice4filterModMixer; //xy=477,779
AudioEffectMultiply      voice1multiply; //xy=483,118
AudioSynthWaveformDc     voice1filterenv; //xy=484,155
AudioMixer4              voice1filterModMixer; //xy=485,209
AudioEffectMultiply      voice2multiply; //xy=486,314
AudioSynthWaveformDc     voice2filterenv; //xy=488,352
AudioSynthWaveform       masterLFO;      //xy=492,70
AudioMixer4              voice2filterModMixer; //xy=493,405
AudioFilterStateVariable voice1filter;   //xy=732,149
AudioFilterStateVariable voice2filter;   //xy=737,317
AudioFilterStateVariable voice3filter;   //xy=740,494
AudioFilterStateVariable voice4filter;   //xy=743,664
AudioMixer4              oscillatorMixer; //xy=951,160
AudioOutputI2S           i2s1;           //xy=1200,332
AudioConnection          patchCord1(voice2n, 0, voice2mix, 2);
AudioConnection          patchCord2(voice1a, 0, voice1mix, 0);
AudioConnection          patchCord3(voice3a, 0, voice3mix, 0);
AudioConnection          patchCord4(voice1n, 0, voice1mix, 2);
AudioConnection          patchCord5(voice3b, 0, voice3mix, 1);
AudioConnection          patchCord6(voice2b, 0, voice2mix, 1);
AudioConnection          patchCord7(voice1b, 0, voice1mix, 1);
AudioConnection          patchCord8(voice4n, 0, voice4mix, 2);
AudioConnection          patchCord9(voice2a, 0, voice2mix, 0);
AudioConnection          patchCord10(voice3n, 0, voice3mix, 2);
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
AudioConnection          patchCord41(oscillatorMixer, 0, i2s1, 0);
AudioConnection          patchCord42(oscillatorMixer, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=1191,376
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
const int FLOATINGPOINT = A11;
const int SWITCHLEFTBOTTOM = 30;
const int SWITCHLEFTMIDDLE = 29;
const int SWITCHLEFTTOP = 7;
const int SWITCHRIGHTBOTTOM = 28;
const int SWITCHRIGHTMIDDLE = 27;
const int SWITCHRIGHTTOP = 26;



const int TONEBANK[13][3] = {  
   {WAVEFORM_SQUARE, WAVEFORM_SQUARE, 0},
   {WAVEFORM_SQUARE, WAVEFORM_SAWTOOTH, 0},
   {WAVEFORM_SAWTOOTH, WAVEFORM_SAWTOOTH, 0},
   {WAVEFORM_SQUARE, WAVEFORM_TRIANGLE, 0},
   {WAVEFORM_TRIANGLE, WAVEFORM_SAWTOOTH, 0},
   {WAVEFORM_TRIANGLE, WAVEFORM_SAWTOOTH, 170},
   {WAVEFORM_SINE, WAVEFORM_SAWTOOTH, 0},
   {WAVEFORM_SINE, WAVEFORM_SQUARE, 0},
   {WAVEFORM_TRIANGLE, WAVEFORM_TRIANGLE, 0},
   {WAVEFORM_TRIANGLE, WAVEFORM_TRIANGLE, 70},
   {WAVEFORM_SINE, WAVEFORM_TRIANGLE, 0},
   {WAVEFORM_SINE, WAVEFORM_SINE, 0},
   {WAVEFORM_SINE, WAVEFORM_SINE, 255}
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
int channelOn[4] = {false, false, false, false}; // I don't know why he chose int here.
int envelopeOpen[4] = {false, false, false, false};
int notePlaying[4] = {false, false, false, false};

// Tamboura Stuff
long tambouraPreviousMillis[4] = {0, 0, 0, 0};
long randomNotePlayInterval[4] = {random(2000, 7000),random(2000, 7000),random(2000, 7000),random(2000, 7000)};

// Initialize Buttons
Bounce noteBounce[] = {
  Bounce(notePins[0],10),
  Bounce(notePins[1],10),
  Bounce(notePins[2],10),
  Bounce(notePins[3],10)
};


// Initialize Rotary Switches
const int ROTARY_REFRESH_RATE = 50;
const int MODE_ROTARY_PIN = A17;
const int TRANSPOSE_ROTARY_PIN = A16;
long modeLastChecked = 0;
long transposeLastChecked = 0;
long tonebankLastChecked = 0;
long octaveLastChecked = 0;
int oldTranspose = 0;
int currentTranspose = 0;
int currentMode = 0;
int newScale;
int slider1, slider2, slider3, slider4;
bool footpedalIsInserted = false;

// Initialize the Tonebank variables
// I'd like to put volume, octave, and other variables in here for more consistency
int oldTonebankNumber, tonebankNumber, oldOctaveNumber, octaveNumber, voiceaWaveform, voicebWaveform, noiseLevel;


// Initialize Scales and Waveforms
// C C# D D# E F F# G G# A A# B
const float frequencies[12] = {4186.01, 4434.92, 4698.63, 4978.03, 5274.04, 5587.65, 5919.91, 6271.93, 6644.88, 7040.00, 7458.62, 7902.13};

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
  {{ 7, 12 }, { 12, 24 }, { 12, 24 },{ 0, 12 }}       // Mode 6 {{1|C,8|C},{1|C,8|C},{1|C,8|C},{1|C,8|C}}  TAMBOURA
};


// Initialize Envelope
int droneMode, previousDroneMode;
int attackTime, decayTime, releaseTime;
int filterAttackTime, filterDecayTime, filterReleaseTime;
float sustainLevel;
float filterSustainLevel;
bool noteTrigFlag[4];
unsigned long attackWait[4];
double oscillatorDetuneAmount;
const int lengthIntervalFilter = 30;
unsigned beginningFilterInterval, currentMillis, bellowsPressureMapped;
float warbleAmount = 0;
const float BELLOWS_RELEASE_CONSTANT = .005;
const float BELLOWS_FILL_CONSTANT = .6;


void setup() {
  initializePins();
  initializeTeensyAudio();
  initializeOscillators();
  initializeMixersandFilters();
  flashRebootLights(50);
  checkForFootpedal();
  randomSeed(analogRead(FLOATINGPOINT));
}

void loop() {
  
  updateMode(); // Right Rotary Switch
  updateKnobs(); // 7 Rotary Pots
  updateSliders(); // 4 Slider Pots
  updateTranspose(); // Left Rotary Switch
  updateDroneMode(); // Left Toggle Switch
  updateEnvelopeMode(); // Right Toggle Switch
  updateKeys(); // 4 Momentary Switches
  updateIndicators(); // 4 Indicator Leds
}







