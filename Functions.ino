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

   voice1mix.gain(0,.5);
   voice1mix.gain(1,.5);
   voice1mix.gain(2,.5);

}

void testTone() {

}



void initalizeOscillators() {
  voice1a.begin(.3,445,WAVEFORM_SQUARE);
  voice1b.begin(.3,440,WAVEFORM_SAWTOOTH);
}



float calculateOscillatorInterval(int sliderValue) {
   return 10.50;
//  return mapfloat(sliderValue, 0, 1023, scales [ ((newScale) % 12) ] * pow(2, oscillator_octave + newScale / 12), scales [ ((newScale + oscillator_range) % 12) ] * pow(2, oscillator_octave + (newScale + oscillator_range) / 12));
}



// This is a homemade function to map to floating point numbers.
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

