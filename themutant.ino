#include <Audio.h>
#include <Wire.h>
#include <Bounce.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>


// GUItool: begin automatically generated code
AudioSynthWaveform       shapeLFO;       //xy=461.6666564941406,884.9999389648438
AudioSynthWaveform       masterLFO;      //xy=461.6666564941406,934.9999389648438
AudioSynthWaveformModulated voice1b;        //xy=682.6666564941406,686.9999389648438
AudioSynthWaveformModulated voice4b;        //xy=680.6666564941406,1237.9999389648438
AudioSynthWaveformModulated voice2b;        //xy=682.6666564941406,843.9999389648438
AudioSynthWaveformModulated voice3b;        //xy=683.6666564941406,1015.9999389648438
AudioSynthNoiseWhite     voice2n;        //xy=706.6666564941406,881.9999389648438
AudioSynthWaveform       voice1a;        //xy=707.6666564941406,647.9999389648438
AudioSynthWaveform       voice3a;        //xy=706.6666564941406,973.9999389648438
AudioSynthNoiseWhite     voice1n;        //xy=707.6666564941406,723.9999389648438
AudioSynthNoiseWhite     voice4n;        //xy=706.6666564941406,1278.9999389648438
AudioSynthWaveform       voice2a;        //xy=708.6666564941406,804.9999389648438
AudioSynthNoiseWhite     voice3n;        //xy=707.6666564941406,1057.9999389648438
AudioSynthWaveform       voice4a;        //xy=708.6666564941406,1193.9999389648438
AudioMixer4              voice1mix;      //xy=856.6666564941406,669.9999389648438
AudioSynthWaveformDc     voice1env;      //xy=856.6666564941406,725.9999389648438
AudioMixer4              voice2mix;      //xy=856.6666564941406,824.9999389648438
AudioSynthWaveformDc     voice2env;      //xy=856.6666564941406,884.9999389648438
AudioMixer4              voice3mix;      //xy=858.6666564941406,998.9999389648438
AudioSynthWaveformDc     voice3env;      //xy=859.6666564941406,1058.9999389648438
AudioSynthWaveformDc     voice4env;      //xy=859.6666564941406,1273.9999389648438
AudioMixer4              voice4mix;      //xy=861.6666564941406,1214.9999389648438
AudioEffectMultiply      voice4multiply; //xy=1048.6666564941406,1244.9999389648438
AudioSynthWaveformDc     voice4filterenv; //xy=1050.6666564941406,1278.9999389648438
AudioEffectMultiply      voice3multiply; //xy=1055.6666564941406,1042.9999389648438
AudioSynthWaveformDc     voice3filterenv; //xy=1058.6666564941406,1076.9999389648438
AudioMixer4              voice3filterModMixer; //xy=1060.6666564941406,1130.9999389648438
AudioMixer4              voice4filterModMixer; //xy=1061.6666564941406,1328.9999389648438
AudioEffectMultiply      voice1multiply; //xy=1067.6666564941406,667.9999389648438
AudioSynthWaveformDc     voice1filterenv; //xy=1068.6666564941406,704.9999389648438
AudioMixer4              voice1filterModMixer; //xy=1069.6666564941406,758.9999389648438
AudioEffectMultiply      voice2multiply; //xy=1070.6666564941406,863.9999389648438
AudioSynthWaveformDc     voice2filterenv; //xy=1072.6666564941406,901.9999389648438
AudioMixer4              voice2filterModMixer; //xy=1077.6666564941406,954.9999389648438
AudioFilterStateVariable voice1filter;   //xy=1316.6666564941406,698.9999389648438
AudioFilterStateVariable voice2filter;   //xy=1321.6666564941406,866.9999389648438
AudioFilterStateVariable voice3filter;   //xy=1324.6666564941406,1043.9999389648438
AudioFilterStateVariable voice4filter;   //xy=1327.6666564941406,1213.9999389648438
AudioMixer4              oscillatorMixer; //xy=1535.6666564941406,709.9999389648438
AudioOutputI2S           i2s1;           //xy=1557.6666564941406,769.9999389648438
AudioConnection          patchCord1(shapeLFO, 0, voice1b, 1);
AudioConnection          patchCord2(shapeLFO, 0, voice2b, 1);
AudioConnection          patchCord3(shapeLFO, 0, voice3b, 1);
AudioConnection          patchCord4(shapeLFO, 0, voice4b, 1);
AudioConnection          patchCord5(masterLFO, 0, voice1filterModMixer, 1);
AudioConnection          patchCord6(masterLFO, 0, voice2filterModMixer, 1);
AudioConnection          patchCord7(masterLFO, 0, voice3filterModMixer, 1);
AudioConnection          patchCord8(masterLFO, 0, voice4filterModMixer, 1);
AudioConnection          patchCord9(masterLFO, 0, voice1b, 0);
AudioConnection          patchCord10(masterLFO, 0, voice2b, 0);
AudioConnection          patchCord11(masterLFO, 0, voice3b, 0);
AudioConnection          patchCord12(masterLFO, 0, voice4b, 0);
AudioConnection          patchCord13(voice1b, 0, voice1mix, 1);
AudioConnection          patchCord14(voice4b, 0, voice4mix, 1);
AudioConnection          patchCord15(voice2b, 0, voice2mix, 1);
AudioConnection          patchCord16(voice3b, 0, voice3mix, 1);
AudioConnection          patchCord17(voice2n, 0, voice2mix, 2);
AudioConnection          patchCord18(voice1a, 0, voice1mix, 0);
AudioConnection          patchCord19(voice3a, 0, voice3mix, 0);
AudioConnection          patchCord20(voice1n, 0, voice1mix, 2);
AudioConnection          patchCord21(voice4n, 0, voice4mix, 2);
AudioConnection          patchCord22(voice2a, 0, voice2mix, 0);
AudioConnection          patchCord23(voice3n, 0, voice3mix, 2);
AudioConnection          patchCord24(voice4a, 0, voice4mix, 0);
AudioConnection          patchCord25(voice1mix, 0, voice1multiply, 0);
AudioConnection          patchCord26(voice1env, 0, voice1multiply, 1);
AudioConnection          patchCord27(voice2mix, 0, voice2multiply, 0);
AudioConnection          patchCord28(voice2env, 0, voice2multiply, 1);
AudioConnection          patchCord29(voice3mix, 0, voice3multiply, 0);
AudioConnection          patchCord30(voice3env, 0, voice3multiply, 1);
AudioConnection          patchCord31(voice4env, 0, voice4multiply, 1);
AudioConnection          patchCord32(voice4mix, 0, voice4multiply, 0);
AudioConnection          patchCord33(voice4multiply, 0, voice4filter, 0);
AudioConnection          patchCord34(voice4filterenv, 0, voice4filterModMixer, 0);
AudioConnection          patchCord35(voice3multiply, 0, voice3filter, 0);
AudioConnection          patchCord36(voice3filterenv, 0, voice3filterModMixer, 0);
AudioConnection          patchCord37(voice3filterModMixer, 0, voice3filter, 1);
AudioConnection          patchCord38(voice4filterModMixer, 0, voice4filter, 1);
AudioConnection          patchCord39(voice1multiply, 0, voice1filter, 0);
AudioConnection          patchCord40(voice1filterenv, 0, voice1filterModMixer, 0);
AudioConnection          patchCord41(voice1filterModMixer, 0, voice1filter, 1);
AudioConnection          patchCord42(voice2multiply, 0, voice2filter, 0);
AudioConnection          patchCord43(voice2filterenv, 0, voice2filterModMixer, 0);
AudioConnection          patchCord44(voice2filterModMixer, 0, voice2filter, 1);
AudioConnection          patchCord45(voice1filter, 0, oscillatorMixer, 0);
AudioConnection          patchCord46(voice2filter, 0, oscillatorMixer, 1);
AudioConnection          patchCord47(voice3filter, 0, oscillatorMixer, 2);
AudioConnection          patchCord48(voice4filter, 0, oscillatorMixer, 3);
AudioConnection          patchCord49(oscillatorMixer, 0, i2s1, 0);
AudioConnection          patchCord50(oscillatorMixer, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=1548.6666564941406,813.9999389648438
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
long randomNotePlayInterval[4] = {random(5000, 13000),random(5000, 13000),random(5000, 13000),random(5000, 13000)};

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

// Initialize Scales and Waveforms
// C C# D D# E F F# G G# A A# B
const int midiNotes[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

// Initialize Modes
// C C# D D# E F F# G G# A A# B
// 0 1  2 3  4 5 6  7 8  9 10 11
// These modes are based off of the root C, which can be transposed later.
const int modes[6][4][2] = 
{
  {{ 0, 2 }, { 2, 4 }, { 7, 9 },{ 9, 12 }},         // Mode 1 {{1|C,2|D},{2|D,3|E},{5|G,6|A},{6|A,8|C}}  PENTATONIC A
  {{ 9, 12 }, { 12, 14 }, { 14, 16 },{ 19, 21 }},   // Mode 2 {{6|A,8|C},{1|C,2|D},{2|D,3|E},{5|G,6|A}}  PENTATONIC B
  {{ 0, 5 }, { 7, 9 }, { 9, 11 },{ 11, 12 }},       // Mode 3 {{1|C,4|F},{5|G,6|A},{6|A,7|B},{7|B,8|C}}  ALTERNATIVE
  {{ 7, 9 }, { 12, 14 }, { 14, 16 },{ 19, 21 }},    // Mode 4 {{5|G,6|A},{1|C,2|D},{2|D,3|E},{5|G,6|A}}  STILL LIFE
  {{ 5, 7 }, { 12, 14 }, { 16, 17 },{ 19, 21 }},    // Mode 5 {{4|F,5|G},{1|C,2|D},{3|E,4|F},{5|G,6|A}}  SURFER
  {{ 0, 7 }, { 7, 12 }, { 0, 5 },{ 5, 12 }}       // Mode 6 {{1|C,5|G},{5|G,8|C},{1|C,4|F},{4|F,8|C}}  TAMBOURA
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
