#ifndef SCPH_KNIVES_KNIFELT_H
#define SCPH_KNIVES_KNIFELT_H
#include "KnifeTypeSimple.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <map>

#include "TTree.h"

#include "Oi.hpp"

namespace Knives {


template <typename T>
class KnifeLt : public KnifeTypeSimple<T> {
 public:
  //KnifeLt() : KnifeTypeSimple<T>() {};
  KnifeLt(std::string name, T cut) : KnifeTypeSimple<T>(name, cut) {};
  ~KnifeLt() {};
  bool eval() {
    return (*this->val < this->cut());
  };
  void print() {
    oiinfo << "knife " << this->get_name() << "<" << this->cut();
  };
  std::string cut_string() {
    std::stringstream ss;
    ss << this->get_name() << "<" << this->cut();
    return ss.str();
  };
};


}
#endif
