void updateEffect(int footpedalValue) {
//  int bellowsValue = updateBellowsValue(footpedalValue);
//  if (tonebankEffect != lastToneBankEffect) {
//    // Turn them all off!
//    updateDelay(false, 0);
//    updateTremolo(false, 0);
//    updateWarble(false, 0);
//    updateBellows(false, 0);
//    lastToneBankEffect = tonebankEffect;
//  }
//  if (tonebankEffect == DELAY) {
//    updateDelay(true, bellowsValue);
//  } else if (tonebankEffect == WARBLE) {
//    updateWarble(true, bellowsValue);
//  } else if (tonebankEffect == BELLOWS) {
//    updateBellows(true, bellowsValue);
//  } else if (tonebankEffect == TREMOLO) {
//    updateTremolo(true, bellowsValue);
//  }
  
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
