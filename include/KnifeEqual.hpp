#ifndef SCPH_KNIVES_KNIFEEQUAL_H
#define SCPH_KNIVES_KNIFEEQUAL_H
#include "KnifeTypeSimple.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <map>

#include "TTree.h"

#include "Oi.hpp"

namespace Knives {


template <typename T>
class KnifeEqual : public KnifeTypeSimple<T> {
 public:
  KnifeEqual(std::string name, T cut) : KnifeTypeSimple<T>(name, cut) {};
  ~KnifeEqual() {};
  bool eval() {
    return (*this->val == this->cut());
  };
  void print() {
    oiinfo << "knife " << this->get_name() << "==" << this->cut();
  };
  std::string cut_string() {
    std::stringstream ss;
    ss << this->get_name() << "==" << this->cut();
    return ss.str();
  };
};


}
#endif
