#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <Bounce.h>


// GUItool: begin automatically generated code
AudioSynthNoiseWhite     voice4n;         //xy=164.5,960.75
AudioSynthWaveform       voice4b;      //xy=165.75,916.75
AudioSynthWaveform       voice4a;      //xy=166,875.5
AudioSynthWaveform       voice3b;      //xy=168,737.25
AudioSynthWaveform       voice3a;      //xy=168.5,695.5
AudioSynthNoiseWhite     voice3n;         //xy=169,779.75
AudioSynthWaveform       voice1a;        //xy=171.00000381469727,338.6666564941406
AudioSynthNoiseWhite     voice2n;         //xy=170.75,592.5
AudioSynthNoiseWhite     voice1n;        //xy=171.5,414.4166564941406
AudioSynthWaveform       voice2b;      //xy=171.5,555
AudioSynthWaveform       voice1b;        //xy=172.25000381469727,375.4166564941406
AudioSynthWaveform       voice2a;      //xy=172,515.5000057220459
AudioSynthWaveformDc     voice4filterenv;            //xy=304,1002
AudioSynthWaveformDc     voice2filterenv;            //xy=309,638
AudioSynthWaveformDc     voice3filterenv;            //xy=310,823.0000057220459
AudioSynthWaveformDc     voice4env;            //xy=317,955
AudioMixer4              voice4mix;         //xy=317.25,896.5
AudioSynthWaveformDc     voice1env;      //xy=320.00000381469727,416.66665840148926
AudioMixer4              voice1mix;      //xy=320.25,360.4166564941406
AudioSynthWaveformDc     voice1filterenv;            //xy=320,463
AudioMixer4              voice2mix;         //xy=320.25,535.5
AudioSynthWaveformDc     voice2env;            //xy=320.5,595.25
AudioMixer4              voice3mix;         //xy=320.5,720.25
AudioSynthWaveformDc     voice3env;            //xy=321.75,780.25
AudioEffectMultiply      voice4multiply;      //xy=475.25,917.25
AudioEffectMultiply      voice2multiply;      //xy=493.75,558.25
AudioEffectMultiply      voice1multiply; //xy=495.25,388.4166564941406
AudioEffectMultiply      voice3multiply;      //xy=497,737.75
AudioFilterStateVariable voice1filter;        //xy=658,390
AudioFilterStateVariable voice3filter;        //xy=661,763.0000057220459
AudioFilterStateVariable voice4filter;        //xy=661,922
AudioFilterStateVariable voice2filter;        //xy=665,575
AudioMixer4              mastermix;         //xy=864,663.75
AudioOutputI2S           i2s1;           //xy=1044.5,668.9166870117188
AudioConnection          patchCord1(voice4n, 0, voice4mix, 2);
AudioConnection          patchCord2(voice4b, 0, voice4mix, 1);
AudioConnection          patchCord3(voice4a, 0, voice4mix, 0);
AudioConnection          patchCord4(voice3b, 0, voice3mix, 1);
AudioConnection          patchCord5(voice3a, 0, voice3mix, 0);
AudioConnection          patchCord6(voice3n, 0, voice3mix, 2);
AudioConnection          patchCord7(voice1a, 0, voice1mix, 0);
AudioConnection          patchCord8(voice2n, 0, voice2mix, 2);
AudioConnection          patchCord9(voice1n, 0, voice1mix, 2);
AudioConnection          patchCord10(voice2b, 0, voice2mix, 1);
AudioConnection          patchCord11(voice1b, 0, voice1mix, 1);
AudioConnection          patchCord12(voice2a, 0, voice2mix, 0);
AudioConnection          patchCord13(voice4filterenv, 0, voice4filter, 1);
AudioConnection          patchCord14(voice2filterenv, 0, voice2filter, 1);
AudioConnection          patchCord15(voice3filterenv, 0, voice3filter, 1);
AudioConnection          patchCord16(voice4env, 0, voice4multiply, 1);
AudioConnection          patchCord17(voice4mix, 0, voice4multiply, 0);
AudioConnection          patchCord18(voice1env, 0, voice1multiply, 1);
AudioConnection          patchCord19(voice1mix, 0, voice1multiply, 0);
AudioConnection          patchCord20(voice1filterenv, 0, voice1filter, 1);
AudioConnection          patchCord21(voice2mix, 0, voice2multiply, 0);
AudioConnection          patchCord22(voice2env, 0, voice2multiply, 1);
AudioConnection          patchCord23(voice3mix, 0, voice3multiply, 0);
AudioConnection          patchCord24(voice3env, 0, voice3multiply, 1);
AudioConnection          patchCord25(voice4multiply, 0, voice4filter, 0);
AudioConnection          patchCord26(voice2multiply, 0, voice2filter, 0);
AudioConnection          patchCord27(voice1multiply, 0, voice1filter, 0);
AudioConnection          patchCord28(voice3multiply, 0, voice3filter, 0);
AudioConnection          patchCord29(voice1filter, 0, mastermix, 0);
AudioConnection          patchCord30(voice3filter, 0, mastermix, 2);
AudioConnection          patchCord31(voice4filter, 0, mastermix, 3);
AudioConnection          patchCord32(voice2filter, 0, mastermix, 1);
AudioConnection          patchCord33(mastermix, 0, i2s1, 0);
AudioControlSGTL5000     sgtl5000_1;     //xy=1039.5,613.6666870117188
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
const int SWITCHLEFTBOTTOM = 30;
const int SWITCHLEFTMIDDLE = 29;
const int SWITCHLEFTTOP = 7;
const int SWITCHRIGHTBOTTOM = 28;
const int SWITCHRIGHTMIDDLE = 27;
const int SWITCHRIGHTTOP = 26;
int knob1, knob2, knob3, knob4, knob5, knob6, knob7;



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
const int tonebank[6][2] = {  
   {WAVEFORM_SINE, WAVEFORM_SINE},
   {WAVEFORM_TRIANGLE, WAVEFORM_SAWTOOTH},
   {WAVEFORM_TRIANGLE, WAVEFORM_SAWTOOTH_REVERSE},
   {WAVEFORM_SQUARE, WAVEFORM_SQUARE},
   {WAVEFORM_SAWTOOTH, WAVEFORM_SQUARE},
   {WAVEFORM_SQUARE, WAVEFORM_SAWTOOTH_REVERSE} 
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



void setup() {
  initializePins();
  flashRebootLights(60);

  initializeTeensyAudio();
  initializeOscillators();
  initializeMixers();
}

void loop() {
  updateKnobs(); // 7 Rotary Pots
  updateSliders(); // 4 Slider Pots
  updateTranspose(); // Left Rotary Switch
  updateTonebank(); // Right Rotary Switch
  updateDroneMode(); // Left Toggle Switch
  updateEnvelopeMode(); // Right Toggle Switch
  updateKeys(); // 4 Momentary Switches
}







