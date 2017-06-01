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
