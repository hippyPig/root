#define SCPH_SPECTRUM_CLASS_H_cxx
#include "Spectrum.hpp"

#include <stdio.h>


char* spectrum::colour(int attr, int fg, int bg) {
  static char cmd[13];
  sprintf(cmd, "%c[%d;%d;%dm", 0x1B, attr, fg + 30, bg + 40);
  return cmd;
}

const char* spectrum::reset = SPECTRUM_DEFAULT;
const char* spectrum::underline = SPECTRUM_ATTR(4);


const char* spectrum::fore::black = SPECTRUM_FORE(30);
const char* spectrum::fore::blue = SPECTRUM_FORE(34);
const char* spectrum::fore::red = SPECTRUM_FORE(31);
const char* spectrum::fore::magenta = SPECTRUM_FORE(35);
const char* spectrum::fore::green = SPECTRUM_FORE(92);
const char* spectrum::fore::cyan = SPECTRUM_FORE(36);
const char* spectrum::fore::yellow = SPECTRUM_FORE(33);
const char* spectrum::fore::white = SPECTRUM_FORE(37);
const char* spectrum::fore::console = SPECTRUM_FORE(39);

const char* spectrum::fore::lightblack = SPECTRUM_FORE(90);
const char* spectrum::fore::lightblue = SPECTRUM_FORE(94);
const char* spectrum::fore::lightred = SPECTRUM_FORE(91);
const char* spectrum::fore::lightmagenta = SPECTRUM_FORE(95);
const char* spectrum::fore::lightgreen = SPECTRUM_FORE(92);
const char* spectrum::fore::lightcyan = SPECTRUM_FORE(96);
const char* spectrum::fore::lightyellow = SPECTRUM_FORE(93);
const char* spectrum::fore::lightwhite = SPECTRUM_FORE(97);

const char* spectrum::back::black = SPECTRUM_BACK(40);
const char* spectrum::back::blue = SPECTRUM_BACK(44);
const char* spectrum::back::red = SPECTRUM_BACK(41);
const char* spectrum::back::magenta = SPECTRUM_BACK(45);
const char* spectrum::back::green = SPECTRUM_BACK(42);
const char* spectrum::back::cyan = SPECTRUM_BACK(46);
const char* spectrum::back::yellow = SPECTRUM_BACK(43);
const char* spectrum::back::white = SPECTRUM_BACK(47);
const char* spectrum::back::console = SPECTRUM_BACK(49);

const char* spectrum::back::lightblack = SPECTRUM_BACK(100);
const char* spectrum::back::lightblue = SPECTRUM_BACK(104);
const char* spectrum::back::lightred = SPECTRUM_BACK(101);
const char* spectrum::back::lightmagenta = SPECTRUM_BACK(105);
const char* spectrum::back::lightgreen = SPECTRUM_BACK(102);
const char* spectrum::back::lightcyan = SPECTRUM_BACK(106);
const char* spectrum::back::lightyellow = SPECTRUM_BACK(103);
const char* spectrum::back::lightwhite = SPECTRUM_BACK(107);

