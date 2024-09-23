What I've learned:

Standard 'Blink' program:

- how to adjust the timing for the blinking of the arduino's 'L' LED

Working with LEDs:

- Breadboard (purpose, build, etc.)
  - buses (+/- columns on edges) align vertically while the alphabetical rows align horizontally
- LED(purpose, build, etc.)
  - has positive and negative leads
  - must be used with a resistor to limit the amount of current flowing through it, or else, kaboom! (jk, or am I????)
  - 2 ways to tell which lead of the LED is positive
    - positive lead is longer
    - the negative lead enters the body of the LED, there is a flat edge to the case of the LED
    - NOTE: If you happen to have an LED that has a flat side next to the longer lead, you should assume that the longer lead is positive
- Resistors:
  - unit is called Ohm (usually shortened to Ω the Greek letter Omega)
  - denote the values of resistors in kΩ (1,000 Ω) and MΩ (1,000,000 Ω)
- used 3 different values of resistor (220Ω, 1kΩ, and 10kΩ)
  - resistors look the same, except they have different colored stripes

Detecting button press and release:

- Pull down resistor:
  - large resistor (Ex: 10kΩ) lined up to pull voltage of a pin down to a low amount
  - prevents short circuits and ensures the circuits only utilize 2 states (HIGH/LOW)
  - used in this case to detect when a button is NOT being pressed

Arduino IDE/C++:

- create a synchronous block of code, which leaves time for user to click a button
- understanding of dynamic memory allocation (why, when, and how)
- install and use libraries (Hashtable, vector, etc.)

4 digit display:

-
