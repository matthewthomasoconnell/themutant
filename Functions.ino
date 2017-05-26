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


void initializeMixers() {
  voice1mix.gain(0,.5);
  voice1mix.gain(1,.5);
  voice1mix.gain(2,.5);

  voice2mix.gain(0,.5);
  voice2mix.gain(1,.5);
  voice2mix.gain(2,.5);

  voice3mix.gain(0,.5);
  voice3mix.gain(1,.5);
  voice3mix.gain(2,.5);

  voice4mix.gain(0,.5);
  voice4mix.gain(1,.5);
  voice4mix.gain(2,.5);

  mastermix.gain(0,.5);
  mastermix.gain(1,.5);
  mastermix.gain(2,.5);
  mastermix.gain(3,.5);

  
}

void testTone() {

}



void startNote(int i) {

  Serial.print("Start Note " + i);
  noteTrigFlag[i] = false;

  if (i == 0) {
    voice1env.amplitude(0,releaseTime);
  } else if (i == 1) {
    voice2env.amplitude(0,releaseTime);
  } else if (i == 2) {
    voice3env.amplitude(0,releaseTime);
  } else if (i == 3) {
    voice4env.amplitude(0,releaseTime);
  }   



  
}
void stopNote(int i) {
  Serial.print("Stop Note " + i);
  
  noteTrigFlag[i] = true;
  attackWait[i] = millis();

  if (i == 0) {
    voice1env.amplitude(1,attackTime);
  } else if (i == 1) {
    voice2env.amplitude(1,attackTime);
  } else if (i == 2) {
    voice3env.amplitude(1,attackTime);
  } else if (i == 3) {
    voice4env.amplitude(1,attackTime);
  }   
}




void initalizeOscillators() {
  voice1a.begin(.3,1,WAVEFORM_SQUARE);
  voice1b.begin(.3,1,WAVEFORM_SAWTOOTH);
  voice1n.amplitude(.1);

  voice2a.begin(.3,1,WAVEFORM_SQUARE);
  voice2b.begin(.3,1,WAVEFORM_SAWTOOTH);
  voice2n.amplitude(.1);

  voice3a.begin(.3,1,WAVEFORM_SQUARE);
  voice3b.begin(.3,1,WAVEFORM_SAWTOOTH);
  voice3n.amplitude(.1);

  voice4a.begin(.3,1,WAVEFORM_SQUARE);
  voice4b.begin(.3,1,WAVEFORM_SAWTOOTH);
  voice4n.amplitude(.1);
}


void updateSliders() {
  slider1 = analogRead(A15);
  slider2 = analogRead(A14);
  slider3 = analogRead(A12);
  slider4 = analogRead(A13);

  // Map the sliders to specific starting notes and intervals
  slider1 = mapfloat(slider1, 0, 1023, scales [ ((newScale) % 12) ] * pow(2, oscillator_octave + newScale / 12), scales [ ((newScale + oscillator_range) % 12) ] * pow(2, oscillator_octave + (newScale + oscillator_range) / 12));
  slider2 = mapfloat(slider2, 0, 1023, scales [ ((newScale + oscillator_interval) % 12) ] * pow(2, oscillator_octave + (newScale + oscillator_interval) / 12), scales [ ((newScale + oscillator_interval + oscillator_range) % 12) ] * pow(2, oscillator_octave + (newScale + oscillator_interval + oscillator_range) / 12));
  slider3 = mapfloat(slider3, 0, 1023, scales [ ((newScale + oscillator_interval * 2) % 12) ] * pow(2, oscillator_octave + (newScale + oscillator_interval * 2) / 12), scales [ ((newScale + oscillator_interval * 2 + oscillator_range) % 12) ] * pow(2, oscillator_octave + (newScale + oscillator_interval * 2 + oscillator_range) / 12));
  slider4 = mapfloat(slider4, 0, 1023, scales [ ((newScale + oscillator_interval * 3) % 12) ] * pow(2, oscillator_octave + (newScale + oscillator_interval * 3) / 12), scales [ ((newScale + oscillator_interval * 3 + oscillator_range) % 12) ] * pow(2, oscillator_octave + (newScale + oscillator_interval * 3 + oscillator_range) / 12));

  voice1a.frequency(slider1);
  voice2a.frequency(slider2);
  voice3a.frequency(slider3);
  voice4a.frequency(slider4);

  voice1b.frequency(slider1);
  voice2b.frequency(slider2);
  voice3b.frequency(slider3);
  voice4b.frequency(slider4);
}


// I might want to utilize this at some point
//
//float calculateOscillatorInterval(int sliderValue) {
//   return 10.50;
////  return mapfloat(sliderValue, 0, 1023, scales [ ((newScale) % 12) ] * pow(2, oscillator_octave + newScale / 12), scales [ ((newScale + oscillator_range) % 12) ] * pow(2, oscillator_octave + (newScale + oscillator_range) / 12));
//}



// This is a homemade function to map to floating point numbers.
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}





int rotaryTurned(int pinNum) {
   int val = 0;         // variable to store the read value
   val = analogRead(pinNum);   // read the input pin
   
   if( val >= 720 and val <= 770 ) {  // 830
     return 11;
   }
   if( val >= 630 and val <= 670 ) {  // 830
     return 10;
   }
   if( val >= 440 and val <= 480 ) {  // 830
     return 9;
   }
   if( val >= 350 and val <= 390 ) {  // 830
     return 8;
   }
    if( val >= 260 and val <= 300 ) {  // 830
     return 7;
   }
   if( val >= 160 and val <= 200 ) {  // 830
     return 6;
   }
   if( val >= 70 and val <= 110 ) {  // 830
     return 5;
   }
   if( val <= 30 ) {  // 830
     return 4;
   }
   else if ( val >= (540) and val <= (580) ) { // 630
     return 3;
   }
   else if ( val >= (1000)) { // 430
     return 2;
   }
   else if ( val >= (900) and val <= (950) ) { // 230
     return 1;
   }
   else if( val >= 820 and val <= 850 )  {
     return 0;
   }
   return false;
}






