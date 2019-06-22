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

  // FOOTPEDAL
  pinMode(FOOTPEDAL, INPUT_PULLUP);

}

// This goes in the setup sketch to initialize the audio board
void initializeTeensyAudio() {
  AudioMemory(160);
  Serial.begin(115200);
  sgtl5000_1.enable();
  sgtl5000_1.volume(1);
}

void flashRebootLights(int speed) {
  // Turn off Teensy LED
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  int i = 0;
  while (i < 3) {
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


void updateAnalogInputs() {
  knob1.update();
  knob2.update();
  knob3.update();
  knob4.update();
  knob5.update();
  knob6.update();
  knob7.update();
  footpedal.update();
  slider1.update();
  slider2.update();
  slider3.update();
  slider4.update();
}

void updateKnobs() {
  updateFilters(knob1.getValue());
  updateWaveforms(knob2.getValue());
  updateOscillatorRatio(knob3.getValue());
  updateOctave(knob4.getValue());
  updateOscillatorDetune(knob5.getValue());
  updateFreqModLFO(knob6.getValue(), knob7.getValue());
  if (footpedalIsInserted) {
    updateWarble();
  }
}


// Turn on the waveforms - This is arbitrary since it will be changed in the loop
void initializeOscillators() {
  voice1a.begin(1, 1, WAVEFORM_SQUARE);
  voice2a.begin(1, 1, WAVEFORM_SQUARE);
  voice3a.begin(1, 1, WAVEFORM_SQUARE);
  voice4a.begin(1, 1, WAVEFORM_SQUARE);


  // Frequency-Modulated oscillators
  voice1b.begin(1, 1, WAVEFORM_SQUARE);
  voice2b.begin(1, 1, WAVEFORM_SQUARE);
  voice3b.begin(1, 1, WAVEFORM_SQUARE);
  voice4b.begin(1, 1, WAVEFORM_SQUARE);

  // Pro Tip: Try 4 here for more FM sounds
  voice1b.frequencyModulation(.05);
  voice2b.frequencyModulation(.05);
  voice3b.frequencyModulation(.05);
  voice4b.frequencyModulation(.05);


  masterLFO.begin(1, 1, WAVEFORM_SINE);
  shapeLFO.begin(0, 1.2, WAVEFORM_SINE); // I'm not really utilizing this.

}

// Turn on the Mixers
void initializeMixersandFilters() {

  voice1mix.gain(0, .33);
  voice1mix.gain(1, .33);
  voice1mix.gain(2, .33);

  voice2mix.gain(0, .33);
  voice2mix.gain(1, .33);
  voice2mix.gain(2, .33);

  voice3mix.gain(0, .33);
  voice3mix.gain(1, .33);
  voice3mix.gain(2, .33);

  voice4mix.gain(0, .33);
  voice4mix.gain(1, .33);
  voice4mix.gain(2, .33);

  oscillatorMixer.gain(0, .25);
  oscillatorMixer.gain(1, .25);
  oscillatorMixer.gain(2, .25);
  oscillatorMixer.gain(3, .25);

  voice1filterModMixer.gain(0, 1);
  voice1filterModMixer.gain(1, 0);
  voice2filterModMixer.gain(0, 1);
  voice2filterModMixer.gain(1, 0);
  voice3filterModMixer.gain(0, 1);
  voice3filterModMixer.gain(1, 0);
  voice4filterModMixer.gain(0, 1);
  voice4filterModMixer.gain(1, 0);


  voice1filter.resonance(2);
  voice2filter.resonance(2);
  voice3filter.resonance(2);
  voice4filter.resonance(2);

}

void updateIndicators() {
  float envValue, writeValue;
  for (int i = 0; i < 4; i++) {
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
    voice1env.amplitude(0, releaseTime);
    envelopeOpen[i] = false;
    // It's a midi thing - you wouldn't understand
    int noteFrequency1 = calculateMidiBound(1, 0);
    usbMIDI.sendNoteOff(noteFrequency1, 99, 1);
  } else if (i == 1) {
    voice2filterenv.amplitude(-1, filterReleaseTime);
    voice2env.amplitude(0, releaseTime);
    envelopeOpen[i] = false;
    // It's a midi thing - you wouldn't understand
    int noteFrequency2 = calculateMidiBound(2, 0);
    usbMIDI.sendNoteOff(noteFrequency2, 99, 2);
  } else if (i == 2) {
    voice3filterenv.amplitude(-1, filterReleaseTime);
    voice3env.amplitude(0, releaseTime);
    envelopeOpen[i] = false;
    // It's a midi thing - you wouldn't understand
    int noteFrequency3 = calculateMidiBound(3, 0);
    usbMIDI.sendNoteOff(noteFrequency3, 99, 3);
  } else if (i == 3) {
    voice4filterenv.amplitude(-1, filterReleaseTime);
    voice4env.amplitude(0, releaseTime);
    envelopeOpen[i] = false;
    // It's a midi thing - you wouldn't understand
    int noteFrequency4 = calculateMidiBound(4, 0);
    usbMIDI.sendNoteOff(noteFrequency4, 99, 4);
  }
}

void startNote(int i) {
  if (i == 0) {
    voice1filterenv.amplitude(1, filterAttackTime);
    voice1env.amplitude(1, attackTime);
    envelopeOpen[i] = true;
    // It's a midi thing - you wouldn't understand
    int noteFrequency1 = calculateMidiBound(1, 0);
    usbMIDI.sendNoteOn(noteFrequency1, 99, 1);
  } else if (i == 1) {
    voice2filterenv.amplitude(1, filterAttackTime);
    voice2env.amplitude(1, attackTime);
    envelopeOpen[i] = true;
    // Midi stuff
    int noteFrequency2 = calculateMidiBound(2, 0);
    usbMIDI.sendNoteOn(noteFrequency2, 99, 2);
  } else if (i == 2) {
    voice3filterenv.amplitude(1, filterAttackTime);
    voice3env.amplitude(1, attackTime);
    envelopeOpen[i] = true;
    // Midi stuff
    int noteFrequency3 = calculateMidiBound(3, 0);
    usbMIDI.sendNoteOn(noteFrequency3, 99, 3);
  } else if (i == 3) {
    voice4filterenv.amplitude(1, filterAttackTime);
    voice4env.amplitude(1, attackTime);
    envelopeOpen[i] = true;
    // Midi stuff
    int noteFrequency4 = calculateMidiBound(4, 0);
    usbMIDI.sendNoteOn(noteFrequency4, 99, 4);
  }
}

void updateOscillatorDetune(int knobValue) {
  oscillatorDetuneAmount = mapdouble(knobValue, 0, 1023, -100, 100);
  oscillatorDetuneAmount = oscillatorDetuneAmount + warbleAmount;
  //  Serial.println(warbleAmount);
}

void updateWarble() {
  warbleAmount = mapdouble(footpedal.getValue(), 0, 1023, -3, 3);
}

void updateOctave(int tonebankKnob) {
  if ( octaveLastChecked == 0 ) {
    octaveLastChecked = millis() + ROTARY_REFRESH_RATE;
  }
  if ( millis() - octaveLastChecked > ROTARY_REFRESH_RATE ) {
    octaveNumber = returnOctaveFromPot(tonebankKnob);
    if ( oldOctaveNumber != octaveNumber ) {
      //      Serial.println(octaveNumber);
      oldOctaveNumber = octaveNumber;
    }
    octaveLastChecked = millis();
  }
}

void updateOscillatorRatio(int knobValue) {
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
  float noiseLevelMapped = mapfloat(noiseLevel, 0, 1023, 0, 1);
  voice1n.amplitude(noiseLevelMapped);
  voice2n.amplitude(noiseLevelMapped);
  voice3n.amplitude(noiseLevelMapped);
  voice4n.amplitude(noiseLevelMapped);
}

void updateSliders() {
//  slider1 = analogRead(SLIDER1);
//  slider2 = analogRead(SLIDER2);
//  slider3 = analogRead(SLIDER3);
//  slider4 = analogRead(SLIDER4);

  // Map the sliders to specific starting notes and intervals
  float osc1freq = mapfloat(slider1.getValue(), 0, 1023, calculateSliderBound(1, 0), calculateSliderBound(1, 1));
  float osc2freq = mapfloat(slider2.getValue(), 0, 1023, calculateSliderBound(2, 0), calculateSliderBound(2, 1));
  float osc3freq = mapfloat(slider3.getValue(), 0, 1023, calculateSliderBound(3, 0), calculateSliderBound(3, 1));
  float osc4freq = mapfloat(slider4.getValue(), 0, 1023, calculateSliderBound(4, 0), calculateSliderBound(4, 1));

  voice1a.frequency(osc1freq);
  voice2a.frequency(osc2freq);
  voice3a.frequency(osc3freq);
  voice4a.frequency(osc4freq);

  if (oscillatorDetuneAmount >= 0) {
    voice1b.frequency(osc1freq + oscillatorDetuneAmount / 100 * osc1freq);
    voice2b.frequency(osc2freq + oscillatorDetuneAmount / 100 * osc2freq);
    voice3b.frequency(osc3freq + oscillatorDetuneAmount / 100 * osc3freq);
    voice4b.frequency(osc4freq + oscillatorDetuneAmount / 100 * osc4freq);
  } else {
    voice1b.frequency(osc1freq + (oscillatorDetuneAmount / 100 * osc1freq) / 2);
    voice2b.frequency(osc2freq + (oscillatorDetuneAmount / 100 * osc2freq) / 2);
    voice3b.frequency(osc3freq + (oscillatorDetuneAmount / 100 * osc3freq) / 2);
    voice4b.frequency(osc4freq + (oscillatorDetuneAmount / 100 * osc4freq) / 2);
  }

  updateSlidersMidi();

}

void updateSlidersMidi() {

  // This assumes that the synth is set to a max pitch bend of +12 semitones
  float osc1Bend = mapfloat(slider1.getRawValue(), 0, 1023, 0, (calculateMidiBound(1, 1) - calculateMidiBound(1, 0)) * 8192 / 12);
  float osc2Bend = mapfloat(slider2.getRawValue(), 0, 1023, 0, (calculateMidiBound(2, 1) - calculateMidiBound(2, 0)) * 8192 / 12);
  float osc3Bend = mapfloat(slider3.getRawValue(), 0, 1023, 0, (calculateMidiBound(3, 1) - calculateMidiBound(3, 0)) * 8192 / 12);
  float osc4Bend = mapfloat(slider4.getRawValue(), 0, 1023, 0, (calculateMidiBound(4, 1) - calculateMidiBound(4, 0)) * 8192 / 12);

  usbMIDI.sendPitchBend(osc1Bend, 1);
  usbMIDI.sendPitchBend(osc2Bend, 2);
  usbMIDI.sendPitchBend(osc3Bend, 3);
  usbMIDI.sendPitchBend(osc4Bend, 4);
}

float calculateSliderBound(int sliderNumber, int upperOrLower) {
  int transposedModeInterval = modes[currentMode][sliderNumber - 1][upperOrLower] + currentTranspose;
  int octaveMultiplier;
  if (transposedModeInterval >= 24) {
    octaveMultiplier = 0;
  } else if (transposedModeInterval >= 12) {
    octaveMultiplier = 1;
  } else {
    octaveMultiplier = 2;
  }
  int frequencyIndex =  transposedModeInterval % 12;
  float sliderBound = frequencies[ frequencyIndex ] / pow(2, octaveNumber + octaveMultiplier);

  return sliderBound;
}

int calculateMidiBound(int sliderNumber, int upperOrLower) {
  int transposedModeInterval = modes[currentMode][sliderNumber - 1][upperOrLower] + currentTranspose;
  int octaveMultiplier;

  if (transposedModeInterval >= 24) {
    octaveMultiplier = 0;
  } else if (transposedModeInterval >= 12) {
    octaveMultiplier = 1;
  } else {
    octaveMultiplier = 2;
  }
  int noteIndex =  transposedModeInterval % 12;
  int midiBound = midiNotes[ noteIndex ] - 12 * (octaveNumber + octaveMultiplier);

  return midiBound;
}


void updateMode() {
  // MODE ROTARY CHECK
  if ( modeLastChecked == 0 ) {
    modeLastChecked = millis() + ROTARY_REFRESH_RATE;
  }
  if ( millis() - modeLastChecked > ROTARY_REFRESH_RATE ) {
    // We are returning 4,5,6,7,8,9 from the rotary switch, so just subtract 4 from each result to get 0 - 5
    currentMode = rotaryTurned(MODE_ROTARY_PIN) - 4;
  }
}

void updateWaveforms(int tonebankKnob) {
  if ( tonebankLastChecked == 0 ) {
    tonebankLastChecked = millis() + ROTARY_REFRESH_RATE;
  }
  if ( millis() - tonebankLastChecked > ROTARY_REFRESH_RATE ) {
    tonebankNumber = returnTonebankFromPot(tonebankKnob);
    if ( oldTonebankNumber != tonebankNumber ) {
      //      Serial.println(tonebankNumber);

      voiceaWaveform = TONEBANK[tonebankNumber][0];
      voicebWaveform = TONEBANK[tonebankNumber][1];
      noiseLevel = TONEBANK[tonebankNumber][2];

      voice1a.begin( voiceaWaveform );
      voice2a.begin( voiceaWaveform );
      voice3a.begin( voiceaWaveform );
      voice4a.begin( voiceaWaveform );

      voice1b.begin( voicebWaveform );
      voice2b.begin( voicebWaveform );
      voice3b.begin( voicebWaveform );
      voice4b.begin( voicebWaveform );

      updateNoise(noiseLevel);

      oldTonebankNumber = tonebankNumber;
    }
    tonebankLastChecked = millis();
  }
}


void updateTranspose() {
  // TRANSPOSE ROTARY CHECK
  if ( transposeLastChecked == 0 ) {
    transposeLastChecked = millis() + ROTARY_REFRESH_RATE;
  }
  if ( millis() - transposeLastChecked > ROTARY_REFRESH_RATE ) {
    currentTranspose = rotaryTurned(TRANSPOSE_ROTARY_PIN);
    oldTranspose = currentTranspose;
    transposeLastChecked = millis();
  }
}



void updateFilters(int filterFrequency) {

  int filterFrequencyMapped = map(filterFrequency, 0, 1023, 0, 22000);
  //    int filterResonanceMapped = mapfloat(filterResonance, 0, 1023, 1, 5);

  voice1filter.frequency(filterFrequencyMapped);
  voice2filter.frequency(filterFrequencyMapped);
  voice3filter.frequency(filterFrequencyMapped);
  voice4filter.frequency(filterFrequencyMapped);

}





void updateDroneMode() {
  if (digitalRead(SWITCHRIGHTBOTTOM) == LOW) {
    droneMode = ORGAN;
    previousDroneMode = ORGAN;
  }
  if (digitalRead(SWITCHRIGHTMIDDLE) == LOW) {
    droneMode = LATCH;
    if (previousDroneMode != LATCH) {
      for (int i = 0; i < 4; i++) {
        channelOn[i] = false;
        stopNote(i);
      }
    }
    previousDroneMode = LATCH;
  }
  if (digitalRead(SWITCHRIGHTTOP) == LOW) {
    droneMode = TAMBOURA;
    if (previousDroneMode != TAMBOURA) {
      for (int i = 0; i < 4; i++) {
        channelOn[i] = false;
      }
    }
    beginTambouraMode();
    previousDroneMode = TAMBOURA;
  }
}

void updateKeys() {
  // RISING EDGE -> PUSHED BUTTON
  // FALLING EDGE -> UNPUSHED BUTTON
  for (int i = 0; i < 4; i++) {
    if (noteBounce[i].update()) {
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
        if (noteBounce[i].risingEdge()) { // Button pushed
          if (channelOn[i] == false) { // channel was off, turn it on
            channelOn[i] = true;
          } else {
            channelOn[i] = false;
          }
        }
      }
    }
  }
}

void beginTambouraMode() {
  for (int i = 0; i < 4; i++) {
    if (channelOn[i] == true) {
      long tambouraCurrentMillis = millis();
      if (tambouraCurrentMillis - tambouraPreviousMillis[i] >= randomNotePlayInterval[i]) {
        tambouraPreviousMillis[i] = tambouraCurrentMillis;
        if (notePlaying[i] == false) {
          //          Serial.println(randomNotePlayInterval[i]);
          startNote(i);
          notePlaying[i] = true;
        } else {
          stopNote(i);
          notePlaying[i] = false;
        }
      }
    } else {
      stopNote(i);
    }
  }
}


void updateFreqModLFO(int rate, int depth) {
  // Pro Tip: Try 400 here for more FM sounds
  float masterLFORate = mapfloat(rate, 0, 1023, 0, 4);
  float masterLFODepth = mapfloat(depth, 0, 1023, 0, 1);

  masterLFO.frequency(masterLFORate);
  masterLFO.amplitude(masterLFODepth);
}

//This has been replaced by FM LFO
void updateFilterLFO(int rate, int depth) {
  float masterLFORate = mapfloat(rate, 0, 1023, 0, 20);
  float masterLFODepth = mapfloat(depth, 0, 1023, 0, 1);

  // Filter Envelope
  voice1filterModMixer.gain(0, 1 - masterLFODepth);
  voice2filterModMixer.gain(0, 1 - masterLFODepth);
  voice3filterModMixer.gain(0, 1 - masterLFODepth);
  voice4filterModMixer.gain(0, 1 - masterLFODepth);

  // LFO Modulation
  voice1filterModMixer.gain(1, masterLFODepth);
  voice2filterModMixer.gain(1, masterLFODepth);
  voice3filterModMixer.gain(1, masterLFODepth);
  voice4filterModMixer.gain(1, masterLFODepth);

  masterLFO.frequency(masterLFORate);
  masterLFO.amplitude(masterLFODepth);

}

void updateEnvelopeMode() {
  if (digitalRead(SWITCHLEFTBOTTOM) == LOW) {
    attackTime = 500;
    filterAttackTime = 1000;
    releaseTime = 5000;
    filterReleaseTime = 1000;
  } else if (digitalRead(SWITCHLEFTMIDDLE) == LOW) {
    attackTime = 1000;
    filterAttackTime = 2000;
    releaseTime = 2000;
    filterReleaseTime = 1000;
  } else if (digitalRead(SWITCHLEFTTOP) == LOW) {
    attackTime = 5000;
    filterAttackTime = 8000;
    releaseTime = 5000;
    filterReleaseTime = 5000;
  }
}

void checkForFootpedal() {
  int footpedalValue = analogRead(FOOTPEDAL);
  if (footpedalValue < 300 or footpedalValue > 400) {
    footpedalIsInserted = true;
  }
}
