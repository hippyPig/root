#ifndef SCPH_KNIVES_KNIFEGT_H
#define SCPH_KNIVES_KNIFEGT_H
#include "KnifeTypeSimple.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <map>

#include "TTree.h"

#include "Oi.hpp"

namespace Knives {


template <typename T>
class KnifeGt : public KnifeTypeSimple<T> {
 public:
  //KnifeGt() : KnifeTypeSimple<T>() {};
  KnifeGt(std::string name, T cut) : KnifeTypeSimple<T>(name, cut) {};
  ~KnifeGt() {};
  bool eval() {
    return (*this->val > this->cut());
  };
  void print() {
    oiinfo << "knife " << this->get_name() << ">" << this->cut();
  };
  std::string cut_string() {
    std::stringstream ss;
    ss << this->get_name() << ">" << this->cut();
    return ss.str();
  };
};


}
#endif
