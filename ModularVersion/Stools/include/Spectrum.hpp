#ifndef SCPH_SPECTRUM_CLASS_H
#define SCPH_SPECTRUM_CLASS_H

#include <iostream>

#define SPECTRUM_DEFAULT "\033[0m"
#define SPECTRUM_FORE(C) "\033[" #C "m"
#define SPECTRUM_BACK(C) "\033[" #C "m"
#define SPECTRUM_ATTR(A) "\033[" #A "m"

class spectrum {
 public:
  class fore {
   public:
    static const char* black;
    static const char* blue;
    static const char* red;
    static const char* magenta;
    static const char* green;
    static const char* cyan;
    static const char* yellow;
    static const char* white;
    static const char* console;
                       
    static const char* lightblack;
    static const char* lightblue;
    static const char* lightred;
    static const char* lightmagenta;
    static const char* lightgreen;
    static const char* lightcyan;
    static const char* lightyellow;
    static const char* lightwhite;
  };                   
  class back {         
   public:
    static const char* black;
    static const char* blue;
    static const char* red;
    static const char* magenta;
    static const char* green;
    static const char* cyan;
    static const char* yellow;
    static const char* white;
    static const char* console;
                       
    static const char* lightblack;
    static const char* lightblue;
    static const char* lightred;
    static const char* lightmagenta;
    static const char* lightgreen;
    static const char* lightcyan;
    static const char* lightyellow;
    static const char* lightwhite;
  };
  static char* colour(int attr, int fg, int bg);
  static const char* reset;
  static const char* underline;
};


#endif
