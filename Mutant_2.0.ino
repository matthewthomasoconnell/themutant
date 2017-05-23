#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SerialFlash.h>
#include <Bounce.h>


// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=72,105
AudioSynthWaveform       waveform3;      //xy=72,173
AudioSynthWaveform       waveform4;      //xy=72,208
AudioSynthNoiseWhite     noise4;         //xy=71,564
AudioSynthWaveform       waveform2;      //xy=73,139
AudioSynthNoiseWhite     noise3;         //xy=72,528
AudioSynthNoiseWhite     noise2;         //xy=74,488
AudioSynthNoiseWhite     noise1;         //xy=76,448
AudioSynthWaveform       waveform7;      //xy=84,354
AudioSynthWaveform       waveform8;      //xy=85,403
AudioSynthWaveform       waveform5;      //xy=86,261
AudioSynthWaveform       waveform6;      //xy=86,307
AudioEffectEnvelope      envelope10;     //xy=287,487
AudioEffectEnvelope      envelope9;      //xy=288,445
AudioEffectEnvelope      envelope11;     //xy=288,526
AudioEffectEnvelope      envelope12;     //xy=291,575
AudioEffectEnvelope      envelope3;      //xy=293,165
AudioEffectEnvelope      envelope1;      //xy=294,96
AudioEffectEnvelope      envelope2;      //xy=294,131
AudioEffectEnvelope      envelope8;      //xy=293,394
AudioEffectEnvelope      envelope4;      //xy=295,200
AudioEffectEnvelope      envelope7;      //xy=296,346
AudioEffectEnvelope      envelope6;      //xy=300,302
AudioEffectEnvelope      envelope5;      //xy=303,253
AudioMixer4              mixer1;         //xy=510,152
AudioMixer4              mixer4;         //xy=509,496
AudioMixer4              mixer2;         //xy=527,328
AudioMixer4              mixer3;         //xy=692,230
AudioFilterStateVariable filter1;        //xy=912,237
AudioSynthWaveformSine   sine1;          //xy=920,471
AudioOutputI2S           i2s1;           //xy=1147,177
AudioConnection          patchCord1(waveform1, envelope1);
AudioConnection          patchCord2(waveform3, envelope3);
AudioConnection          patchCord3(waveform4, envelope4);
AudioConnection          patchCord4(noise4, envelope12);
AudioConnection          patchCord5(waveform2, envelope2);
AudioConnection          patchCord6(noise3, envelope11);
AudioConnection          patchCord7(noise2, envelope10);
AudioConnection          patchCord8(noise1, envelope9);
AudioConnection          patchCord9(waveform7, envelope7);
AudioConnection          patchCord10(waveform8, envelope8);
AudioConnection          patchCord11(waveform5, envelope5);
AudioConnection          patchCord12(waveform6, envelope6);
AudioConnection          patchCord13(envelope10, 0, mixer4, 1);
AudioConnection          patchCord14(envelope9, 0, mixer4, 0);
AudioConnection          patchCord15(envelope11, 0, mixer4, 2);
AudioConnection          patchCord16(envelope12, 0, mixer4, 3);
AudioConnection          patchCord17(envelope3, 0, mixer1, 2);
AudioConnection          patchCord18(envelope1, 0, mixer1, 0);
AudioConnection          patchCord19(envelope2, 0, mixer1, 1);
AudioConnection          patchCord20(envelope8, 0, mixer2, 3);
AudioConnection          patchCord21(envelope4, 0, mixer1, 3);
AudioConnection          patchCord22(envelope7, 0, mixer2, 2);
AudioConnection          patchCord23(envelope6, 0, mixer2, 1);
AudioConnection          patchCord24(envelope5, 0, mixer2, 0);
AudioConnection          patchCord25(mixer1, 0, mixer3, 0);
AudioConnection          patchCord26(mixer4, 0, mixer3, 2);
AudioConnection          patchCord27(mixer2, 0, mixer3, 1);
AudioConnection          patchCord28(mixer3, 0, filter1, 0);
AudioConnection          patchCord29(filter1, 0, i2s1, 0);
AudioConnection          patchCord30(filter1, 0, i2s1, 1);
AudioConnection          patchCord31(sine1, 0, filter1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=64.5,750
// GUItool: end automatically generated code

// Initialize Buttons
int notePins[4] = {0,1,24,25};
int btnState[4];
int prevBtnState[4];
int indicatorLeds[4] = {6,2,8,4};
Bounce noteBounce[] = {
  Bounce(notePins[0],10),
  Bounce(notePins[1],10),
  Bounce(notePins[2],10),
  Bounce(notePins[3],10)
};


// Initializae Rotary Switches
const int ROTARY_REFRESH_RATE = 50;
const int TONEBANK_ROTARY_PIN = A17;
const int TRANSPOSE_ROTARY_PIN = A16;
long toneBankLastChecked = 0;
long transposeLastChecked = 0;
int newScale;


// Initialize the Tonebank variables
int tonebank[6] ={WAVEFORM_SINE,WAVEFORM_TRIANGLE,WAVEFORM_SAWTOOTH_REVERSE,WAVEFORM_SAWTOOTH,WAVEFORM_SQUARE,WAVEFORM_PULSE};
int oldWaveform = tonebank[0];

// Initialize Scales and Waveforms
// C C# D D# E F F# G G# A A# B
const float scales[12] ={16.35, 17.32, 18.35, 19.45, 20.60, 21.83, 23.12, 24.50, 25.96, 27.50, 29.14, 30.87};
int oldScale = scales[0];



void setup() {

  AudioMemory(160);
  Serial.begin(115200);
  sgtl5000_1.enable();
  sgtl5000_1.volume(.8);
  
  initializePins();
  flashRebootLights(50);

  initalizeOscillators();
  initializeMixers();

}

void loop() {
  // put your main code here, to run repeatedly:

}
