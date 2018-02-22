// This is a homemade function to map to floating point numbers.
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// This is a homemade function to map to floating point numbers.
float mapdouble(double x, double in_min, double in_max, double out_min, double out_max) {
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

// I know this should be automated, but the for loop was causing issues and I had to move on.
int returnTonebankFromPot(int potValue) {
   if( potValue < 79 ) {
     return 0;
   } else if (potValue >= 79 and potValue < 79 * 2) {
     return 1;
   } else if (potValue >= 79 * 2 and potValue < 79 * 3) {
     return 2;
   } else if (potValue >= 79 * 3 and potValue < 79 * 4) {
     return 3;
   } else if (potValue >= 79 * 4 and potValue < 79 * 5) {
     return 4;
   } else if (potValue >= 79 * 5 and potValue < 79 * 6) {
     return 5;
   } else if (potValue >= 79 * 6 and potValue < 79 * 7) {
     return 6;
   } else if (potValue >= 79 * 7 and potValue < 79 * 8) {
     return 7;
   } else if (potValue >= 79 * 8 and potValue < 79 * 9) {
     return 8;
   } else if (potValue >= 79 * 9 and potValue < 79 * 10) {
     return 9;
   } else if (potValue >= 79 * 10 and potValue < 79 * 11) {
     return 10;
   } else if (potValue >= 79 * 11 and potValue < 79 * 12) {
     return 11;
   } else if (potValue >= 79 * 12) {
     return 12;
   }
   return false;
}

// I know this should be automated, but the for loop was causing issues and I had to move on.
int returnOctaveFromPot(int potValue) {
   if( potValue < 128 ) {
     return 7;
   } else if (potValue >= 128 and potValue < 256) {
     return 6;
   } else if (potValue >= 256 and potValue < 384) {
     return 5;
   } else if (potValue >= 384 and potValue < 512) {
     return 4;
   } else if (potValue >= 512 and potValue < 640) {
     return 3;
   } else if (potValue >= 640 and potValue < 768) {
     return 2;
   } else if (potValue >= 768 and potValue < 896) {
     return 1;
   } else if (potValue >= 896 and potValue < 1024) {
     return 0;
   }
   return false;
}

