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
  voice1a.begin(1,1,WAVEFORM_SQUARE);
  voice1b.begin(1,1,WAVEFORM_SQUARE);

  voice2a.begin(1,1,WAVEFORM_SQUARE);
  voice2b.begin(1,1,WAVEFORM_SQUARE);

  voice3a.begin(1,1,WAVEFORM_SQUARE);
  voice3b.begin(1,1,WAVEFORM_SQUARE);

  voice4a.begin(1,1,WAVEFORM_SQUARE);
  voice4b.begin(1,1,WAVEFORM_SQUARE);

  masterLFO.begin(1,1,WAVEFORM_SINE);



  
}

// Turn on the Mixers
void initializeMixersandFilters() {
  
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

  oscillatorMixer.gain(0,.25);
  oscillatorMixer.gain(1,.25);
  oscillatorMixer.gain(2,.25);
  oscillatorMixer.gain(3,.25);

  voice1filterModMixer.gain(0,1);
  voice1filterModMixer.gain(1,0);
  voice2filterModMixer.gain(0,1);
  voice2filterModMixer.gain(1,0);
  voice3filterModMixer.gain(0,1);
  voice3filterModMixer.gain(1,0);
  voice4filterModMixer.gain(0,1);
  voice4filterModMixer.gain(1,0);

  masterMixer.gain(0,1);

}

void updateIndicators() {
  float envValue, writeValue;
  for(int i=0; i<4; i++){
    if (i == 0) {
      envValue = voice1env.read();
    } else if (i == 1) {
      envValue = voice2env.read();
    } else if (i == 2) {
      envValue = voice3env.read();
    } else if (i == 3) {
      envValue = voice4env.read();
    }
    writeValue = mapfloat(envValue, 0, 1, 0, 255);
    analogWrite(indicatorLeds[i], writeValue);
  }
}

void stopNote(int i) {
  if (i == 0) {
    voice1filterenv.amplitude(-1, filterReleaseTime);
    voice1env.amplitude(0,releaseTime);
    envelopeOpen[i] = false;
  } else if (i == 1) {
    voice2filterenv.amplitude(-1, filterReleaseTime);
    voice2env.amplitude(0,releaseTime);
    envelopeOpen[i] = false;
  } else if (i == 2) {
    voice3filterenv.amplitude(-1, filterReleaseTime);
    voice3env.amplitude(0,releaseTime);
    envelopeOpen[i] = false;
  } else if (i == 3) {
    voice4filterenv.amplitude(-1, filterReleaseTime);
    voice4env.amplitude(0,releaseTime);
    envelopeOpen[i] = false;
  }
}

void startNote(int i) {  
  if (i == 0) {
    voice1filterenv.amplitude(1,filterAttackTime);
    voice1env.amplitude(1,attackTime);
    envelopeOpen[i] = true;
  } else if (i == 1) {
    voice2filterenv.amplitude(1,filterAttackTime);
    voice2env.amplitude(1,attackTime);
    envelopeOpen[i] = true;
  } else if (i == 2) {
    voice3filterenv.amplitude(1,filterAttackTime);
    voice3env.amplitude(1,attackTime);
    envelopeOpen[i] = true;
  } else if (i == 3) {
    voice4filterenv.amplitude(1,filterAttackTime);
    voice4env.amplitude(1,attackTime);
    envelopeOpen[i] = true;
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

  updateFilters(knob1, knob2); // This is causing major glitches
  updateNoise(knob4);
  updateOscillatorRatio(knob5);
  updateOscillatorDetune(knob6);
  updateEffect(footpedal);



}


void updateEffect(int footpedalValue) {
  int bellowsValue = updateBellowsValue(footpedalValue);
  if (tonebankEffect != lastToneBankEffect) {
    // Turn them all off!
    updateDelay(false, 0);
    updateTremolo(false, 0);
    updateWarble(false, 0);
    updateBellows(false, 0);
    lastToneBankEffect = tonebankEffect;
  }
  if (tonebankEffect == DELAY) {
    updateDelay(true, bellowsValue);
  } else if (tonebankEffect == WARBLE) {
    updateWarble(true, bellowsValue);
  } else if (tonebankEffect == BELLOWS) {
    updateBellows(true, bellowsValue);
  } else if (tonebankEffect == TREMOLO) {
    updateTremolo(true, bellowsValue);
  }
  
}


void updateDelay(bool effectOn, int footpedalValue) {
  if (effectOn) {

    // This should probably be put into separate outputs.
    int delaySpeed = map(footpedalValue, 0, 1023, 100, 500);
    masterMixer.gain(0,.7); 
    masterMixer.gain(3,.3); 
    delayFilter.frequency(1000);
    delayFilter.resonance(2);
    masterDelay.delay(0, delaySpeed);
  } else {
    // Turn everything off
    masterMixer.gain(0,1); 
    masterMixer.gain(3,0); 
    delayFilter.frequency(500);
    delayFilter.resonance(2);
    masterDelay.disable(0);
  }
}

void updateWarble(bool effectOn, int footpedalValue) {
  if (effectOn) {
    // Get to Warbling!
    warbleAmount = mapfloat(footpedal, 0, 1023, -.03, .03);
  } else {
    // Cut it out!
    warbleAmount = 0;
  }
}
void updateBellows(bool effectOn, int footpedalValue) {
  if (effectOn) {
    // Get to Bellowing!
    float reedsVolume = mapfloat(footpedal, 0, 1023, 0, 1);
    masterMixer.gain(0,reedsVolume);
  } else {
    // Cut it out!
    bellowsAmount = 0;
  }



  
}
void updateTremolo(bool effectOn, int footpedalValue) {
  if (effectOn) {
    // Get to Tremoloing!
    voice1filterModMixer.gain(0,.5);
    voice1filterModMixer.gain(1,.5);
    voice2filterModMixer.gain(0,.5);
    voice2filterModMixer.gain(1,.5);
    voice3filterModMixer.gain(0,.5);
    voice3filterModMixer.gain(1,.5);
    voice4filterModMixer.gain(0,.5);
    voice4filterModMixer.gain(1,.5);

    float masterLFOFrequency = mapfloat(footpedalValue, 0, 1023, 0, .5);

    masterLFO.frequency(masterLFOFrequency);
    masterLFO.amplitude(.2);
    
  } else {
    // Cut it out!
    voice1filterModMixer.gain(0,1);
    voice1filterModMixer.gain(1,0);
    voice2filterModMixer.gain(0,1);
    voice2filterModMixer.gain(1,0);
    voice3filterModMixer.gain(0,1);
    voice3filterModMixer.gain(1,0);
    voice4filterModMixer.gain(0,1);
    voice4filterModMixer.gain(1,0);    
  }
}


void updateOscillatorDetune(int knobValue){
  oscillatorDetuneAmount = mapfloat(knobValue, 0, 1023, -1, 1);
  oscillatorDetuneAmount = oscillatorDetuneAmount + warbleAmount;
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
    float noiseLevelMapped = mapfloat(noiseLevel, 0, 1023, 0, .5);
      
    voice1n.amplitude(noiseLevelMapped);
    voice2n.amplitude(noiseLevelMapped);
    voice3n.amplitude(noiseLevelMapped);
    voice4n.amplitude(noiseLevelMapped);
    
}


void updateSliders() {
  slider1 = analogRead(SLIDER1);
  slider2 = analogRead(SLIDER2);
  slider3 = analogRead(SLIDER3);
  slider4 = analogRead(SLIDER4);

  float osc1freq = mapfloat(slider1, 0, 1023, fixed_intervals[newScale][0][0], fixed_intervals[newScale][0][1]);
  float osc2freq = mapfloat(slider2, 0, 1023, fixed_intervals[newScale][1][0], fixed_intervals[newScale][1][1]);
  float osc3freq = mapfloat(slider3, 0, 1023, fixed_intervals[newScale][2][0], fixed_intervals[newScale][2][1]);
  float osc4freq = mapfloat(slider4, 0, 1023, fixed_intervals[newScale][3][0], fixed_intervals[newScale][3][1]);

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


// THIS IS FOR CHROMATIC, 4THS
//
//void updateSliders() {
//  slider1 = analogRead(SLIDER1);
//  slider2 = analogRead(SLIDER2);
//  slider3 = analogRead(SLIDER3);
//  slider4 = analogRead(SLIDER4);
//
//  // Map the sliders to specific starting notes and intervals
//  float osc1freq = mapfloat(slider1, 0, 1023, scales [ ((newScale) % 12) ] * pow(2, oscillator_octave + newScale / 12), scales [ ((newScale + oscillator_range) % 12) ] * pow(2, oscillator_octave + (newScale + oscillator_range) / 12));
//  float osc2freq = mapfloat(slider2, 0, 1023, scales [ ((newScale + oscillator_interval) % 12) ] * pow(2, oscillator_octave + (newScale + oscillator_interval) / 12), scales [ ((newScale + oscillator_interval + oscillator_range) % 12) ] * pow(2, oscillator_octave + (newScale + oscillator_interval + oscillator_range) / 12));
//  float osc3freq = mapfloat(slider3, 0, 1023, scales [ ((newScale + oscillator_interval * 2) % 12) ] * pow(2, oscillator_octave + (newScale + oscillator_interval * 2) / 12), scales [ ((newScale + oscillator_interval * 2 + oscillator_range) % 12) ] * pow(2, oscillator_octave + (newScale + oscillator_interval * 2 + oscillator_range) / 12));
//  float osc4freq = mapfloat(slider4, 0, 1023, scales [ ((newScale + oscillator_interval * 3) % 12) ] * pow(2, oscillator_octave + (newScale + oscillator_interval * 3) / 12), scales [ ((newScale + oscillator_interval * 3 + oscillator_range) % 12) ] * pow(2, oscillator_octave + (newScale + oscillator_interval * 3 + oscillator_range) / 12));
//
//  voice1a.frequency(osc1freq);
//  voice2a.frequency(osc2freq);
//  voice3a.frequency(osc3freq);
//  voice4a.frequency(osc4freq);
//
////  Serial.println(oscillatorDetuneAmount);
//
//  if (oscillatorDetuneAmount >= 0) {
//    voice1b.frequency(osc1freq + oscillatorDetuneAmount * osc1freq);
//    voice2b.frequency(osc2freq + oscillatorDetuneAmount * osc2freq);
//    voice3b.frequency(osc3freq + oscillatorDetuneAmount * osc3freq);
//    voice4b.frequency(osc4freq + oscillatorDetuneAmount * osc4freq);
//  } else {
//    voice1b.frequency(osc1freq + (oscillatorDetuneAmount * osc1freq) / 2);
//    voice2b.frequency(osc2freq + (oscillatorDetuneAmount * osc2freq) / 2);
//    voice3b.frequency(osc3freq + (oscillatorDetuneAmount * osc3freq) / 2);
//    voice4b.frequency(osc4freq + (oscillatorDetuneAmount * osc4freq) / 2);
//  }
//
//
//}


void updateTonebank() {
  // TONEBANK ROTARY CHECK
  if( toneBankLastChecked == 0 ) {
    toneBankLastChecked = millis() + ROTARY_REFRESH_RATE;
  }
  if( millis() - toneBankLastChecked > ROTARY_REFRESH_RATE ) {
    
    // We are returning 4,5,6,7,8,9 from the rotary switch, so just subtract 4 from each result to get 0 - 5
    tonebankNumber = rotaryTurned(TONEBANK_ROTARY_PIN) - 4;

    voiceaWaveform = TONEBANK[tonebankNumber][0];
    voicebWaveform = TONEBANK[tonebankNumber][1];
    tonebankEffect = TONEBANK[tonebankNumber][2];
    
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






void updateFilters(int filterFrequency, int filterResonance) {

    int filterFrequencyMapped = map(filterFrequency, 0, 1023, 0, 22000);
    int filterResonanceMapped = mapfloat(filterResonance, 0, 1023, 1, 5);
  
    voice1filter.frequency(filterFrequencyMapped);
    voice2filter.frequency(filterFrequencyMapped);
    voice3filter.frequency(filterFrequencyMapped);
    voice4filter.frequency(filterFrequencyMapped);

    voice1filter.resonance(filterResonanceMapped);
    voice2filter.resonance(filterResonanceMapped);
    voice3filter.resonance(filterResonanceMapped);
    voice4filter.resonance(filterResonanceMapped);
}


void updateKeys() {
  // RISING EDGE -> PUSHED BUTTON
  // FALLING EDGE -> UNPUSHED BUTTON
  for(int i=0; i<4; i++){
    if (noteBounce[i].update()){
        if (droneMode == ORGAN) {
          if (noteBounce[i].risingEdge()) { // Button pushed, turn on note
            startNote(i);
            channelOn[i] = true;
          } else if (noteBounce[i].fallingEdge()) { // Button unpushed
            stopNote(i);
            channelOn[i] = false;
          }
        } else if (droneMode == LATCH) {
          if (noteBounce[i].risingEdge()) { // Button pushed
            if (channelOn[i] == false) { // note was off, turn it on
              startNote(i);
              channelOn[i] = true;
            } else {
              stopNote(i);
              channelOn[i] = false;
            }
          }
        } else if (droneMode == TAMBOURA) {
          unsigned long currentTambouraMillis = millis();
          if (noteBounce[i].risingEdge()) { // Button pushed
            if (channelOn[i] == false) { // channel was off, turn it on
              channelOn[i] = true;

              // We hit the interval
              if (currentTambouraMillis - previousTambouraMillis >= tambouraInterval) {
                // save the last time you opened the envelope
                previousTambouraMillis = currentTambouraMillis;
            
                // if the LED is off turn it on and vice-versa:
                if (envelopeOpen[i] == false) {
                  startNote(i);
                }
      
              }            
            } else {
              // Turn off that channel
              channelOn[i] = false;
            }
          }
        }
    }
  }
  
}

void updateEnvelopeMode() {
  if (digitalRead(SWITCHLEFTBOTTOM) == LOW) {
    attackTime = 3000;
    releaseTime = 7000;
    filterAttackTime = 4000;
    filterReleaseTime = 7000;
  } else if (digitalRead(SWITCHLEFTMIDDLE) == LOW) {
    attackTime = 2000;
    releaseTime = 3000;
    filterAttackTime = 2000;
    filterReleaseTime = 3000;
  } else if (digitalRead(SWITCHLEFTTOP) == LOW) {
    attackTime = 10;
    releaseTime = 500;
    filterAttackTime = 10;
    filterReleaseTime = 50;
  }
}

void updateDroneMode() {
  if (digitalRead(SWITCHRIGHTBOTTOM) == LOW) {
    droneMode = ORGAN;
  }
  if (digitalRead(SWITCHRIGHTMIDDLE) == LOW) {
    droneMode = LATCH;
  }
  if (digitalRead(SWITCHRIGHTTOP) == LOW) {
    droneMode = TAMBOURA;
  }
}



