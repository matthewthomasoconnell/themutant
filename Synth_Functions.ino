void initializePins() {
  // INDICATOR LEDS
  pinMode(indicatorLeds[0], OUTPUT);
  pinMode(indicatorLeds[1], OUTPUT);
  pinMode(indicatorLeds[2], OUTPUT);
  pinMode(indicatorLeds[3], OUTPUT);

  // NOTE BUTTONS
  pinMode(notePins[0], INPUT_PULLUP);
  pinMode(notePins[1], INPUT_PULLUP);
  pinMode(notePins[2], INPUT_PULLUP);
  pinMode(notePins[3], INPUT_PULLUP);

  // TOGGLE SWITCHES
  pinMode(7, INPUT_PULLUP);
  pinMode(29, INPUT_PULLUP);
  pinMode(30, INPUT_PULLUP);
  pinMode(26, INPUT_PULLUP);
  pinMode(27, INPUT_PULLUP);
  pinMode(28, INPUT_PULLUP);
  
}

// This goes in the setup sketch to initialize the audio board
void initializeTeensyAudio() {
  AudioMemory(160);
  Serial.begin(115200);
  sgtl5000_1.enable();
  sgtl5000_1.volume(.8);
}

void flashRebootLights(int speed) {
  // Turn off Teensy LED
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  
  int i = 0;
  while(i < 5) {
    digitalWrite(indicatorLeds[0], HIGH);
    delay(speed);
    digitalWrite(indicatorLeds[0], LOW);
    digitalWrite(indicatorLeds[1], HIGH);
    delay(speed);
    digitalWrite(indicatorLeds[1], LOW);
    digitalWrite(indicatorLeds[2], HIGH);
    delay(speed);
    digitalWrite(indicatorLeds[2], LOW);
    digitalWrite(indicatorLeds[3], HIGH);
    delay(speed);
    digitalWrite(indicatorLeds[3], LOW);
    i++;
  }
}

// Turn on the waveforms - This is arbitrary since it will be changed in the loop
void initializeOscillators() {
  voice1a.begin(.3,1,WAVEFORM_SQUARE);
  voice1b.begin(.3,1,WAVEFORM_SQUARE);

  voice2a.begin(.3,1,WAVEFORM_SQUARE);
  voice2b.begin(.3,1,WAVEFORM_SQUARE);

  voice3a.begin(.3,1,WAVEFORM_SQUARE);
  voice3b.begin(.3,1,WAVEFORM_SQUARE);

  voice4a.begin(.3,1,WAVEFORM_SQUARE);
  voice4b.begin(.3,1,WAVEFORM_SQUARE);
}

// Turn on the Mixers
void initializeMixersandFilters() {
  masterFilter.frequency(20000);
  masterFilter.resonance(1);
  
  voice1mix.gain(0,.33);
  voice1mix.gain(1,.33);
  voice1mix.gain(2,.33);

  voice2mix.gain(0,.33);
  voice2mix.gain(1,.33);
  voice2mix.gain(2,.33);

  voice3mix.gain(0,.33);
  voice3mix.gain(1,.33);
  voice3mix.gain(2,.33);

  voice4mix.gain(0,.33);
  voice4mix.gain(1,.33);
  voice4mix.gain(2,.33);

  mastermix.gain(0,.25);
  mastermix.gain(1,.25);
  mastermix.gain(2,.25);
  mastermix.gain(3,.25);
}



void startNote(int i) {
  noteTrigFlag[i] = false;

  if (i == 0) {
//    voice1filterenv.amplitude(-1, releaseTime);
    voice1env.amplitude(0,releaseTime);
  } else if (i == 1) {
//    voice2filterenv.amplitude(-1, releaseTime);
    voice2env.amplitude(0,releaseTime);
  } else if (i == 2) {
//    voice3filterenv.amplitude(-1, releaseTime);
    voice3env.amplitude(0,releaseTime);
  } else if (i == 3) {
//    voice4filterenv.amplitude(-1, releaseTime);
    voice4env.amplitude(0,releaseTime);
  }   
}

void stopNote(int i) {  
  noteTrigFlag[i] = true;
  attackWait[i] = millis();

  if (i == 0) {
//    voice1filterenv.amplitude(1,attackTime);
    voice1env.amplitude(1,attackTime);
  } else if (i == 1) {
//    voice2filterenv.amplitude(1,attackTime);
    voice2env.amplitude(1,attackTime);
  } else if (i == 2) {
//    voice3filterenv.amplitude(1,attackTime);
    voice3env.amplitude(1,attackTime);
  } else if (i == 3) {
//    voice4filterenv.amplitude(1,attackTime);
    voice4env.amplitude(1,attackTime);
  }   
}

void updateKnobs() {
  knob1 = analogRead(KNOB1);
  knob2 = analogRead(KNOB2);
  knob3 = analogRead(KNOB3);
  knob4 = analogRead(KNOB4);
  knob5 = analogRead(KNOB5);
  knob6 = analogRead(KNOB6);
  knob7 = analogRead(KNOB7);
  footpedal = analogRead(FOOTPEDAL);


  updateMasterFilter(knob1); // This is causing major glitches
  updateNoise(knob4);
  updateOscillatorRatio(knob5);
  updateOscillatorDetune(knob6, footpedal);
  
}

void updateOscillatorDetune(int knobValue, int footpedal){
  oscillatorDetuneAmount = mapfloat(knobValue, 0, 1023, -1, 1);
  float footpedalAmount = mapfloat(footpedal, 0, 1023, -.025, .025);
  
  oscillatorDetuneAmount = oscillatorDetuneAmount + footpedalAmount;

  Serial.println(oscillatorDetuneAmount);
}


void updateOscillatorRatio(int knobValue){
  float voiceaAmplitude = mapfloat(knobValue, 0, 1023, 0, 1);
  float voicebAmplitude = 1 - voiceaAmplitude;
  
  voice1a.amplitude(voiceaAmplitude);
  voice2a.amplitude(voiceaAmplitude);
  voice3a.amplitude(voiceaAmplitude);
  voice4a.amplitude(voiceaAmplitude);

  voice1b.amplitude(voicebAmplitude);
  voice2b.amplitude(voicebAmplitude);
  voice3b.amplitude(voicebAmplitude);
  voice4b.amplitude(voicebAmplitude);
}


void updateNoise(int noiseLevel) {
  if (noiseLevel != oldNoiseLevel) {
    float noiseLevelMapped = mapfloat(noiseLevel, 0, 1023, 0, .5);
    
//    Serial.println(noiseLevelMapped);
  
    voice1n.amplitude(noiseLevelMapped);
    voice2n.amplitude(noiseLevelMapped);
    voice3n.amplitude(noiseLevelMapped);
    voice4n.amplitude(noiseLevelMapped);
    
    oldNoiseLevel = noiseLevel;
  }
}



void updateSliders() {
  slider1 = analogRead(SLIDER1);
  slider2 = analogRead(SLIDER2);
  slider3 = analogRead(SLIDER3);
  slider4 = analogRead(SLIDER4);

  // Map the sliders to specific starting notes and intervals
  float osc1freq = mapfloat(slider1, 0, 1023, scales [ ((newScale) % 12) ] * pow(2, oscillator_octave + newScale / 12), scales [ ((newScale + oscillator_range) % 12) ] * pow(2, oscillator_octave + (newScale + oscillator_range) / 12));
  float osc2freq = mapfloat(slider2, 0, 1023, scales [ ((newScale + oscillator_interval) % 12) ] * pow(2, oscillator_octave + (newScale + oscillator_interval) / 12), scales [ ((newScale + oscillator_interval + oscillator_range) % 12) ] * pow(2, oscillator_octave + (newScale + oscillator_interval + oscillator_range) / 12));
  float osc3freq = mapfloat(slider3, 0, 1023, scales [ ((newScale + oscillator_interval * 2) % 12) ] * pow(2, oscillator_octave + (newScale + oscillator_interval * 2) / 12), scales [ ((newScale + oscillator_interval * 2 + oscillator_range) % 12) ] * pow(2, oscillator_octave + (newScale + oscillator_interval * 2 + oscillator_range) / 12));
  float osc4freq = mapfloat(slider4, 0, 1023, scales [ ((newScale + oscillator_interval * 3) % 12) ] * pow(2, oscillator_octave + (newScale + oscillator_interval * 3) / 12), scales [ ((newScale + oscillator_interval * 3 + oscillator_range) % 12) ] * pow(2, oscillator_octave + (newScale + oscillator_interval * 3 + oscillator_range) / 12));

  voice1a.frequency(osc1freq);
  voice2a.frequency(osc2freq);
  voice3a.frequency(osc3freq);
  voice4a.frequency(osc4freq);

//  Serial.println(oscillatorDetuneAmount);

  if (oscillatorDetuneAmount >= 0) {
    voice1b.frequency(osc1freq + oscillatorDetuneAmount * osc1freq);
    voice2b.frequency(osc2freq + oscillatorDetuneAmount * osc2freq);
    voice3b.frequency(osc3freq + oscillatorDetuneAmount * osc3freq);
    voice4b.frequency(osc4freq + oscillatorDetuneAmount * osc4freq);
  } else {
    voice1b.frequency(osc1freq + (oscillatorDetuneAmount * osc1freq) / 2);
    voice2b.frequency(osc2freq + (oscillatorDetuneAmount * osc2freq) / 2);
    voice3b.frequency(osc3freq + (oscillatorDetuneAmount * osc3freq) / 2);
    voice4b.frequency(osc4freq + (oscillatorDetuneAmount * osc4freq) / 2);
  }


}


void updateTonebank() {
  // TONEBANK ROTARY CHECK
  if( toneBankLastChecked == 0 ) {
    toneBankLastChecked = millis() + ROTARY_REFRESH_RATE;
  }
  if( millis() - toneBankLastChecked > ROTARY_REFRESH_RATE ) {

    // We are returning 4,5,6,7,8,9 from the rotary switch, so just subtract 4 from each result to get 0 - 5
    tonebankNumber = rotaryTurned(TONEBANK_ROTARY_PIN) - 4;

    voiceaWaveform = tonebank[tonebankNumber][0];
    voicebWaveform = tonebank[tonebankNumber][1];
    
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
}

void updateTranspose() {
  // TRANSPOSE ROTARY CHECK
  if( transposeLastChecked == 0 ) {
    transposeLastChecked = millis() + ROTARY_REFRESH_RATE; 
  }
  if( millis() - transposeLastChecked > ROTARY_REFRESH_RATE ) {
    newScale = rotaryTurned(TRANSPOSE_ROTARY_PIN);
    oldScale = newScale;
    transposeLastChecked = millis();
  }
}

void updateEnvelopeMode() {
  if (digitalRead(SWITCHLEFTBOTTOM) == LOW) {
    attackTime = 100;
    decayTime = 100;
    sustainLevel = 1;
    releaseTime = 200;
  } else if (digitalRead(SWITCHLEFTMIDDLE) == LOW) {
    attackTime = 100;
    decayTime = 100;
    sustainLevel = 1;
    releaseTime = 1500;  
  } else if (digitalRead(SWITCHLEFTTOP) == LOW) {
    attackTime = 1000;
    decayTime = 100;
    sustainLevel = 1;
    releaseTime = 3000; 
  }
}

void updateDroneMode() {
  if (digitalRead(SWITCHRIGHTBOTTOM) == LOW) {
    oscillator_interval = 5;
    oscillator_range = 5;
  }
  if (digitalRead(SWITCHRIGHTMIDDLE) == LOW) {
    oscillator_interval = 5;
    oscillator_range = 12;
  }
  if (digitalRead(SWITCHRIGHTTOP) == LOW) {
    oscillator_interval = 7;
    oscillator_range = 5;
  }
}

void updateKeys() {
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


void updateMasterFilter(int filterFrequency) {

  int filterFrequencyMapped = map(filterFrequency, 0, 1023, 0, 22000);
  masterFilter.frequency(filterFrequencyMapped);

//  if (filterFrequency > oldFilterFrequency + 20 || filterFrequency < oldFilterFrequency - 20) {
//
//    int filterFrequencyMapped = map(filterFrequency, 0, 1023, 0, 22000);
//    masterfilter.frequency(filterFrequencyMapped);
//    oldFilterFrequency = filterFrequency;
//  }

}


void updateFilter(int filterFrequency) {
//  if (filterFrequency > oldFilterFrequency + 20 || filterFrequency < oldFilterFrequency - 20) {
//
//    int filterFrequencyMapped = map(filterFrequency, 0, 1023, 0, 22000);
//  
//    Serial.println(filterFrequencyMapped);
//    
//    voice1filter.frequency(filterFrequencyMapped);
//    voice2filter.frequency(filterFrequencyMapped);
//    voice3filter.frequency(filterFrequencyMapped);
//    voice4filter.frequency(filterFrequencyMapped);
//
//    oldFilterFrequency = filterFrequency;
//  }
}


