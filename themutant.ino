#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <Bounce.h>

// GUItool: begin automatically generated code
AudioSynthNoiseWhite     voice4n;        //xy=248.75,720.75
AudioSynthWaveform       voice4b;        //xy=249.75,676.75
AudioSynthWaveform       voice4a;        //xy=250.75,635.75
AudioSynthWaveform       voice3a;        //xy=252.75,455.75
AudioSynthWaveform       voice3b;        //xy=252.75,497.75
AudioSynthNoiseWhite     voice3n;        //xy=253.75,539.75
AudioSynthWaveform       voice1a;        //xy=255.75,98.75
AudioSynthNoiseWhite     voice2n;        //xy=254.75,352.75
AudioSynthNoiseWhite     voice1n;        //xy=255.75,174.75
AudioSynthWaveform       voice2b;        //xy=255.75,315.75
AudioSynthWaveform       voice1b;        //xy=256.75,135.75
AudioSynthWaveform       voice2a;        //xy=256.75,275.75
AudioSynthWaveformDc     voice4env;      //xy=401.75,715.75
AudioMixer4              voice1mix;      //xy=404.75,120.75
AudioSynthWaveformDc     voice1env;      //xy=404.75,176.75
AudioMixer4              voice2mix;      //xy=404.75,295.75
AudioSynthWaveformDc     voice2env;      //xy=404.75,355.75
AudioMixer4              voice4mix;      //xy=403.75,656.75
AudioMixer4              voice3mix;      //xy=404.75,480.75
AudioSynthWaveformDc     voice3env;      //xy=405.75,540.75
AudioEffectMultiply      voice4multiply; //xy=559.75,677.75
AudioEffectMultiply      voice1multiply; //xy=577.75,130.75
AudioEffectMultiply      voice2multiply; //xy=577.75,318.75
AudioEffectMultiply      voice3multiply; //xy=581.75,497.75
AudioMixer4              mastermix;      //xy=794.75,431.75
AudioFilterStateVariable masterFilter;        //xy=970.0000152587891,435.0000057220459
AudioOutputI2S           i2s1;           //xy=1157.500015258789,440.2500057220459
AudioConnection          patchCord1(voice4n, 0, voice4mix, 2);
AudioConnection          patchCord2(voice4b, 0, voice4mix, 1);
AudioConnection          patchCord3(voice4a, 0, voice4mix, 0);
AudioConnection          patchCord4(voice3a, 0, voice3mix, 0);
AudioConnection          patchCord5(voice3b, 0, voice3mix, 1);
AudioConnection          patchCord6(voice3n, 0, voice3mix, 2);
AudioConnection          patchCord7(voice1a, 0, voice1mix, 0);
AudioConnection          patchCord8(voice2n, 0, voice2mix, 2);
AudioConnection          patchCord9(voice1n, 0, voice1mix, 2);
AudioConnection          patchCord10(voice2b, 0, voice2mix, 1);
AudioConnection          patchCord11(voice1b, 0, voice1mix, 1);
AudioConnection          patchCord12(voice2a, 0, voice2mix, 0);
AudioConnection          patchCord13(voice4env, 0, voice4multiply, 1);
AudioConnection          patchCord14(voice1mix, 0, voice1multiply, 0);
AudioConnection          patchCord15(voice1env, 0, voice1multiply, 1);
AudioConnection          patchCord16(voice2mix, 0, voice2multiply, 0);
AudioConnection          patchCord17(voice2env, 0, voice2multiply, 1);
AudioConnection          patchCord18(voice4mix, 0, voice4multiply, 0);
AudioConnection          patchCord19(voice3mix, 0, voice3multiply, 0);
AudioConnection          patchCord20(voice3env, 0, voice3multiply, 1);
AudioConnection          patchCord21(voice4multiply, 0, mastermix, 3);
AudioConnection          patchCord22(voice1multiply, 0, mastermix, 0);
AudioConnection          patchCord23(voice2multiply, 0, mastermix, 1);
AudioConnection          patchCord24(voice3multiply, 0, mastermix, 2);
AudioConnection          patchCord25(mastermix, 0, masterFilter, 0);
AudioConnection          patchCord26(masterFilter, 0, i2s1, 0);
AudioControlSGTL5000     sgtl5000_1;     //xy=1147.500015258789,398.2500057220459
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
int knob1, knob2, knob3, knob4, knob5, knob6, knob7, footpedal;




// Initialize Buttons and Note Pins
const int notePins[4] = {0,1,24,25};
const int indicatorLeds[4] = {6,2,8,4};
int btnState[4], prevBtnState[4];
// Initialize Buttons
Bounce noteBounce[] = {
  Bounce(notePins[0],10),
  Bounce(notePins[1],10),
  Bounce(notePins[2],10),
  Bounce(notePins[3],10)
};

// Effects Constants
const int TREMOLO = 0;
const int WARBLE = 1;
const int DELAY = 2;
const int BELLOWS = 3;

// Initialize Rotary Switches
const int ROTARY_REFRESH_RATE = 50;
const int TONEBANK_ROTARY_PIN = A17;
const int TRANSPOSE_ROTARY_PIN = A16;
long toneBankLastChecked = 0;
long transposeLastChecked = 0;
int newScale;

//Oscillator Intervals and Ranges
int oscillator_octave = 2;
int oscillator_range = 5;
int oscillator_interval = 5; // in half steps (5 => 4ths, 7 => 5ths)
int slider1, slider2, slider3, slider4;

// Initialize the Tonebank variables
// I'd like to put volume, octave, and other variables in here for more consistency
const int tonebank[6][3] = {  
   {WAVEFORM_SQUARE, WAVEFORM_SQUARE, TREMOLO},
   {WAVEFORM_TRIANGLE, WAVEFORM_SAWTOOTH, WARBLE},
   {WAVEFORM_TRIANGLE, WAVEFORM_SAWTOOTH_REVERSE, TREMOLO},
   {WAVEFORM_SQUARE, WAVEFORM_SQUARE, BELLOWS},
   {WAVEFORM_SAWTOOTH, WAVEFORM_SQUARE, WARBLE},
   {WAVEFORM_SQUARE, WAVEFORM_SAWTOOTH_REVERSE, DELAY} 
};
int oldTonebankNumber, tonebankNumber, voiceaWaveform, voicebWaveform;

// Initialize Scales and Waveforms
// C C# D D# E F F# G G# A A# B
const float scales[12] ={16.35, 17.32, 18.35, 19.45, 20.60, 21.83, 23.12, 24.50, 25.96, 27.50, 29.14, 30.87};
int oldScale = scales[0];

// Initialize Envelope
int droneMode;
int attackTime, decayTime, releaseTime;
float sustainLevel;
bool noteTrigFlag[4];
unsigned long attackWait[4];
int oldNoiseLevel, oldFilterFrequency;
float oscillatorDetuneAmount;



void setup() {
  initializePins();
  flashRebootLights(60);

  initializeTeensyAudio();
  initializeOscillators();
  initializeMixersandFilters();
}

void loop() {
  
  updateKnobs(); // 7 Rotary Pots
  updateSliders(); // 4 Slider Pots
  updateTranspose(); // Left Rotary Switch
  updateTonebank(); // Right Rotary Switch
  updateDroneMode(); // Left Toggle Switch
  updateEnvelopeMode(); // Right Toggle Switch
  updateKeys(); // 4 Momentary Switches
  updateIndicators(); // 4 Indicator Leds
}







