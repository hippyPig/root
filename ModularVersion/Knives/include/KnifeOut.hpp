#ifndef SCPH_KNIVES_KNIFEOUT_H
#define SCPH_KNIVES_KNIFEOUT_H
#include "KnifeTypeRange.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <map>

#include "TTree.h"


namespace Knives {


template <typename T>
class KnifeOut : public KnifeTypeRange <T> {
 public:
  //KnifeIn() : KnifeTypeRange<T>() {};
  KnifeOut(std::string name, T a, T b) : KnifeTypeRange<T>(name, a, b) {};
  ~KnifeOut();
  bool eval() {
    return (!((*this->val < this->cut_high()) && (*this->val > this->cut_low())));
  };
  void print() {
    oiinfo << "knife " << this->get_name() << "<=" << this->cut_low()
              << " || " << this->get_name() << ">=" << this->cut_high();
  };
  std::string cut_string() {
    std::stringstream ss;
    ss << this->get_name() << "<=" << this->cut_low()
              << "||" << this->get_name() << ">=" << this->cut_high();
    return ss.str();
  };
};


}
#endif
