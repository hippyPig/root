#ifndef SCPH_KNIVES_KNIFEISNOT_H
#define SCPH_KNIVES_KNIFEISNOT_H
#include "KnifeTypeBool.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <map>

#include "TTree.h"

#include "Oi.hpp"

namespace Knives {


template <typename T>
class KnifeIsNot : public KnifeTypeBool <T> {
 public:
  KnifeIsNot(std::string name) : KnifeTypeBool<T>(name) {};
  ~KnifeIsNot();
  bool eval() {
    if (!(*this->val)) {
      return true;
    }
    return false;
  };
  void print() {
    oiinfo << "knife " << "!" << this->get_name();
  };
  std::string cut_string() {
    std::stringstream ss;
    ss << "!" << this->get_name();
    return ss.str();
  };
};


}
#endif
