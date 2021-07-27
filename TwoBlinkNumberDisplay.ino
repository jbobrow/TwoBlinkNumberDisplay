/*
   Two Blink Number Display

   by Jonathan Bobrow
   7.27.2021
*/

// TODO: Orient display on 2 Blinks automatically, trivial with 1 Blink attached
// TODO: Keep both Blinks in sync for the number they are displaying
// One way to do this is to simply broadcast what the bottom should display

// Use bits to store patterns for numbers
// TODO: remove the enums and simply put the values in the arrays
// Note: these enums are really not necessary once the patterns are finalized
// (having them here makes it easy to make modifications to the design)
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
  T_ZER = 59  // 111011
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

// internal state for this Blink
bool isTop = false;
byte valueToDisplay = 0;

byte neighborFace = 0;

Timer timer;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

  // toggle top
  if (buttonLongPressed()) {
    isTop = !isTop;
  }

  // increment display if pressed
  if (buttonPressed()) {
    valueToDisplay = (valueToDisplay + 1) % 10;
  }

  // increment display every second if top
  if (isTop) {
    if (timer.isExpired()) {
      valueToDisplay = (valueToDisplay + 1) % 10;
      timer.set(1000);
    }
  }

  // get top neighbor
  FOREACH_FACE(f) {
    if (!isValueReceivedOnFaceExpired(f)) {
      neighborFace = f;
    }
  }

  if (!isTop) {
    valueToDisplay = getLastValueReceivedOnFace(neighborFace);
  }

  // display the value
  displayDigitFromBinary( getDisplayBinary( valueToDisplay ));

  // communicate our value to display on our neighbor face
  setValueSentOnFace( valueToDisplay, neighborFace );
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
    if ((digit >> (5 - f)) & 1) {
      setColorOnFace(WHITE, f);
    }
    else {
      setColorOnFace(OFF, f);
    }
  }
}
