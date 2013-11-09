#ifndef SCPH_KNIVES_KNIVENOTEQUAL_H
#define SCPH_KNIVES_KNIVENOTEQUAL_H
#include "KnifeTypeSimple.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <map>

#include "TTree.h"

#include "Oi.hpp"

namespace Knives {


template <typename T>
class KnifeNotEqual : public KnifeTypeSimple<T> {
 public:
  KnifeNotEqual(std::string name, T cut) : KnifeTypeSimple<T>(name, cut) {};
  ~KnifeNotEqual() {};
  bool eval() {
    return (*this->val != this->cut());
  };
  void print() {
    oiinfo << "knife " << this->get_name() << "!=" << this->cut();
  };
  std::string cut_string() {
    std::stringstream ss;
    ss << this->get_name() << "!=" << this->cut();
    return ss.str();
  };
};


}
#endif
