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
  B_SIX = 35, // 100011
  B_SEV = 36, // 100100
  B_EIG = 63, // 111111
  B_NIN = 28, // 011100
  B_ZER = 31  // 011111
};


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

/*
   Receive a number between 0-63 and display the on bits
   to the matching faces of a Blink. i.e. the number 1
   (also represented 000001 in binary) will turn on the LED
   on face 5 (OFF, OFF, OFF, OFF, OFF, ON)

*/

void displayDigitFromBinary(byte digit) {
  FOREACH_FACE(f) {
    if ((digit >> f) & 1) {
      setColorOnFace(WHITE, f);
    }
    else {
      setColorOnFace(OFF, f);
    }
  }
}
