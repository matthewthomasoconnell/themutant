#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <Bounce.h>



// GUItool: begin automatically generated code
AudioSynthWaveform       voice1b;        //xy=1007.8889389038086,1104.6666831970215
AudioSynthNoiseWhite     voice1n;        //xy=1010.8889389038086,1148.6666831970215
AudioSynthWaveform       voice1a;        //xy=1012.8889389038086,1061.6666831970215
AudioMixer4              voice1mix;      //xy=1152.8889389038086,1124.6666831970215
AudioSynthWaveformDc     voice1env;      //xy=1153.8889389038086,1189.6666831970215
AudioEffectMultiply      voice1multiply; //xy=1327.999984741211,1152.6666584014893
AudioOutputI2S           i2s1;           //xy=1560.5556983947754,1152.888910293579
AudioConnection          patchCord1(voice1b, 0, voice1mix, 1);
AudioConnection          patchCord2(voice1n, 0, voice1mix, 2);
AudioConnection          patchCord3(voice1a, 0, voice1mix, 0);
AudioConnection          patchCord4(voice1mix, 0, voice1multiply, 0);
AudioConnection          patchCord5(voice1env, 0, voice1multiply, 1);
AudioConnection          patchCord6(voice1multiply, 0, i2s1, 0);
AudioControlSGTL5000     sgtl5000_1;     //xy=1002.0000457763672,1330.7776145935059
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







int attackTime = 5000;
int decayTime = 1000;
float sustainLevel = 1;
int releaseTime = 5000;
bool noteTrigFlag[4];
unsigned long attackWait[4];


void setup() {

  AudioMemory(160);
  Serial.begin(115200);
  sgtl5000_1.enable();
  sgtl5000_1.volume(.8);
  
  initializePins();
  flashRebootLights(60);

  initalizeOscillators();
  initializeMixers();

  
  


}

void loop() {
  for(int i=0; i<4; i++){
    btnState[i] = digitalRead(notePins[i]);
    if (noteBounce[i].update()){
      if(i == 0){
        if (btnState[i] == LOW && prevBtnState[i] == HIGH){
          voice1env.amplitude(1,attackTime);
          noteTrigFlag[i] = true;
          attackWait[i] = millis();
        }else{
          noteTrigFlag[i] = false;
          voice1env.amplitude(0,releaseTime);
        }
      }
    }
    prevBtnState[i] = btnState[i];
  }





}
