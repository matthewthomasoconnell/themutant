#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <Bounce.h>

// GUItool: begin automatically generated code
AudioSynthNoiseWhite     voice4n;         //xy=161.5,813.75
AudioSynthWaveform       voice3b;      //xy=163,636.25
AudioSynthWaveform       voice4b;      //xy=162.75,769.75
AudioSynthWaveform       voice3a;      //xy=163.5,594.5
AudioSynthWaveform       voice4a;      //xy=163,728.5
AudioSynthNoiseWhite     voice3n;         //xy=164,678.75
AudioSynthNoiseWhite     voice2n;         //xy=168.75,539.5
AudioSynthWaveform       voice2b;      //xy=169.5,502
AudioSynthWaveform       voice2a;      //xy=170,462.5000057220459
AudioSynthWaveform       voice1a;        //xy=171.00000381469727,338.6666564941406
AudioSynthNoiseWhite     voice1n;        //xy=171.5,414.4166564941406
AudioSynthWaveform       voice1b;        //xy=172.25000381469727,375.4166564941406
AudioSynthWaveformDc     voice4env;            //xy=314,808
AudioMixer4              voice4mix;         //xy=314.25,749.5
AudioMixer4              voice3mix;         //xy=315.5,619.25
AudioSynthWaveformDc     voice3env;            //xy=316.75,679.25
AudioMixer4              voice2mix;         //xy=318.25,482.5
AudioSynthWaveformDc     voice2env;            //xy=318.5,542.25
AudioSynthWaveformDc     voice1env;      //xy=320.00000381469727,416.66665840148926
AudioMixer4              voice1mix;      //xy=320.25,360.4166564941406
AudioEffectMultiply      voice4multiply;      //xy=472.25,770.25
AudioEffectMultiply      voice3multiply;      //xy=492,636.75
AudioEffectMultiply      voice1multiply; //xy=495.25,388.4166564941406
AudioEffectMultiply      voice2multiply;      //xy=498.75,509.25
AudioMixer4              mastermix;         //xy=796,587.75
AudioOutputI2S           i2s1;           //xy=967.5,585.9166870117188
AudioConnection          patchCord1(voice4n, 0, voice4mix, 2);
AudioConnection          patchCord2(voice3b, 0, voice3mix, 1);
AudioConnection          patchCord3(voice4b, 0, voice4mix, 1);
AudioConnection          patchCord4(voice3a, 0, voice3mix, 0);
AudioConnection          patchCord5(voice4a, 0, voice4mix, 0);
AudioConnection          patchCord6(voice3n, 0, voice3mix, 2);
AudioConnection          patchCord7(voice2n, 0, voice2mix, 2);
AudioConnection          patchCord8(voice2b, 0, voice2mix, 1);
AudioConnection          patchCord9(voice2a, 0, voice2mix, 0);
AudioConnection          patchCord10(voice1a, 0, voice1mix, 0);
AudioConnection          patchCord11(voice1n, 0, voice1mix, 2);
AudioConnection          patchCord12(voice1b, 0, voice1mix, 1);
AudioConnection          patchCord13(voice4env, 0, voice4multiply, 1);
AudioConnection          patchCord14(voice4mix, 0, voice4multiply, 0);
AudioConnection          patchCord15(voice3mix, 0, voice3multiply, 0);
AudioConnection          patchCord16(voice3env, 0, voice3multiply, 1);
AudioConnection          patchCord17(voice2mix, 0, voice2multiply, 0);
AudioConnection          patchCord18(voice2env, 0, voice2multiply, 1);
AudioConnection          patchCord19(voice1env, 0, voice1multiply, 1);
AudioConnection          patchCord20(voice1mix, 0, voice1multiply, 0);
AudioConnection          patchCord21(voice4multiply, 0, mastermix, 3);
AudioConnection          patchCord22(voice3multiply, 0, mastermix, 2);
AudioConnection          patchCord23(voice1multiply, 0, mastermix, 0);
AudioConnection          patchCord24(voice2multiply, 0, mastermix, 1);
AudioConnection          patchCord25(mastermix, 0, i2s1, 0);
AudioControlSGTL5000     sgtl5000_1;     //xy=798.5,450.6666946411133
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




//Oscillator Intervals and Ranges
int oscillator_octave = 2;
int oscillator_range = 5;
int oscillator_interval = 5; // in half steps (5 => 4ths, 7 => 5ths)
int slider1, slider2, slider3, slider4;




// Initialize the Tonebank variables
int tonebank[6][2] = {  
   {WAVEFORM_SINE, WAVEFORM_SINE},
   {WAVEFORM_TRIANGLE, WAVEFORM_TRIANGLE},
   {WAVEFORM_SAWTOOTH_REVERSE, WAVEFORM_SAWTOOTH_REVERSE},
   {WAVEFORM_SAWTOOTH, WAVEFORM_SAWTOOTH},
   {WAVEFORM_PULSE, WAVEFORM_PULSE},
   {WAVEFORM_SQUARE, WAVEFORM_SQUARE} 
};
int oldTonebankNumber, tonebankNumber;


// Initialize Scales and Waveforms
// C C# D D# E F F# G G# A A# B
const float scales[12] ={16.35, 17.32, 18.35, 19.45, 20.60, 21.83, 23.12, 24.50, 25.96, 27.50, 29.14, 30.87};
int oldScale = scales[0];







int attackTime = 1000;
int decayTime = 1000;
float sustainLevel = 1;
int releaseTime = 4000;
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



  updateSliders();


  // TONEBANK ROTARY CHECK
  if( toneBankLastChecked == 0 ) {
    toneBankLastChecked = millis() + ROTARY_REFRESH_RATE;
  }
  if( millis() - toneBankLastChecked > ROTARY_REFRESH_RATE ) {

    // We are returning 4,5,6,7,8,9 from the rotary switch, so just subtract 4 from each result to get 0 - 5
    tonebankNumber = rotaryTurned(TONEBANK_ROTARY_PIN) - 4;

    int voiceaWaveform = tonebank[tonebankNumber][0];
    int voicebWaveform = tonebank[tonebankNumber][1];
    

    if ( oldTonebankNumber != tonebankNumber ) {

      Serial.println(tonebankNumber);

      voice1a.begin( voiceaWaveform );
      voice2a.begin( voiceaWaveform );
      voice3a.begin( voiceaWaveform );
      voice4a.begin( voiceaWaveform );
      
      voice1b.begin( voicebWaveform );
      voice2b.begin( voicebWaveform );
      voice3b.begin( voicebWaveform );
      voice4b.begin( voicebWaveform );
    }

    oldTonebankNumber = tonebankNumber;

    toneBankLastChecked = millis();
  }

  


  // Play / Stop Note Loop
  for(int i=0; i<4; i++){
    btnState[i] = digitalRead(notePins[i]);
    if (noteBounce[i].update()){
        if (btnState[i] == LOW && prevBtnState[i] == HIGH){
          startNote(i);
        }else {
          stopNote(i);
        }
    }
    prevBtnState[i] = btnState[i];
  }





}
