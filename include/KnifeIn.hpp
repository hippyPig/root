#ifndef SCPH_KNIVES_KNIFEIN_H
#define SCPH_KNIVES_KNIFEIN_H
#include "KnifeTypeRange.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <map>

#include "TTree.h"

#include "Oi.hpp"

namespace Knives {


template <typename T>
class KnifeIn : public KnifeTypeRange <T> {
 public:
  //KnifeOut() : KnifeTypeRange<T>() {};
  KnifeIn(std::string name, T a, T b) : KnifeTypeRange<T>(name, a, b) {};
  ~KnifeIn();
  bool eval() {
    return (((*this->val < this->cut_high()) && (*this->val > this->cut_low())));
  };
  void print() {
    oiinfo << "knife " << this->cut_low() << "<" << this->get_name()
              << "<" << this->cut_high();
  };
  std::string cut_string() {
    std::stringstream ss;
    ss << this->cut_low() << "<" << this->get_name() << "<" << this->cut_high();
    return ss.str();
  };
};


}
#endif
