/*
   Two Blink Number Display

   by Jonathan Bobrow
   7.27.2021
*/

// Use bits to store patterns for numbers
enum numberTops {
  T_ONE = 36, // 100100
  T_TWO = 61, // 111101
  T_THR = 61, // 111101
  T_FOU = 31, // 011111
  T_FIV = 55, // 110111
  T_SIX = 35, // 100011
  T_SEV = 61, // 111101
  T_EIG = 63, // 111111
  T_NIN = 63, // 111111
  T_ZER = 59 // 111011
};

enum numberBottoms {
  B_ONE = 36, // 100100
  B_TWO = 47, // 101111
  B_THR = 62, // 111110
  B_FOU = 24, // 011000
  B_FIV = 60, // 111100
  B_SIX = 63, // 111111
  B_SEV = 36, // 100100
  B_EIG = 63, // 111111
  B_NIN = 28, // 011100
  B_ZER = 31  // 011111
};

// array for tops and array for bottoms
byte numTops[10] = { T_ZER, T_ONE, T_TWO, T_THR, T_FOU, T_FIV, T_SIX, T_SEV, T_EIG, T_NIN };
byte numBottoms[10] = { B_ZER, B_ONE, B_TWO, B_THR, B_FOU, B_FIV, B_SIX, B_SEV, B_EIG, B_NIN };

bool isTop = true;
byte valueToDisplay = 0;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

  // toggle top
  if (buttonLongPressed()) {
    isTop = !isTop;
  }

  if (buttonPressed()) {
    // increment display
    valueToDisplay = (valueToDisplay + 1) % 10;
  }

  displayDigitFromBinary( getDisplayBinary( valueToDisplay ));
}

/*
   Get the correct display half for the digit
*/
byte getDisplayBinary(byte value) {
  // for value 0-9
  if (isTop) {
    return numTops[value];
  }
  else {
    return numBottoms[value];
  }
}

/*
   Receive a number between 0-63 and display the on bits
   to the matching faces of a Blink. i.e. the number 1
   (also represented 000001 in binary) will turn on the LED
   on face 5 (OFF, OFF, OFF, OFF, OFF, ON)

*/

void displayDigitFromBinary(byte digit) {
  FOREACH_FACE(f) {
    if ((digit >> (5-f)) & 1) {
      setColorOnFace(WHITE, f);
    }
    else {
      setColorOnFace(OFF, f);
    }
  }
}
