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

void flashRebootLights(int speed) {
  // Turn off Teensy LED
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  
  int i = 0;
  while(i < 20) {
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


void initializeMixers() {
  mixer1.gain(0, 1);
  mixer1.gain(1, 1);
  mixer1.gain(2, 1);
  mixer1.gain(3, 1);
  mixer2.gain(0, 1);
  mixer2.gain(1, 1);
  mixer2.gain(2, 1);
  mixer2.gain(3, 1);
  mixer3.gain(0, 1);
  mixer3.gain(1, 1);
  mixer3.gain(2, 1);
  mixer3.gain(3, 1);
  mixer4.gain(0, 1);
  mixer4.gain(1, 1);
  mixer4.gain(2, 1);
  mixer4.gain(3, 1);
}


void initalizeOscillators() {
  waveform1.begin( WAVEFORM_SINE );
  waveform1.frequency( 440 );
  waveform1.amplitude(0.5);
  waveform1.pulseWidth(0.50);
  
  waveform2.amplitude(0.5);
  waveform2.pulseWidth(0.50);
  
  waveform3.amplitude(0.5);
  waveform3.pulseWidth(0.50);
  
  waveform4.amplitude(0.5);
  waveform4.pulseWidth(0.50);

  envelope1.sustain(1);
  envelope2.sustain(1);
  envelope3.sustain(1);
  envelope4.sustain(1);
  
  envelope1.attack(200);
  envelope2.attack(200);
  envelope3.attack(200);
  envelope4.attack(200);
  
  envelope1.release(200);
  envelope2.release(200);
  envelope3.release(200);
  envelope4.release(200);

}



float calculateOscillatorInterval(int sliderValue) {
//  return mapfloat(sliderValue, 0, 1023, scales [ ((newScale) % 12) ] * pow(2, oscillator_octave + newScale / 12), scales [ ((newScale + oscillator_range) % 12) ] * pow(2, oscillator_octave + (newScale + oscillator_range) / 12));
}


