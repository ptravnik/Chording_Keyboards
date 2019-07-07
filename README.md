This project contains files for K-Chord and other chording keyboards.

[1] Why chording?
Medics may disagree, but it seems that constantly bending fingers back and forth while touch-typing by the 10-finger method is the second reason (besides the poor posture) why people have carpal tunnel syndrome. In such sense, "ergonomic" keyboards help just a little if not at all. There are numerous mechanical keyboard on the market. Cherry switches and their clones offer performance superior to the film keyboards, but the idea is pretty much the same: 10 fingers, 60 or so switches; once in a while one must reach that switch in the galaxy far, far away with the left or right pinky!
The main drive for this project was not to type faster than speech, a a steno professionals do, but to type at reasonable speed whole day with no strain. In practice, I seldom exceed 20 WPM (just cannot think GOOD code that fast!), but can maintain this for many hours - without ever bending a finger. The keyboard has 8 finger buttons and 6 thumb buttons. The fingers always remain in the "home" position; there is nothing else, but the home position. The thumbs move as the nature intended: in the main (grip) joint, with the zero second joint bending. By shifting the fingers down 1 inch, a set of two analog joysticks, three mouse buttons and 4 arrow keys is accessible. Together with the left thumb, the arrow keys provide full set of cursor movements, including page-up and page-down.
This is the third version of my chording keyboard. The work in progress is described on the Hackaday site https://hackaday.io/project/25386-chording-hybrid-keyboard. The experience has been good so far. I use it now as my primary input method, for text writing, programming, and operating specialized software.

[2] Building a chording keyboard.
This project depository contains:

(a) the full electronics description as a set of three PCBs,

(b) A set of CNC files for making a body, and

(c) the code for Arduino Micro, which drives the entire project. No modification is required at the operating system side; the keyboard works as an off-the-shelf USB keyboard. It has been tested on Windows and Linux extensively.

To order PCBs, simply use Gerber files provided or modify KiCAD files to you liking. The body can be machined or laser-cut. To build the firmware, copy the .ino folder and use Arduino IDE to compile and upload (put any macros of your liking into the macros.h file).
